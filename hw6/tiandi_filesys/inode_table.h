/* 
 * File:   inodetable.h
 * Author: Panda & Jacy
 *
 * Created on May 5, 2014, 11:37 AM
 */

#ifndef INODETABLE_H
#define	INODETABLE_H

#include "file_table.h"
#include "util.h"

extern iNodeTable inode_table;

typedef struct {
    iNode* inode;    
    int inode_idx;
} iNodeEntry;


typedef struct {
    iNodeEntry* entries[MAX_N_FILE_OPEN];    
    int size;
} iNodeTable;


int it_init();

int it_put(iNode* inode);

int it_exist(int inode_idx);

#endif	/* INODETABLE_H */

