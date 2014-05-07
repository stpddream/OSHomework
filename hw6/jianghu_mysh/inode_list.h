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

#include "../tiandi_filesys/filesys_hd.h"
#include "../tiandi_filesys/filesys.h"
#include "../tiandi_filesys/kernel_mem.h"

extern iList_node *iList_head, *iList_tail;    
    
typedef struct{
    iNode inode;
    struct iList_node* next;
}iList_node;    

int inode_append(int inode_idx);
int inode_remove_tail();
int gen_path(char* path);

#ifdef	__cplusplus
}
#endif

#endif	/* INODE_LIST_H */

