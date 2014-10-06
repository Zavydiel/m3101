#include <stdio.h>
#include "fct.h"

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
  set_int(ptr, c->free);
  set_int(ptr + sizeof(unsigned int), c->size);
  set_int(ptr + c-> size - sizeof(unsigned int), c->size);
}

void get_chunk(chunk *c, unsigned char *ptr)
{
  c->free = get_int(ptr);
  c->size = get_int(ptr + sizeof(unsigned int));
  c->addr = ptr;
  if (ptr == &heap[0]) 
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
  printf("free: %d\t", c->free);
  printf("size: %d\t", c->size);
  printf("addr: %p\t", c->addr);
  printf("next: %p\t", c->next_chunk);
  printf("prev: %p\n", c->previous_chunk);
}

void init_alloc()
{
  chunk c = {1, sizeof(heap), &heap[0], NULL, NULL};
  set_chunk(&c, (void*) &heap);
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
 
  get_chunk(current, (unsigned char*) &heap);
  print_chunk(current);

  while (current->next_chunk != NULL)
    {
      get_chunk(current, current->next_chunk);
      print_chunk(current);
    }
  printf("---------------------------------------------------------\n");
}

void *my_alloc(unsigned int size) 
{
  int actual_size = size + 3 * sizeof(unsigned int); 
  chunk tmp;
  chunk *current = &tmp;
  chunk new, new_remains;

  get_chunk(current, (unsigned char*) &heap);
  while (current->free !=1 && current->size < actual_size)
    {
      if (current->next_chunk == NULL)
	return NULL;
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

  return (void*) current->addr;
}
