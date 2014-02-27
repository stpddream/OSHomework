/* 
 * Project: mysh
 * File:   util.h
 * Author: Panda
 *
 * Created on February 17, 2014, 11:12 PM
 */

#ifndef UTIL_H
#define	UTIL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mod(int, int);
void print_cmd(char**);
int cmd_compare(char**, char**);
char* substring(char*, int, int);

#endif	/* UTIL_H */

