#include <stdio.h>
#include "fct.h"

int main()
{
  
  /*chunk c2;
  void *ptr;
  chunk c = {42, 4, NULL, NULL, NULL};
  ptr = &heap[0];
  c.free = 85;
  c.size = 8;

  printf("%d\n", get_int(ptr));
  set_int(ptr, 1337);
  printf("%d\n", get_int(ptr));
  set_chunk(&c, ptr);
  get_chunk(&c2, ptr);
  print_chunk(&c2);*/
  
  print_memory();
  init_alloc();
  print_memory();
  return 0;
}

