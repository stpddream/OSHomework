/* 
 * File:   filesys.h
 * Author: Panda & Jacy
 */

#ifndef FILESYS_HD_H
#define	FILESYS_HD_H

#define TIANDI_FS_ID 6666    /* Magic Number for tiandi filesystem */

/* File System Layout Specification */

#define BOOT_SZ 512             /* Size of Boot block: 512 byets */
#define SUPERBL_SZ 512          /* Size of Super block: 512 bytes */
#define DATABL_INODE_RATIO 4    /* Data Block to Inode ratio 4 : 1 */
#define BLOCK_SZ 512            /* Block size: 512 bytes */

/* Super Block Specification */
#define SIGN_SZ 12

/* Inode Specification */
#define INODE_SZ 128        /* Inodo size: 128 bytes */
#define N_DBLOCKS 10
#define N_IBLOCKS 4
#define FILE_NAME_MAX 14    /* Maximum file name length */

typedef struct {  
    int fun;
    char have_fun[20];    
} Bootblock;

typedef struct {
    int system_type;    	/*magic number for file system*/
    char sign[SIGN_SZ];    /* file system signature */


    int block_size; 		/* size of blocks in bytes */
    int size;           /* Disk size */
    
    
    int inode_offset; 	/* offset of inode region in blocks */
    int data_offset; 	/* data region offset in blocks */

    int ibit_offset;	/* inode bitmap region offset in blocks*/
    int abit_offset;	/* allocation bitmap region offset in block */
    int swap_offset; 	/* swap region offset in blocks */

    // Counts
    int inode_count;  	/* Number of total inodes */
    int databl_count;  	/* Number of total data blocks */
    int freeinode_count;	/* Number of free inodes */
    int freeblock_count; 	/* Number of total free data blocks */
    
    int inode_alloc_hd;    /* Head of inode allocated, in bytes */
    int data_alloc_hd;    /* Head of data block allocated, in bytes */

} Superblock;


typedef struct {
    int file_type;              /* File Type */
    int permission; 		/* file permission field */
    int nlink; 			/* number of links to this file */
    int size; 			/* number of bytes in file */
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

typedef struct{
    //indicator showing if the position is within the direct blocks, indirect blocks
    //double indirect or triple indirect
    int size_range;
    int layers[4];
    int offset;
}DataPos;

#endif	/* FILESYS_HD_H */

