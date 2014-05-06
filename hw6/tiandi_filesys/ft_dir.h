/* 
 * File:   ft_dir.h
 * Author: Panda & Jacy
 *
 * Created on April 29, 2014, 9:12 PM
 */

#ifndef FT_DIR_H
#define	FT_DIR_H

#include "filesys.h"

#define DIR_ENTRY_SZ 16

typedef struct {
    char file_name[FILE_NAME_MAX];
    int inode_idx;
} DirFileEntry;

int dir_add(iNode* dir_inode, int inode_file_idx, char* name);
int dir_lookup(iNode* dir_inode, char* file_name);
int dir_remove_file(iNode* inode, int dir_inode_idx, int inode_file_idx);

/* Debug */
void list_dir(iNode* node);
//int zanshimeile();


#endif	/* FT_DIR_H */

