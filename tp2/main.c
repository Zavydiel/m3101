#include "string.h"

int main() 
{
  char hello[18] = "hello";
  char *a = "a";
  char *zzz = "zzzz";
  char *world = " world";
  char *tmp;

  printf("%d\n", my_strlen(hello));
  printf("%d\n", my_strcmp(hello, a));
  printf("%d\n", my_strcmp(zzz, a));
  printf("%d\n", my_strcmp(hello, zzz));
  printf("%d\n", my_strcmp(hello, hello));
  printf("%s\n", my_strcat(hello, world));
  printf("%d\n", my_strlen(hello));

  printf("%c\n", (int) *my_strchr(hello, (int) 'e'));
  printf("%c\n", (int) *my_strchr(hello, (int) 'z'));  
  tmp =  my_strstr(hello, world);
  if (tmp) printf("%s\n", tmp);
  tmp =  my_strstr(hello, zzz);
  if (tmp) printf("%s\n", tmp);

  return 0;
}


