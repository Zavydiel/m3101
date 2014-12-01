typedef struct
{
  char* artist;
  char* album;
  char* genre;
  char* title;
  char* track;
} sort_info_t;

const char *get_file_extension(const char *file);

void clean_string(char *s);

int get_file_info(const char *source_file, sort_info_t *info);
