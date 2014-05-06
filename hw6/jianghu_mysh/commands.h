/* 
 * File:   commands.h
 * Author: Panda & Jacy 
 *
 * Created on May 3, 2014, 11:30 PM
 */

#ifndef COMMANDS_H
#define	COMMANDS_H

#include <sys/ioctl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>


/**
 * Linux command more
 * @param 
 * @return 
 */
int more(char* content);
int cat(int fd);


#endif	/* COMMANDS_H */

