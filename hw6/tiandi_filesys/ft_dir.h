/* 
 * File:   ft_dir.h
 * Author: Panda & Jacy
 *
 * Created on April 29, 2014, 9:12 PM
 */

#ifndef FT_DIR_H
#define	FT_DIR_H

#include "filesys.h"



typedef struct {
    char file_name[FILE_NAME_MAX];
    int inode_idx;
} DirFileEntry;

int dir_add_file(int inode_dir_idx, int inode_file_idx);
int dir_remove_file(int inode_dir_idx, int inode_file_idx);
//int zanshimeile();


#endif	/* FT_DIR_H */

