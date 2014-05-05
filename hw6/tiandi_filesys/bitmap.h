/* 
 * File:   bitmap.h
 * Author: Panda & Jacy
 *
 * Created on April 28, 2014, 11:27 AM
 */

/**
 * Low level bitmap functionality
 */
#ifndef BITMAP_H
#define	BITMAP_H

#include "util.h"

#define BM_OFF 0
#define BM_ON 1

int bm_on(char* map, int offset);
int bm_off(char* map, int offset);
boolean bm_is_on(char* map, int offset);
void bm_update(FILE* fp, int bm_begin, int idx, int action);




#endif	/* BITMAP_H */

