/* 
 * File:   bitmap.h
 * Author: Panda & Jacy
 *
 * Created on April 28, 2014, 11:27 AM
 */

/**
 * Helper class for organizing a single byte bitmap
 * 
 */



/**
 * Low level bitmap functionality
 */
#ifndef BITMAP_H
#define	BITMAP_H

#include "util.h"

int bm_on(char* map, int offset);
int bm_off(char* map, int offset);
boolean bm_is_on(char* map, int offset);




#endif	/* BITMAP_H */

