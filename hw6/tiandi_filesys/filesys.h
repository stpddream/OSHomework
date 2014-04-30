/* 
 * File:   filesys.h
 * Author: Panda & Jacy
 */

#ifndef FILESYS_H
#define	FILESYS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define TIANDI_FS_ID 6666    /* Magic Number for tiandi filesystem */

/* File System Layout Specification */
#define BOOT_SZ 512
#define SUPERBL_SZ 512
#define BLOCK_BASE 1024
#define DATABL_INODE_RATIO 4    /* Data Block to Inode ratio 4 : 1 */
#define BLOCK_SZ 512

/* Super Block Specification */
#define SIGN_SZ 12

/* Inode Specification */
#define INODE_SZ 128
#define N_DBLOCKS 10
#define N_IBLOCKS 4
#define FILE_NAME_MAX 14    /* Maximum file name length */





typedef struct {    
    char have_fun[20];    
} Bootblock;

typedef struct {
    int system_type;    	/*magic number for file system*/
    char sign[SIGN_SZ];    /* file system signature */


    int size; 		/* size of blocks in bytes */
    int inode_offset; 	/* offset of inode region in blocks */
    int data_offset; 	/* data region offset in blocks */

    int ibit_offset;	/* inode bitmap region offset in blocks*/
    int abit_offset;	/* allocation bitmap region offset in block */
    int swap_offset; 	/* swap region offset in blocks */

    // Counts
    int inode_count;  	/* Number of total inodes */
    int block_count;  	/* Number of total blocks */
    int freeinode_count;	/* Number of free inodes */
    int freeblock_count; 	/* Number of total free blocks */

} Superblock;


typedef struct {
    int file_type;              /* File Type */
    int permission; 		/* file permission field */
    int nlink; 			/* number of links to this file */
    int size; 			/* numer of bytes in file */
    int uid; 			/* owner's user ID */
    int gid; 			/* owner's group ID */
    int ctime; 			/* change time */
    int mtime; 			/* modification time */
    int atime; 			/* access time */
    int dblocks[N_DBLOCKS]; 	/* pointers to data blocks */
    int iblocks[N_IBLOCKS]; 	/* pointers to indirect blocks */
    int i2block; 			/* pointer to doubly indirect block */
    int i3block; 			/* pointer to triply indirect block */

    char name[FILE_NAME_MAX];       /* file name */
} iNode;



/* Low Level File System Functions */
int fs_init(FILE* group, int size);
int fs_remove_file(int inode_idx);

iNode* fs_get_inode(int inode_idx);
int fs_alloc_inode();
int fs_update_inode(int inode_idx, iNode* node);

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

