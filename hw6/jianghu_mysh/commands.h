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

#include "libs/file.h"
#include "util.h"
#include "inode_list.h"
#include "libs/file.h"
#include "libs/ft_dir.h"
#include "util.h"


#define MAX_PATH_LEN 256


/**
 * Linux command more
 * @param 
 * @return 
 */

extern char cur_dir[MAX_PATH_LEN];

int cmd_more(char* content);
int cmd_cat(char* path);
int cmd_ls(char** args, int n_args);
int cmd_mkdir(char** dir_name, int n_args); 
int cmd_rmdir(char** dir_name, int n_args);
int cmd_cd(char* dir_name);
int cmd_pwd();
int cmd_rm(char** path, int n_args);
int cmd_chmod();

#endif	/* COMMANDS_H */

