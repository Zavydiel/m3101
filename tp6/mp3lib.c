#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../tp5/tag.h"
#include "mp3lib.h"

const char *get_file_extension(const char *file) 
{
  int i;
  while (file[i] != 0) { 
    if (file[i] == '.')
	return &file[i];
    i++;
  }
  return NULL;
  
}

void clean_string(char *s)
{
  int i = 1;
  
  s[0] = toupper(s[0]);
  while (s[i] != 0)
    {
      s[i] = tolower(s[i]);
      if (s[i] == '/')
	s[i] = '-';
      i++;
    }
}

int get_file_info(const char *source_file, sort_info_t *info) 
{
  id3v2_frame_t *frames;
  int nb_frames, i;

  frames = tag_get_frames(source_file, &nb_frames);

  for (i = 0; i < nb_frames; i++)
    {
      if (strcmp(frames[i].id, "TALB") == 0) 
	{
	  info->album = malloc(frames[i].size);
	  strcpy(info->album, frames[i].text);
	}
      else  if (strcmp(frames[i].id, "TCON") == 0) 
	{
	  info->genre = malloc(frames[i].size);
	  strcpy(info->genre, frames[i].text);
	}
      else  if (strcmp(frames[i].id, "TPE1") == 0) 
	{
	  info->artist = malloc(frames[i].size);
	  strcpy(info->artist, frames[i].text);
	}
      else  if (strcmp(frames[i].id, "TRCK") == 0) 
	{
	  info->track = malloc(frames[i].size);
	  strcpy(info->track, frames[i].text);
	}
      else  if (strcmp(frames[i].id, "TIT2") == 0) 
	{
	  info->title = malloc(frames[i].size);
	  strcpy(info->title, frames[i].text);
	}
    }

  tag_free(frames, nb_frames);

  return 0;
}
