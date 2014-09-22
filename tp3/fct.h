typedef struct
{
  unsigned int free ; 
  unsigned int size ; 
  unsigned char * addr ; 
  unsigned char * next_chunk ; 
  unsigned char * previous_chunk ; 
} chunk ;

unsigned int get_int(void *ptr);

void set_int(void *ptr, unsigned int val);

void set_chunk(chunk *c, unsigned char *ptr);

void print_chunk(void *ptr);
