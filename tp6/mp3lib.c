#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>


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

const char *get_artist_folder(char *buffer, int size, const char *root_folder, const sort_info_t *info)
{
  snprintf(buffer, size, "%s/By Artist/%c/%s/%s - %s/", root_folder, info->artist[0], info->artist, info->artist, info->album);  

  return buffer;
}

const char *get_genre_folder(char *buffer, int size, const char *root_folder, const sort_info_t *info) 
{
  snprintf(buffer, size, "%s/By Genre/%s/%s/%s - %s/", root_folder, info->genre, info->artist, info->artist, info->album); 

  return buffer;
}

int check_and_create_folder(const char *path)
{
  struct stat buf;
  int i;
  if (mkdir(path, 0700))
    {
      if (stat(path, &buf)) 
	{
	  return -1;
	}
      else 
	{
	  if (S_ISDIR(buf.st_mode))
	    {
	      i = access(path, R_OK | W_OK | X_OK);
	      return i;
	    }
	  else 
	    {
	      return -1;
	    }
	}
    }
  return 0;
}

int create_tree(const char *fullpath)
{
  int i;
  int l = strlen(fullpath);
  char* path = malloc(l + 1);
  
  for (i = 0; i < l; i++)
    {
      path[i] = fullpath[i];
      if (path[i] == '/' || path[i] == 0) 
	{
	  path[i + 1] = 0;
	  check_and_create_folder(path);
	}
    }

  return check_and_create_folder(path);
}

const char *get_file_name(char *buffer, int size, const sort_info_t *info, const char *ext)
{
  snprintf(buffer, size, "%s - %s - %02d.%s%s", info->artist, info->album, atoi(info->track), info->title, ext);  
  
  return buffer;
}

int sort_file(const char *root_folder, const char *source_file) 
{
  int size = 255;
  sort_info_t info;
  char* buffer = malloc(size);
  char* newpath = malloc(size);
  char* filename = malloc(size);
  
  printf("%s\n", source_file);
  
  get_file_info(source_file, &info);

  if (info.artist == NULL || info.album == NULL || info.title == NULL
      || info.track == NULL || info.genre == NULL)
    {
      return -1;
    }

  get_file_name(filename, size, &info, get_file_extension(source_file));

  get_genre_folder(buffer, size, root_folder, &info);
  create_tree(buffer);
  snprintf(newpath, size,  strcat(buffer, filename));
  link(source_file, newpath);

  get_artist_folder(buffer, size, root_folder, &info);
  create_tree(buffer);
  snprintf(newpath, size, strcat(buffer, filename));
  link(source_file, newpath);  

  return 0;
}

int process(const char* root_folder, const char* source_file)
{
  struct stat buf; 
  struct dirent* file;
  DIR* dir;
  char* path = malloc(255);
  if (stat(source_file, &buf)) 
    {
      printf("stat");
      return -1;
    }
  else 
    {
      if (S_ISDIR(buf.st_mode))
	{
	  dir = opendir(source_file);
	  while ((file = readdir(dir)) != NULL)
	    {
	      if (file->d_name[0] == '.')
		continue;
	      snprintf(path, 255, "%s/%s", source_file, file->d_name);
	      printf("%s\n", path);
	      process(root_folder, path);
	    }
	  closedir(dir);
	}
      else
	sort_file(root_folder, source_file);
    }
  return 0;
}
