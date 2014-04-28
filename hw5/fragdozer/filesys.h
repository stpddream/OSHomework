/* 
 * File:   filesys.h
 * Author: Panda & Jacy
 *
 * Created on April 16, 2014, 3:19 AM
 */

#ifndef FILESYS_H
#define	FILESYS_H


#define TRUE 1
#define FALSE 0
#define SUPER_ITEMS 6
#define BOOT_SIZE 512
#define BLOCK_BASE 1024
#define DATA_BEGIN (BLOCK_BASE + sb.data_offset * BLOCK_SIZE)

#define INODE_ITEMS 25
#define INODE_BEGIN (BLOCK_BASE + sb.inode_offset * BLOCK_SIZE)
#define INODE_SEC_SIZE (DATA_BEGIN - INODE_BEGIN)  
#define N_DBLOCKS 10
#define N_IBLOCKS 4


#define INODE_SIZE sizeof(iNode)
#define BLOCK_SIZE sb.size

//Convert Inode Index to Inode Address in bytes
#define INODE_ADDR(IDX) (BLOCK_BASE + sb.inode_offset * BLOCK_SIZE + INODE_SIZE * IDX)

//Convert Data Index to Data Address
#define DATA_ADDR(IDX) (BLOCK_BASE + sb.data_offset * BLOCK_SIZE + IDX * BLOCK_SIZE)

#define DATA_ADDR_O(IDX, OFFSET) (DATA_ADDR(IDX) + OFFSET * sizeof(int))
#define N_INDIR_PT (BLOCK_SIZE / sizeof(int))

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

#endif	/* FILESYS_H */

