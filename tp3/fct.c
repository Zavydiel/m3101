#include <stdio.h>
#include "fct.h"

static int initialized = 0;

unsigned int get_int(void *ptr)
{
  return * (unsigned int*) ptr;
}

void set_int(void *ptr, unsigned int val)
{
  *(unsigned int*) ptr = val;
}
  
void set_chunk(chunk *c, unsigned char *ptr)
{
  set_int(ptr - 2 * sizeof(unsigned int), c->free);
  set_int(ptr - sizeof(unsigned int), c->size);
  set_int(ptr + c-> size  - 3 * sizeof(unsigned int), c->size);
}

void get_chunk(chunk *c, unsigned char *ptr)
{
  c->free = get_int(ptr - 2 * sizeof(unsigned int));
  c->size = get_int(ptr - sizeof(unsigned int));
  c->addr = ptr;
  if (ptr == &heap[2 * sizeof(unsigned int)]) 
    c->previous_chunk = NULL;
  else
    c->previous_chunk = ptr - get_int(ptr - sizeof(unsigned int));

  if (ptr + c->size >= &heap[sizeof(heap) - 1])
    c->next_chunk = NULL;
  else
    c->next_chunk = ptr + c->size;
}

void print_chunk(chunk *c)
{
  /*printf("free: %d\t", c->free);*/
  if (c->free)
    printf("free\t");
  else
    printf("allocd\t");
  printf("size: %d\t", c->size);
  printf("addr: %p\t", c->addr);
  printf("prev: %p\t", c->previous_chunk);
  printf("next: %p\n", c->next_chunk);
}

void init_alloc()
{
  chunk c = {1, sizeof(heap), &heap[2 * sizeof(unsigned int)], NULL, NULL};
  if (initialized != 0) return;
  initialized = 42;
  set_chunk(&c, (void*) &heap[2 * sizeof(unsigned int)]);
}

void print_memory()
{
  /*int i;
  for (i=0; i < sizeof(heap); i++)
    {
      printf("%d ", heap[i]);
      if ((i+1)%4 == 0) 
	printf("%c ", '|');
    }
    printf("\n");*/

  chunk tmp;
  chunk* current = &tmp;
 
  printf("-----------------------------------------------------------------------------------\n");
  
  get_chunk(current, (unsigned char*)  &heap[2 * sizeof(unsigned int)]);
  print_chunk(current);

  while (current->next_chunk != NULL) {      
      get_chunk(current, current->next_chunk);
      print_chunk(current);
    }
    printf("-----------------------------------------------------------------------------------\n");
}

void *my_malloc(size_t size) 
{  
  int actual_size = size + 3 * sizeof(unsigned int); 
  chunk tmp;
  chunk *current = &tmp;
  chunk new, new_remains;

  init_alloc();

  printf("malloc(%ld)\n", size);

  get_chunk(current, (unsigned char*) &heap[2 * sizeof(unsigned int)]);
  while (current->free !=1 || current->size < actual_size)
    {
      if (current->next_chunk == NULL)
	{
	  printf("Pas assez de place");
	  return NULL;
	}
      get_chunk(current, current->next_chunk);
    }
  
  if (current->size - actual_size <= 1 + 3*sizeof(unsigned int)) 
    {
      new.size = current->size;
      new_remains.size = 0;
    }
  else 
    {
      new.size = actual_size;
      new_remains.size = current->size - actual_size;
    }  

  new.free = 0;
  set_chunk(&new, (void*) current->addr);
  new_remains.free = 1;
  if (new_remains.size != 0) 
    {
      set_chunk(&new_remains, (void*) (current->addr + actual_size));
    }
  printf("%p\n", current->addr);

  return (void*) current->addr;
}

void my_free(void *ptr) {
  char* p = (char*) ptr;
  chunk current;
  chunk prev;
  chunk next;
  
  if (ptr == NULL) return;

  printf("free(%p)\n", ptr);
  init_alloc();

  get_chunk(&current, (void*) p);
  if (current.previous_chunk != NULL) 
    {
      get_chunk(&prev, (void*) current.previous_chunk);
      if (prev.free != 0) 
	{
	  prev.size += current.size;
	  set_chunk(&prev, prev.addr);
	  get_chunk(&current, prev.addr);
	}
    }

  current.free = 1;
  
  if (current.next_chunk != NULL) 
    {
      get_chunk(&next, (void*) current.next_chunk);
      if (next.free != 0) 
	{
	  current.size += next.size;
	}
    }
  set_chunk(&current, current.addr);
}

void *my_realloc(void *ptr, size_t size)
{
  int i;
  char *p = my_malloc(size);
  char *old = ptr;
  printf("realloc(%ld)\n", size);

  if (ptr == NULL)
    return p;

  my_free(ptr);

  for (i = 0; i < size; i++)
    {
      p[i] = old[i];
    }
  
  return p;
}
