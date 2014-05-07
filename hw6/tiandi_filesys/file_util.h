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
#include "kernel_usr.h"
#include "filesys_hd.h"
#include "util.h"



int activate_inode(iNode* inode, int file_type, char* name);
int check_permission(iNode* inode, int mode);

#endif	/* FILE_UTIL_H */

