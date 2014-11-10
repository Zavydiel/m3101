#include "tag.h"
#include <unistd.h>
#include <stdlib.h>

int read_u8(int fd, u8 *val)
{
  if (read(fd, val, 1) <= 0)
    return 0;
  return 1;
}

int read_u16(int fd, u16 *val)
{
  u8 high;
  u8 low;
  if (read_u8(fd, &high) == 0) return 0;
  if (read_u8(fd, &low) == 0) return 0;

  *val = (high << 8) | low;

  return 1;
}

int read_u32(int fd, u32 *val) 
{
  u16 high;
  u16 low;
  if (read_u16(fd, &high) == 0) return 0;
  if (read_u16(fd, &low) == 0) return 0;  
  *val = (high << 16) | low;

  return 1;  
}

u32 convert_size(u32 size) 
{
  size = ((size & 0xFFFFFF00) >> 1) | (size & 0x000000FF);
  size = ((size & 0xFFFF0000) >> 1) | (size & 0x0000FFFF);
  size = ((size & 0xFF000000) >> 1) | (size & 0x00FFFFFF);

  return size;
}

char * read_string(int fd, char *to, int size, int encoding)
{  
  if (to == NULL)
    to = malloc(size + 1);
  to = realloc(to, size + 1);
  
  if (read(fd, to, size) <= 0) return NULL;

  to[size] = 0;

  return to;
}

