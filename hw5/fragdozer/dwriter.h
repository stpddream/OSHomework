

#ifndef DWRITER_H
#define DWRITER_H

#include "util.h"
#include <stdio.h>

#define BUFFER_SIZE_W get_buf_size(DEFAULT_BUF_SIZE); 

extern char* buffer_w;
extern int buffer_ptr_w;
extern FILE* fp_w;
extern int data_idx_w;
extern int data_addr_w;

int dw_init_buffer();
int dw_close();
void dw_flush();
int dw_write2buf(int chunk_addr);
int dw_write_arr(int*);

#endif