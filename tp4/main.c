#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../tp3/fct.c"
#define S_FLAG 1
#define M_FLAG 2

void *dis_malloc(size_t size) 
{
  return my_malloc(size);
}

void dis_free(void *ptr) 
{
  my_free(ptr);
}

void *dis_realloc(void *ptr, size_t size)
{
  return my_realloc(ptr, size);
}

char * miroir(const char *s)
{
  int n = strlen(s);
  int i;

  char* p = dis_malloc(n + 1);
  
  printf("chaine:%s\n", s);
  printf("taille:%d\n", n);

  for (i = 0; i < n; ++i)
    {
      p[i] = s[n - 1 - i];
    }

  p[i] = 0;

  return p;
}

char getoptions(int argc, char**  argv, char* string)
{
  int i, j, l, str = 0;
  char flag = 0;
  for (i = 1; i < argc; ++i)
    {
      if (argv[i][0] == '-')
	{
	  l = strlen(argv[i]);
	  for (j = 1; j < l; j++) 
	    {
	      if (argv[i][j] == 'm')
		flag |= M_FLAG;
	      else if (argv[i][j] == 's')
		flag |= S_FLAG;
	      else 
		return 0;
	    }
	} 
      else 
	{
	  
	  if (str)
	    return 0;
	  
	  l = strlen(argv[i]);
	  string = dis_malloc(string, l + 1);
	  printf("toto:");
	  for (j = 0; j < l; j++)
	    {
	      string[j] = argv[i][j];
	      printf("%c",  argv[i][j]);
	    }
	  string[j] = 0;
	  str++;
	  printf("\n");
	}
    }
  printf("%s\n", string);
  return flag;
}

char *saisie()
{
  int i = 0;
  int size = 32;
  char *p;
  char c;
  
  while (!isspace(c = getchar()))
    {
      i++;
      if (i >= size) 
	{
	  p = dis_realloc(p, size * 2);
	}
      p[i - 1] = c;
    }
  
  p = dis_realloc(p, i);
  
  return p;
}

void error() 
{
  printf("mauvaise utilisation\n");
}

 
int main(int argc, char**  argv) 
{
  /*if( argc > 1)
    printf("%s\n", miroir(argv[1]));

    printf("%s\n", saisie());*/
  char* param = dis_malloc(0);
  char flags;
  flags = getoptions(argc, argv, param);
  if (flags == 0) 
    {
      error();
      return 1;
    }

  if (flags & S_FLAG) 
    {
      if (strlen(param))
	{
	  error();
	  return 1;
	}
      param = saisie();
    }

  if (flags & M_FLAG)
    {
      if (strlen(param) == 0)
	{
	  error();
	  return 1;
	}
      param = miroir(param);
    }

    printf("%s\n", param);

  return 0;
}
