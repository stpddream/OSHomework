/* 
 * File:   tables_hd.h
 * Author: Panda & Jacy
 *
 * Created on May 5, 2014, 6:43 PM
 */

#ifndef TABLES_HD_H
#define	TABLES_HD_H

#define MAX_N_FILE_OPEN 20


/***** Inode Table Header *****/

typedef struct {
    iNode* inode;    
    int inode_idx;
} iNodeEntry;


typedef struct {
    iNodeEntry* entries[MAX_N_FILE_OPEN];    
    int size;
} iNodeTable;


/***** File Table Headers *****/

typedef struct {   
    int inode_idx;
    int pos;
    int protection;
} FileEntry;


typedef struct {
    FileEntry* entries[MAX_N_FILE_OPEN];
    int size;
    int alloc_hd;
} FileTable;

#endif	/* TABLES_HD_H */

