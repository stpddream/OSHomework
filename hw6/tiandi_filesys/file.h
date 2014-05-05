/* 
 * File:   file.h
 * Author: Panda & Jacy
 *
 * Created on May 3, 2014, 10:35 PM
 */

#ifndef FILE_H
#define	FILE_H

#include <stdio.h>
#include <time.h>
#include "filesys_hd.h"


#define FT_FILE 1
#define FT_DIR 2
#define FT_MOUNT 3


int f_open(const char* path, const char* mode);
int f_read();
int f_write();
int f_close();
int f_seek();
int f_rewind();
int f_stat();
int f_remove();
int f_opendir();
int f_readdir();
int f_closedir();
int f_mkdir();
int f_rmdir();
int f_mount();
int f_umount();




#endif	/* FILE_H */

