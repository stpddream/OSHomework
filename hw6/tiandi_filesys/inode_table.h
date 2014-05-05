/* 
 * File:   inodetable.h
 * Author: Panda & Jacy
 *
 * Created on May 5, 2014, 11:37 AM
 */

#ifndef INODETABLE_H
#define	INODETABLE_H


#include "util.h"
#include "tables_hd.h"

extern iNodeTable inode_table;


void it_init();

int it_put(iNode* inode);
int it_remove(int inode_idx);
iNode* it_get_node(int inode_idx);

int it_exist(int inode_idx);

#endif	/* INODETABLE_H */

