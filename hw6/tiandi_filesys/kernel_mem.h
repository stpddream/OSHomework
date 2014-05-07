/* 
 * File:   kernel_mem.h
 * Author: Panda & Jacy
 *
 * Created on May 6, 2014, 11:39 AM
 */

#ifndef KERNEL_MEM_H
#define	KERNEL_MEM_H


#define UNAME_MAX_LEN

#include "device_ctrl.h"
#include "kernel_usr.h"

#define UP_SUPER 1
#define UP_REG 2


extern Dev* cur_dev;
extern User* cur_user;

void set_user(User* user);

#endif	/* KERNEL_MEM_H */

