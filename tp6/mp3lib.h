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

const char *get_artist_folder(char *buffer, int size, const char *root_folder, const sort_info_t *info);

const char *get_genre_folder(char *buffer, int size, const char *root_folder, const sort_info_t *info);

int check_and_create_folder(const char *path);

int create_tree(const char *fullpath);

const char *get_file_name(char *buffer, int size, const sort_info_t *info, const char *ext);

int sort_file(const char *root_folder, const char *source_file);

int process(const char* root_folder, const char* source_file);
