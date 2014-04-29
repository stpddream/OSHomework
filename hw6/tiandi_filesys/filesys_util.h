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
/* num_inode_block * 8 + num_data_block * 8 + num_inode_block + num_data_block */    
#define GROUP_SIZE_BASE (8 + 8 * DATABL_INODE_RATIO + 1 + DATABL_INODE_RATIO) 


int cal_n_inode(int size);
int round_sz(int size);
int rnd2sm(int val, int base);

#endif	/* FILESYS_UTIL_H */

