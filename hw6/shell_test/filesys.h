/* 
 * File:   filesys.h
 * Author: Panda & Jacy
 */

#ifndef FILESYS_H
#define	FILESYS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filesys_util.h"
#include "filesys_hd.h"
#include "util.h"
#include "device_ctrl.h"
        

/* Low Level File System Functions */
int fs_init(Dev* device, int size);
int fs_remove_file(Dev* device, int inode_idx);

int fs_get_inode(iNode* node, int inode_idx, Dev* device);
int fs_alloc_inode(Dev* device);
int fs_dealloc_inode(Dev* device, int inode_idx);
int fs_update_inode(iNode* node, int inode_idx, Dev* device);

int fs_alloc_databl(Dev* device);
int fs_dealloc_databl(Dev* device, int databl_idx);

/* File Manipulation Functions */
/** Seek from offset from the beginning */
int fl_read(Dev* device, iNode* inode, int pos, int bytes, void* data);
int fl_write(Dev* device, iNode* inode, int pos, int bytes, void* data);




#endif	/* FILESYS_H */

