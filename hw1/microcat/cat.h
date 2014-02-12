/* 
 * File:   cat.h
 * Author: Sammy Guergachi <sguergachi at gmail.com>
 *
 * Created on February 9, 2014, 9:02 PM
 */

#ifndef CAT_H
#define	CAT_H


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUFF_SZ 100

int cat(char*, char*);

#endif	/* CAT_H */

