/* 
 * File:   filesys.h
 * Author: Panda & Jacy
 */

#ifndef FILESYS_H
#define	FILESYS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "filesys_hd.h"
#include "filesys_util.h"
#include "util.h"
#include "device_ctrl.h"
        

/* Low Level File System Functions */
int fs_init(Dev* device, int size);
int fs_remove_file(int inode_idx);

int fs_get_inode(iNode* node, int inode_idx, Dev* device);
int fs_alloc_inode(Dev* device);
int fs_dealloc_inode(Dev* device, int inode_idx);
int fs_update_inode(iNode* node, int inode_idx, Dev* device);

/* File Manipulation Functions */

/** Seek from offset from the beginning */
int fl_seek(int inode_idx, int offset);
int fl_read(int inode_idx, int pos, int bytes, char* data);
int fl_write(int inode_idx, int pos, int bytes, char* data);




/* Inode Manipulation Functions */


/** Consider util *//////////////


/** Look for next inode and return inode number */ 


//////////////////////////////







#endif	/* FILESYS_H */

