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

#include "sh_util.h"
#include "inode_list.h"
#include "file.h"
#include "ft_dir.h"


/**
 * Linux command more
 * @param 
 * @return 
 */

extern char cur_dir[MAX_PATH_LEN];

int cmd_more(char* content);
int cmd_cat(int fd);
int cmd_ls(char* flags);
int cmd_mkdir(char* dir_name);
int cmd_rmdir(char* dir_name);
int cmd_cd(char* dir_name);
int cmd_pwd();
int cmd_rm(char* path);
int cmd_chmod();

#endif	/* COMMANDS_H */

