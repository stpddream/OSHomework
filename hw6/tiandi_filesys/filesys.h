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
        

#define TIANDI_FS_ID 6666    /* Magic Number for tiandi filesystem */

/* File System Layout Specification */
#define BOOT_SZ 512
#define SUPERBL_SZ 512
#define DATABL_INODE_RATIO 4    /* Data Block to Inode ratio 4 : 1 */
#define BLOCK_SZ 512

/* Super Block Specification */
#define SIGN_SZ 12

/* Inode Specification */
#define INODE_SZ 128
#define N_DBLOCKS 10
#define N_IBLOCKS 4
#define FILE_NAME_MAX 14    /* Maximum file name length */

/* Low Level File System Functions */
int fs_init(Dev* device, int size);
int fs_remove_file(Dev* device, int inode_idx);

int fs_get_inode(iNode* node, int inode_idx, Dev* device);
int fs_alloc_inode(Dev* device);
int fs_dealloc_inode(Dev* device, int inode_idx);
int fs_update_inode(iNode* node, int inode_idx, Dev* device);


int fs_alloc_databl(Dev* device);

/* File Manipulation Functions */
/** Seek from offset from the beginning */
int fl_read(Dev* device, iNode* inode, int pos, int bytes, char* data);
int fl_write(Dev* device, iNode* inode, int pos, int bytes, char* data);




#endif	/* FILESYS_H */

