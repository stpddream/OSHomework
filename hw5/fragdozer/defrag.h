#include <stdio.h>

#define SUPER_ITEMS 6
#define BLOCK_BASE 1024
#define INODE_ITEMS 25
#define N_DBLOCKS 10
#define N_IBLOCKS 4
#define INODE_SIZE sizeof(iNode)
#define BLOCK_SIZE sb.size
#define TRUE 1
#define FALSE 0
#define INODE_ADDR_BY_IDX(idx) 1024+INODE_SIZE*idx
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

int get_inode_by_addr(int, iNode*);
int get_inode_by_index(int, iNode*);
int is_free_inode(int);
int next_inode(int);
int next_occupied_inode(int);
void print_inode(iNode*);
