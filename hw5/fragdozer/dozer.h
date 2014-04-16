#ifndef DOZER_H
#define DOZER_H

#include "dwriter.h"
#include "dreader.h"
#include <stdio.h>
#include <stdlib.h>
#include "filesys.h"



extern int inode_begin, inode_end;
extern Superblock sb;
extern FILE* fp_w;
extern FILE* fp_r;
extern int data_idx_w;


void doze(iNode* inode);


int copy_datai(int from_idx, int to_idx);
int write_addri(int base_idx, int item, int addr);
int fseeki(FILE* stream, long idx);
int fseekio(FILE* stream, long idx, int item);
int read_int(FILE* stream, long idx, int item);


int write_data(int index, char* data);
char* read_data(int index);    
int write_addr(int pos, int addr);


int get_inode_by_addr(int, iNode*);
int get_inode_by_index(int, iNode*);
int is_free_inode(int);
int next_inode(int);
int next_occupied_inode(int);

#endif