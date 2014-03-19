/* 
 * Project: mysh
 * File:   command.h
 * Author: Panda
 *
 * Created on February 17, 2014, 9:34 PM
 * 
 * Contains command execution functionality
 */

#ifndef COMMAND_H
#define	COMMAND_H

#include <signal.h>
#include <string.h>
#include "cmd_history.h"
#include "jobs.h"
#include "util.h"

#define NOT_INTERNAL_CMD -2


int save_flag;

int exec_sh(char**, int, char*);
int exec_bcmd(char**, int);
int b_exit();
int b_history();


void signal_wrapper(int signum, void*  handler);
void sigchld_handler(int sig);
void sigtstp_handler(int sig);

#endif	/* COMMAND_H */
