/* 
 * File:   filetable.h
 * Author: Panda & Jacy
 *
 * Created on May 3, 2014, 11:03 PM
 */

#ifndef FILETABLE_H
#define	FILETABLE_H

#include <stdio.h>
#include "util.h"

#define MAX_N_FILE_OPEN 20


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


int ft_init();
int ft_put(int inode_idx, int protection);
int ft_remove(int fd);
int ft_exist(int inode_idx);


#endif	/* FILETABLE_H */

