#include <stdio.h>
#include "fct.h"

int main()
{  
  void *ptr;
  void *ptr2;
  int i;
  
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
  
  init_alloc();
  print_memory();
  my_malloc(1);
  print_memory();
  ptr  = my_malloc(11);
  my_malloc(42);
  print_memory();
  my_free(ptr);
  print_memory();
  ptr = my_malloc(2);
  ptr2 = my_malloc(4);
  my_free(ptr);
  my_free(ptr2);
  print_memory();
  ptr2 = my_malloc(21);
  my_realloc(ptr2, 80);
  print_memory();
  
  for (i = 0; i < 87; i++) 
    {
      printf("toto\n");
      my_realloc(ptr, 7);
    }

    print_memory();
  return 0;
}
