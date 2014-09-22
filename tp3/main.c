#include <stdio.h>
#include "fct.h"

int main()
{
  unsigned int a = 420;
  void *ptr = &a;

  printf("%d\n", get_int(ptr));
  set_int(ptr, 1337);
  printf("%d\n", get_int(ptr));

  return 0;
}
