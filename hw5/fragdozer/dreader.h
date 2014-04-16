#define BUFFER_SIZE_R 

extern char* buffer_r;
extern FILE* fp_r;

int dr_init_buffer();
int dr_close();

/* given data block index, return the address of the buffer_r begin in data section*/
int find_chunk(int data_idx);
/* given data blck index, return the location(index) of the data block in buffer_r*/
int find_datablock(int data_idx);
void load_chunk(int chunk_idx);

int read_data();
int* read_indir();

