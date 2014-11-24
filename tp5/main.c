#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "tag.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void read_file(const char* file) 
{
  int fd;
  id3v2_header_t header;
  int frame_number;
  id3v2_frame_t *frames;
  int i;

  fd = open(file, O_RDONLY);

  if (!tag_read_id3_header(fd, &header))
      printf(" header ok!\n");
  
  printf("magic number: %s\n", header.ID3);
  printf("version: %0x\n", header.version);
  printf("flags: %0x\n", header.flags);
  printf("size: %d\n", header.size);
  printf("\n");

  frames = tag_get_frames(file, &frame_number);
  
  for (i = 0; i < frame_number; i++)
    {
      printf("id: %s\n", frames[i].id);
      printf("flags: %0x\n", frames[i].flags);
      printf("size: %d\n", frames[i].size);
      printf("text: %s\n", frames[i].text);
      printf("\n");
    }

  tag_free(frames, frame_number);  
}


int main(int argc, char** argv) 
{
  int i;
  for (i = 1; i < argc; i++)
    {
      read_file(argv[i]);
    }

  return 0;
}

