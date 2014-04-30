/* 
 * File:   filesys_util.h
 * Author: Panda & Jacy 
 *
 * Created on April 28, 2014, 9:17 PM
 */

#ifndef FILESYS_UTIL_H
#define	FILESYS_UTIL_H

#include "filesys.h"

/* Base of group size, formula as follows */
/* Base = Proportion of ibit blocks + Proportion of allocation bit blocks + 
          Proportion of inode blocks + Proportion of data blocks */

#define N_BIT_E_BLOCK (BLOCK_SZ * 8)    //Number of bit each block
#define N_INODE_E_BLOCK (BLOCK_SZ / INODE_SZ)   //Number of inodes each block

#define P_IBIT_BLOCKS 1
#define P_ABIT_BLOCKS (N_INODE_E_BLOCK * DATABL_INODE_RATIO)
#define P_INODE_BLOCKS (N_BIT_E_BLOCK * P_IBIT_BLOCKS)
#define P_DATA_BLOCKS (N_BIT_E_BLOCK * P_ABIT_BLOCKS)

#define GROUP_SIZE_BASE \
        (P_IBIT_BLOCKS + P_ABIT_BLOCKS + P_INODE_BLOCKS + P_DATA_BLOCKS)

#define GRP_HEAD_SZ (BOOT_SZ+SUPERBL_SZ)

#define SUPERBL_BEGIN BOOT_SZ
#define CONTENT_BEGIN (BOOT_SZ+SUPERBL_SZ)
#define IBIT_BEGIN (CONTENT_BEGIN + BLOCK_SZ*sb.ibit_offset)
#define ABIT_BEGIN (CONTENT_BEGIN + BLOCK_SZ*sb.abit_offset)
#define INODE_BEGIN (CONTENT_BEGIN + BLOCK_SZ*sb.inode_offset)
#define DATA_BEGIN (CONTENT_BEGIN + BLOCK_SZ*sb.data_offset)
#define INODE_SEC_SIZE (DATA_BEGIN - INODE_BEGIN)  

//Convert Inode Index to Inode Address in bytes
#define INODE_ADDR(IDX) (INODE_BEGIN + INODE_SZ * IDX)
//Convert Data Index to Data Address
#define DATA_ADDR(IDX) (DATA_BEGIN + BLOCK_SZ * IDX)
#define DATA_ADDR_O(IDX, OFFSET) (DATA_ADDR(IDX) + OFFSET * sizeof(int))
#define N_INDIR_PT (BLOCK_SZ / sizeof(int))


int cal_n_inode(int size);
int round_sz(int size);
int rnd2sm(int val, int base);

//fine!!
//Calculate actual bytes can be processed
int get_valid_size(int inode_idx, int pos, int bytes);
#endif	/* FILESYS_UTIL_H */

