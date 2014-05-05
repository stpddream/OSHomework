/* 
 * File:   util.h
 * Author: Panda & Jacy
 *
 * Created on April 28, 2014, 8:03 PM
 */

#ifndef UTIL_H
#define	UTIL_H

#include <stdio.h>
#include <string.h>
#include "filesys_hd.h"
#include "filesys_util.h"
#include "device_hd.h"

/* Boolean Type */
#define boolean int
#define TRUE 1
#define FALSE 0

#define MIN(A, B) (A > B) ? A : B

/* Display Functions */
const char *bytbi(int x);



/* Clear an array: all item to 0 */
void arr_on(char* arr, int size);

/* Debug printing */
void print_superblock(Superblock* sb);
void print_ibit(Dev* device);
#endif	/* UTIL_H */

