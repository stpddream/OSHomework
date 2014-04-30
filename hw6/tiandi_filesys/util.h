/* 
 * File:   util.h
 * Author: Sammy Guergachi <sguergachi at gmail.com>
 *
 * Created on April 28, 2014, 8:03 PM
 */

#ifndef UTIL_H
#define	UTIL_H

#include <stdio.h>
#include <string.h>

/* Boolean Type */
#define boolean int
#define TRUE 1
#define FALSE 0

#define MIN(A, B) (A > B) ? A : B

/* Display Functions */
const char *bytbi(int x);

#endif	/* UTIL_H */

