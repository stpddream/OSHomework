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
#define P_INODE_BLOCKS (N_BIT_E_BLOCK * P_IBIT_BLOCKS / N_INODE_E_BLOCK)
#define P_DATA_BLOCKS (DATABL_INODE_RATIO * N_INODE_E_BLOCK) * P_INODE_BLOCKS

#define GROUP_SIZE_BASE \
        (P_IBIT_BLOCKS + P_ABIT_BLOCKS + P_INODE_BLOCKS + P_DATA_BLOCKS)


/** blablablabalbal */

#define DATA_BEGIN (BLOCK_BASE + sb.data_offset * BLOCK_SZ)

#define INODE_BEGIN (BLOCK_BASE + sb.inode_offset * BLOCK_SZ)
#define INODE_SEC_SIZE (DATA_BEGIN - INODE_BEGIN)  

//Convert Inode Index to Inode Address in bytes
#define INODE_ADDR(IDX) (BLOCK_BASE + sb.inode_offset * BLOCK_SZ + INODE_SZ * IDX)

//Convert Data Index to Data Address
#define DATA_ADDR(IDX) (BLOCK_BASE + sb.data_offset * BLOCK_SZ + IDX * BLOCK_SZ)

#define DATA_ADDR_O(IDX, OFFSET) (DATA_ADDR(IDX) + OFFSET * sizeof(int))
#define N_INDIR_PT (BLOCK_SZ / sizeof(int))


/****8 blablabalba */


/** Helper Constants */
#define GRP_HEAD_SZ (BOOT_SZ + SUPERBL_SZ)



int cal_n_ibit_blocks(int size);
int round_sz(int size);
int rnd2sm(int val, int base);

//fine!!
//Calculate actual bytes can be processed
int get_valid_size(int inode_idx, int pos, int bytes);
#endif	/* FILESYS_UTIL_H */

