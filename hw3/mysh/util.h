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
#include <sys/wait.h>
#include <sys/types.h>

#define TRUE 1
#define FALSE 0

/* command id */
#define KILL 1
#define FG 2
#define BG 3



int mod(int, int);
void print_cmd(char**);
int cmd_compare(char**, char**);
char* substring(char*, int, int);
int int_valueof(char*, int*);
void print_usage(int);

void exit_clean();
#endif	/* UTIL_H */

