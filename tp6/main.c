#include <stdio.h>
#include <stdlib.h>

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

  /*sort_info_t infos;
  int size = 96;
  char* buf = malloc(size);
  get_file_info("../tp5/asr4/00000.mp3", &infos);*/

  /*printf("Artist: %s\n", infos.artist);
  printf("Album: %s\n", infos.album);
  printf("Track %s\n", infos.track);
  printf("Title: %s\n", infos.title);
  printf("Genre: %s\n", infos.genre);*/

  /*i = check_and_create_folder("/home/infoetu/crosettn/zorro");
  printf("%d\n", i);
  i = check_and_create_folder("/home/infoetu/crosettn/zorro");
  printf("%d\n", i);*/

  /*i = create_tree("/home/infoetu/crosettn/m3101/tp6/toto/toto/");
  printf("%d\n", i);
  i = create_tree("/home/infoetu/crosettn/m3101/tp6/toto/toto/");
  printf("%d\n", i);*/

  /*get_file_name(buf, size, &infos, "mp3");
    printf("%s\n", buf);*/

  /*sort_file("/home/infoetu/crosettn/m3101/tp6/musique/", "../tp5/asr4/00000.mp3");*/

  int i;

  if (argc <2)
    return -1;
  
  for (i = 2; i < argc; i++)
    {
      printf("%s\n", argv[i]);
      process(argv[1], argv[i]);
    }
  
  return 0;
}
