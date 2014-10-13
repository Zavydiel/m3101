typedef struct
{
  unsigned int free ; 
  unsigned int size ; 
  unsigned char * addr ; 
  unsigned char * next_chunk ; 
  unsigned char * previous_chunk ; 
} chunk ;

unsigned char heap[50000000];

unsigned int get_int(void *ptr);

void set_int(void *ptr, unsigned int val);

void set_chunk(chunk *c, unsigned char *ptr);

void get_chunk(chunk *c, unsigned char *ptr);

void print_chunk(chunk *c);

void init_alloc();

void print_memory();

void *malloc(size_t size);

void free(void *ptr);
