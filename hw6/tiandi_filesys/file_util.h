/* 
 * File:   file_util.h
 * Author: Panda & Jacy
 *
 * Created on May 3, 2014, 10:51 PM
 */

#ifndef FILE_UTIL_H
#define	FILE_UTIL_H

#include <string.h>
#include <time.h>
#include "filesys_hd.h"



char* parse_path(char* path);
int activate_inode(iNode* inode, int file_type, char* name);

#endif	/* FILE_UTIL_H */

