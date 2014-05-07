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

#define UP_SUPER 1
#define UP_REG 2

extern Dev* cur_dev;
/*
typedef struct {
    char name[UNAME_MAX_LEN];
    int privilege;    
} User;
*/



#endif	/* KERNEL_MEM_H */

