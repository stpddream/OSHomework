/* 
 * File:   inode_list.h
 * Author: jacyli
 *
 * Created on May 6, 2014, 9:42 PM
 */

#ifndef INODE_LIST_H
#define	INODE_LIST_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "filesys_hd.h"
#include "filesys.h"
#include "kernel_mem.h"

typedef struct iList_node_{
    iNode inode;
    int inode_idx;
    struct iList_node_ *next;
}iList_node;    

extern iList_node *iList_head, *iList_tail;    
    
int inode_append(int inode_idx);
int inode_remove_tail();
int gen_path(char* path);

#ifdef	__cplusplus
}
#endif

#endif	/* INODE_LIST_H */

