/* 
 * File:   util.h
 * Author: Panda & Jacy
 *
 * Created on April 11, 2014, 5:02 PM
 */

#ifndef UTIL_H
#define	UTIL_H

#define DEFAULT_BUF_SIZE 512*128
#define FLEX_BUF_FLAG -1
#define DEFAULT_BUF_FLAG 1

#include "dozer.h"
#include <unistd.h>




void print_inode(iNode* inode, int detail);
void printUsage();
size_t getTotalSysMem();
size_t get_buf_size();
void arr_clear(int* arr, int size);

#endif	/* UTIL_H */

