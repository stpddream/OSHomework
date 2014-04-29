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
#define BOOT_SIZE 512
#define SUPERBL_SIZE 512
#define BLOCK_BASE 1024
#define DATABL_INODE_RATIO 8    /* Data Block to Inode ratio 8 : 1 */

/* Super Block Specification */
#define SIGN_SIZE 12

/* Inode Specification */
#define INODE_SIZE 128
#define N_DBLOCKS 10
#define N_IBLOCKS 4
#define FILE_NAME_MAX 14




#define DATA_BEGIN (BLOCK_BASE + sb.data_offset * BLOCK_SIZE)

#define INODE_ITEMS 25
#define INODE_BEGIN (BLOCK_BASE + sb.inode_offset * BLOCK_SIZE)
#define INODE_SEC_SIZE (DATA_BEGIN - INODE_BEGIN)  

#define BLOCK_SIZE sb.size

//Convert Inode Index to Inode Address in bytes
#define INODE_ADDR(IDX) (BLOCK_BASE + sb.inode_offset * BLOCK_SIZE + INODE_SIZE * IDX)

//Convert Data Index to Data Address
#define DATA_ADDR(IDX) (BLOCK_BASE + sb.data_offset * BLOCK_SIZE + IDX * BLOCK_SIZE)

#define DATA_ADDR_O(IDX, OFFSET) (DATA_ADDR(IDX) + OFFSET * sizeof(int))
#define N_INDIR_PT (BLOCK_SIZE / sizeof(int))

#define MIN(A, B) (A > B) ? A : B

typedef struct {    
    char have_fun[20];    
} Bootblock;

typedef struct {
    int system_type;    	/*magic number for file system*/
    char sign[SIGN_SIZE];    /* file system signature */


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
    int file_type;
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


#endif	/* FILESYS_H */

