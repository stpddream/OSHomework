#define BUFFER_SIZE_W 

extern char* buffer_w;
extern int buffer_ptr_w;
extern FILE* fp_w;
extern int data_idx_w;

int dw_init_buffer();
int dw_close();

void dw_flush();
void write2buf(int data_addr);
