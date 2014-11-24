#include "tag.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int read_u8(int fd, u8 *val)
{
  if (read(fd, val, 1) <= 0)
    {
      perror("read");
      return 0;
    }
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
  size = ((size & 0xFFFFFF00) >> 1) | (size & 0x0000007F);
  size = ((size & 0xFFFF8000) >> 1) | (size & 0x0000BFFF);
  size = ((size & 0xFFC00000) >> 1) | (size & 0x003FFFFF);

  return size;
}

char *read_unicode(int fd, char *to, int size)
{
  char buf[2];
  int i, bom = 0;
  
  if (to == NULL)
    to = malloc(size / 2);
   
  if (read(fd, buf, 2) == -1)
    {
      perror("read");
      return 0;
    }
  if (buf[0] == 0xFE)
      bom = 1;

  for (i = 0; i < (size / 2) - 1; i ++) 
    {
      if (read(fd, buf, 2) == -1)
	{
	  perror("read");
	  return 0;
	}
      
      to[i] = buf[bom];
    }
  to[i] = 0;
  
  return to;
}

char *read_ascii(int fd, char* to, int size) 
{
   if (to == NULL)
     to = malloc(size + 1);
	  
   if (read(fd, to, size) <= 0) {
     perror("read_ascii");
     return NULL;
   }
   to[size] = 0;

   return to;
}
 

char * read_string(int fd, char *to, int size, int encoding)
{  
  if (encoding == 0)
      return read_ascii(fd, to, size);
  if (encoding == 1)
      return read_unicode(fd, to, size);
  return NULL;
}

int tag_read_id3_header(int fd, id3v2_header_t *header)
{
  if (strncmp("ID3", read_string(fd, header->ID3, 3, 0), 3))
      return -1;
  if (!read_u16(fd, &(header->version)))
    return -1;
  if (header->version > 0x0300)
    return -1;
  if (!read_u8(fd, &(header->flags)))
    return -1;
  if (!read_u32(fd, &(header->size)))
      return -1;
  header->size = convert_size(header->size);

  return 0;
}

int tag_read_one_frame(int fd, id3v2_frame_t *frame)
{
  u8 encoding;
  int i;
  
  if (read_string(fd, frame->id, ID3V2_FRAME_ID_LENGTH, 0) == NULL) 
    return -1;

  if (!read_u32(fd, &(frame->size)))
    return -1;
  if (!read_u16(fd, &(frame->flags)))
    return -1;

  for (i = 0; i < ID3V2_FRAME_ID_LENGTH; i++)
    if (!isdigit(frame->id[i]) && !isupper(frame->id[i])) {
      lseek(fd, frame->size, SEEK_CUR);
      return -1;
    }
  
  if (frame->id[0] != 'T' || !strcmp(frame->id, "TXXX")) {
    lseek(fd, frame->size, SEEK_CUR);
    frame->text = NULL;
    return -1;
  }

  if (!read_u8(fd, &encoding))
    return -1;
  frame->text = read_string(fd, NULL,(int) (frame->size - 1), (int) encoding);
  
  if (frame->text == NULL)
    return -1;
   
  return 0;
}

id3v2_frame_t *tag_get_frames(const char *file, int *frame_array_size)
{
  id3v2_frame_t *frames = malloc(sizeof(id3v2_frame_t));
  id3v2_header_t header;
  int fd;
  int i = 0;

  if ((fd = open(file, O_RDONLY)) == -1) 
    {
      perror("open");
      return NULL;
    }

  if (tag_read_id3_header(fd, &header) == -1)
    {
      return NULL;
    }

  while (tag_read_one_frame(fd, &(frames[i])) == 0)
    {
       i++;
      frames = realloc(frames, (i + 1) * sizeof(id3v2_frame_t));
    }

  *frame_array_size = i;

  if (i == 0) 
    return NULL; 

  return frames;
}

void tag_free(id3v2_frame_t *frames, int frame_count)
{
  int i;

  for (i = 0; i < frame_count; i++) 
    {
      free(frames[i].text);
    }

  free(frames);
}




