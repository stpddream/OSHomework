#include <stdio.h>
#include <stdlib.h>


#ifndef DOZER_H
#define DOZER_H


#define TRUE 1
#define FALSE 0
#define SUPER_ITEMS 6
#define BOOT_SIZE 512
#define BLOCK_BASE 1024

#define INODE_ITEMS 25
#define N_DBLOCKS 10
#define N_IBLOCKS 4
#define INODE_SIZE sizeof(iNode)
#define BLOCK_SIZE sb.size

//Convert Inode Index to Inode Address in bytes
#define INODE_ADDR(IDX) BLOCK_BASE + sb.inode_offset * BLOCK_SIZE + INODE_SIZE * IDX

//Convert Data Index to Data Address
#define DATA_ADDR(IDX) BLOCK_BASE + sb.data_offset * BLOCK_SIZE + IDX * BLOCK_SIZE

#define DATA_ADDR_O(IDX, OFFSET) DATA_ADDR(IDX) + OFFSET * sizeof(int)
#define N_INDIR_PT BLOCK_SIZE / sizeof(int)

#define MIN(A, B) (A > B) ? A : B



typedef struct{
  int size;
  int inode_offset;
  int data_offset;
  int swap_offset;
  int free_inode;
  int free_iblock;
}Superblock;

typedef struct{
  int next_inode;
  int protect;
  int nlink;
  int size;
  int uid;
  int gid;
  int ctime;
  int mtime;
  int atime;
  int dblocks[N_DBLOCKS];
  int iblocks[N_IBLOCKS];
  int i2block;
  int i3block;
} iNode;


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