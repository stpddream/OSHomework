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
#include <string.h>
#include "filesys_hd.h"
#include "file_table.h"
#include "inode_table.h"
#include "file_util.h"
#include "ft_dir.h"

#define FT_FILE 1
#define FT_DIR 2
#define FT_MOUNT 3

#define FP_READ 1
#define FP_WRITE 1 << 1
#define FP_APPEND 1 << 2


int f_open(char* path, const char* mode);
int f_read(void* ptr, size_t size, size_t nmemb, int fd);
int f_write(void* ptr, size_t size, size_t nmemb, int fd);
int f_close(int fd);
int f_seek(int fd, long offset, int whence);
int f_rewind(int fd);
int f_stat(int fd, char* buf);
int f_remove();
DirStream* f_opendir(char* path);
int f_readdir(DirStream* ds, DirFileEntry* entry);
int f_closedir(DirStream* ds);
int f_mkdir(char* path);
int f_rmdir();
int f_mount();
int f_umount();




#endif	/* FILE_H */

