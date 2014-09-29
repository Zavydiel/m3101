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

  if (ptr + get_int(ptr + sizeof(unsigned int)) >= &heap[sizeof(heap) - 1])
    c->next_chunk = NULL;
  else
    c->next_chunk = ptr + get_int(ptr + sizeof(unsigned int)) + sizeof(unsigned int);
}

void print_chunk(chunk *c)
{
  printf("free: %d\n", c->free);
  printf("size: %d\n", c->size);
  printf("addr: %p\n", c->addr);
  printf("next: %p\n", c->next_chunk);
  printf("previous: %p\n", c->previous_chunk);
}

void init_alloc()
{
  chunk c = {1, sizeof(heap), &heap[0], NULL, NULL};
  set_chunk(&c, (void*) &heap);
}

void print_memory()
{
  int i;
  for (i=0; i < sizeof(heap); i++)
    {
      printf("%d ", heap[i]);
    }
  printf("\n");
}

void *my_alloc(unsigned int size) 
{
  chunk *current = get_chunk((*void) &heap); 

  return NULL;
}
