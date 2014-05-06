/* 
 * File:   filetable.h
 * Author: Panda & Jacy
 *
 * Created on May 3, 2014, 11:03 PM
 */

#ifndef FILETABLE_H
#define	FILETABLE_H

#include <stdio.h>
#include "util.h"




int ft_init();
int ft_put(int inode_idx, int protection);
int ft_get_idx(int fd);
int ft_get_pos(int fd);
int ft_remove(int fd);
int ft_exist(int inode_idx);


#endif	/* FILETABLE_H */

