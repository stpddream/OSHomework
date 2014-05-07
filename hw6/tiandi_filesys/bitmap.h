/* 
 * File:   bitmap.h
 * Author: Panda & Jacy
 *
 * Created on April 28, 2014, 11:27 AM
 */

/**
 * Helper class for organizing a single byte bitmap
 */



/**
 * Low level bitmap functionality
 */
#ifndef BITMAP_H
#define	BITMAP_H

#include "util.h"
#include "device_ctrl.h"

int ibit_on(Dev* device, int inode_idx);
int ibit_off(Dev* device, int inode_idx);
int ibit_is_on(Dev* device, int inode_idx);


int abit_on(Dev* device, int databl_idx);
int abit_off(Dev* device, int databl_idx);

int bit_turn(Dev* device, int inode_idx, int which_map, int (* func)(char*, int));
        
int bm_on(char* map, int offset);
int bm_off(char* map, int offset);
int bm_is_on(char* map, int offset);




#endif	/* BITMAP_H */

