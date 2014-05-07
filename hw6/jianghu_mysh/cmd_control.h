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
#include <termios.h>
#include "cmd_history.h"
#include "jobs.h"
#include "util.h"

#define NOT_INTERNAL_CMD -2

extern int mysh_terminal;
extern pid_t mysh_pgid;
extern struct termios mysh_tmodes;
extern sigset_t chld_mask;
int save_flag;

int exec_job(Job*);
int exec_bcmd(char**, int);
void b_exit();
int b_history();

void put_in_foreground(Job*);
void signal_wrapper(int, void*);
void sigchld_handler(int);
void sigtstp_handler(int);
void jobs_lock();
void jobs_unlock();

#endif	/* COMMAND_H */
