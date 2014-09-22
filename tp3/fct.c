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

void print_chunk(void *ptr)
{
  int size = get_int(ptr + sizeof(unsigned int));
  printf("%d\n", get_int(ptr));
  printf("%d\n", size);
  printf("%d\n", get_int(ptr + size - sizeof(unsigned int)));
}
