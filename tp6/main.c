#include <stdio.h>

#include "mp3lib.h"

int main(int argc, char** argv)
{
  /*const char* ptr = get_file_extension(argv[1]);
  if (argc > 1)
    {
      if (ptr != NULL)
	{
	  printf("%s\n", ptr);
	}	else {
	printf("NULL\n");
      }
      }*/
  sort_info_t infos;
  
  get_file_info("../tp5/asr4/00000.mp3", &infos);

  printf("Artist: %s\n", infos.artist);
  printf("Album: %s\n", infos.album);
  printf("Track %s\n", infos.track);
  printf("Title: %s\n", infos.title);
  printf("Genre: %s\n", infos.genre);
  
  return 0;
}
