/* 
 * File:   cat.h
 * Author: Sammy Guergachi <sguergachi at gmail.com>
 *
 * Created on February 9, 2014, 9:02 PM
 */

#ifndef CAT_H
#define	CAT_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFF_SZ 100

#define APP_ON 1
#define APP_OFF 0

int cat(char*, char*, int);

#endif	/* CAT_H */

