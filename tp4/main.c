#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../tp3/fct.c"
#define S_FLAG 1
#define M_FLAG 2

char flag = 0;

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

void copy(char* old, char *new, int length) 
{
  int i;
  for(i = 0; i < length; i++) 
    {
      new[i] = old[i];
    }
}

char * miroir(char *s)
{
  int n = strlen(s);
  int i;
  char* p = dis_malloc(n + 1);

  for (i = 0; i < n; ++i)
    {
      p[i] = s[n - 1 - i];
    }

    p[i] = 0;
  
    free(s);
  
  return p;
}

char* getoptions(int argc, char**  argv)
{
  int i, j, l, str = 0;
  char* string = NULL;
  for (i = 1; i < argc; ++i)
    {
      if (argv[i][0] == '-')
	{
	  /* if (strchr(argv[i], 'm'))
	    flag |= M_FLAG;

	  if (strchr(argv[i], 's'))
	      flag |= S_FLAG;

	  if (flag == 0)
	  return 0;*/
	  l = strlen(argv[i]);
	  for (j = 1; j < l; j++)
	    {
	      if (argv[i][j] == 'm')
		flag |= M_FLAG;
	      else if (argv[i][j] == 's')
		flag |= S_FLAG;
	      else
		{
		  flag = 0;
		  return string;
		}
	    }
	} 
      else 
	{	  
	  if (str)
	    return 0;
	  
	  l = strlen(argv[i]);
	  string = dis_malloc(l + 1);
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
  return string;
}

char *saisie()
{
  int i = 0;
  int size = 32;
  char *p = dis_malloc(32);
  char c;
  
  while (!isspace(c = getchar()))
    {
      if (i >= size) 
	{
	  size *= 2;
	  p = dis_realloc(p, size);
	}
      p[i] = c;
      i++;
    }
  
  p = dis_realloc(p, i + 1);
  p[i] = 0;
  return p;
}

void error() 
{
  printf("mauvaise utilisation\n");
}

int main2(int argc, char**  argv) 
{
  char* param = getoptions(argc, argv);
  
  if (flag == 0) 
    {
      dis_free(param);
      error();
      return 1;
    }

  if (flag & S_FLAG) 
    {
      if (param != NULL)
	{
	  dis_free(param);
	  error();
	  return 1;
	}
      param = saisie();
    }

  if (flag & M_FLAG)
    {
      if (strlen(param) == 0)
	{
	  dis_free(param);
	  error();
	  return 1;
	}
      param = miroir(param);
    }

    printf("%s\n", param);
    dis_free(param);
    return 0;
}

int main(int argc, char **argv)
{
  /*int i = 0;
    for(i = 0 ; i < 1000 ; i++)*/
    while(1)
    main2(argc, argv);
  return 0;
}
