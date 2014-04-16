
/* 
 * File:   dreader.h
 * Author: Panda & Jacy
 *
 * Created on April 15, 2014, 10:20 PM
 */

#ifndef DREADER_H
#define	DREADER_H

#define BUFFER_SIZE_R 4096
#define CHUNK_ADDR(IDX) DATA_BEGIN + IDX * BUFFER_SIZE_R


#include "filesys.h"

extern char* buffer_r;
extern FILE* fp_r;
extern int chunk_id;
extern iNode* inode_arr;

int dr_init_buffer();
int dr_close();

/* given data block index, return the address of the buffer_r begin in data section*/
int find_chunk(int data_idx);
/* given data blck index, return the location(index) of the data block in buffer_r*/
int find_datablock(int data_idx);
void load_chunk(int idx);

int dr_read_buf(int idx);
int dr_read_block(int idx);
int dr_read_indir(int block_idx, int item_idx);




#endif	/* DREADER_H */


