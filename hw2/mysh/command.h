
/* 
 * Project: mysh
 * File:   command.h
 * Author: Panda
 *
 * Created on February 17, 2014, 9:34 PM
 */

#ifndef COMMAND_H
#define	COMMAND_H

#include <signal.h>

#include "cmd_history.h"

int save_flag;

int exec_sh(char*, char**);
int exec_bcmd(char*, char**);
int b_exit();
int b_history();

#endif	/* COMMAND_H */
