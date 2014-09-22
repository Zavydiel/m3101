/* int my_strlen(char s[]) */
/* { */
/*   int i  = 0; */
/*   while (s[i] !=0)  */
/*     i++; */
/*   return i; */
/* } */
#include <stdio.h>

int my_strlen(const char *s)
{
  int i = 0;
  while (*(s + i) != 0)
    i++;
  return i;
}

int my_strcmp(const char *s1, const char *s2)
{
  char i = 0;
  while (*(s1 + i) == *(s2 + i) && *(s1 + i) != 0) 
    i++;
  return *(s1 + i) - *(s2 + i);
}

int my_strcmp2(const char *s1, const char *s2, int n)
{
  char i = 0;
  while (*(s1 + i) == *(s2 + i) && *(s1 + i) != 0 && i < n - 1) 
    i++;
  return *(s1 + i) - *(s2 + i);
}

char *my_strcat(char *s1, char *s2)
{
  char i = 0, j = 0;
  while (*(s1 + i) != 0)
    i++;
  
  while(*(s2 + j) != 0)
    {
      *(s1 + i) = *(s2 + j);
      i++;
      j++;
    }
  return s1;
}

char *my_strchr(char *s, int c)
{
  char i = 0;
  while (*(s + i) != c && *(s + i) != 0)
    i++;
  return (s + i);
}
            
char *my_strstr(char *haystack, char *needle)
{
  int needleLength = my_strlen(needle), i = 0;
  while (*(haystack + i) != 0)
    {
      if (my_strcmp2(haystack + i, needle, needleLength) == 0)
	return haystack + i;
      i++;
    }
  return NULL;
}
