#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "tag.h"

int main() 
{
  u32 val = 0x6D776E6E;
  printf("%d\n", convert_size(val));
  return 0;
}
