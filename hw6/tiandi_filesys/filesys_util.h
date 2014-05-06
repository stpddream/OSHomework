/* 
 * File:   filesys_util.h
 * Author: Panda & Jacy 
 *
 * Created on April 28, 2014, 9:17 PM
 */

#ifndef FILESYS_UTIL_H
#define	FILESYS_UTIL_H

#include "filesys_hd.h"
#include "filesys.h"
#include "bitmap.h"



/* Base of group size, formula as follows */
/* Base = Proportion of ibit blocks + Proportion of allocation bit blocks + 
          Proportion of inode blocks + Proportion of data blocks */

#define N_BIT_E_BLOCK (BLOCK_SZ * 8)    //Number of bit each block
#define N_INODE_E_BLOCK (BLOCK_SZ / INODE_SZ)   //Number of inodes each block

#define P_IBIT_BLOCKS 1
#define P_ABIT_BLOCKS (N_INODE_E_BLOCK * DATABL_INODE_RATIO)
#define P_INODE_BLOCKS (N_BIT_E_BLOCK * P_IBIT_BLOCKS / N_INODE_E_BLOCK)
#define P_DATA_BLOCKS (DATABL_INODE_RATIO * N_INODE_E_BLOCK) * P_INODE_BLOCKS

#define GROUP_SIZE_BASE \
        (P_IBIT_BLOCKS + P_ABIT_BLOCKS + P_INODE_BLOCKS + P_DATA_BLOCKS)


/* Pointer to blocks in file system (make sure device is present) */
#define SUPERBL_BEGIN BOOT_SZ
#define CONTENT_BEGIN (BOOT_SZ+SUPERBL_SZ)
#define IBIT_BEGIN (CONTENT_BEGIN + BLOCK_SZ * device->superblock.ibit_offset)
#define ABIT_BEGIN (CONTENT_BEGIN + BLOCK_SZ * device->superblock.abit_offset)
#define INODE_BEGIN (CONTENT_BEGIN + BLOCK_SZ * device->superblock.inode_offset)
#define DATA_BEGIN (CONTENT_BEGIN + BLOCK_SZ * device->superblock.data_offset)
#define INODE_SEC_SIZE (DATA_BEGIN - INODE_BEGIN)  

#define IBIT_ADDR(IDX) (IBIT_BEGIN + IDX)
#define ABIT_ADDR(IDX) (ABIT_BEGIN + IDX) 
#define IBIT_BYTE_ADDR(IDX) (IBIT_BEGIN + device->superblock.inode_count / 8 - 1 - IDX)
#define IBIT_IDX(BYTE, OFFSET) (BYTE * 8 + OFFSET)

#define ABIT_BYTE_ADDR(IDX) (ABIT_BEGIN + device->superblock.databl_count / 8 - 1 - IDX)
#define ABIT_IDX(BYTE, OFFSET) (BYTE * 8 + OFFSET)

//Convert Inode Index to Inode Address in bytes
#define INODE_ADDR(IDX) (INODE_BEGIN + INODE_SZ * IDX)
//Convert Data Index to Data Address
#define DATA_ADDR(IDX) (DATA_BEGIN + BLOCK_SZ * IDX)
#define DATA_ADDR_O(IDX, OFFSET) (DATA_ADDR(IDX) + OFFSET * sizeof(int))
#define N_INDIR_PT (BLOCK_SZ / sizeof(int))

#define N_PTR (BLOCK_SZ/sizeof(int))
#define DBLOCK_SZ (N_DBLOCKS*BLOCK_SZ)
#define IBLOCK_SZ (N_IBLOCKS*N_PTR*BLOCK_SZ)
#define I2BLOCK_SZ (N_PTR*N_PTR*BLOCK_SZ)
#define I3BLOCK_SZ (N_PTR*N_PTR*N_PTR*BLOCK_SZ)
/** Helper Constants */
#define GRP_HEAD_SZ (BOOT_SZ + SUPERBL_SZ)

#define DP_DBLOCK 0
#define DP_IBLOCK 1
#define DP_I2BLOCK 2
#define DP_I3BLOCK 3

/****8 blablabalba */

int cal_n_ibit_blocks(int size);
int round_sz(int size);
int rnd2sm(int val, int base);

int get_valid_size(iNode* inode, int pos, int bytes);
int find_data_ptr(iNode* inode, int fs_alloc_datablpos, DataPos* dp);
int calc_pos(Dev* device, iNode* inode, DataPos* dp);
int find_next_block(DataPos* dp);
int calc_cur_size(DataPos* dp);
int clear_data_bits(Dev* device, iNode* inode);
int alloc_data_ptr(Dev* device, iNode* inode, DataPos* dp);



/* Debug Qu */
//void superbl_print(Superblock* sb);
#endif	/* FILESYS_UTIL_H */
