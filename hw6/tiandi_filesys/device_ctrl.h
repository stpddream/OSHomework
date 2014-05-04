/* 
 * File:   diskio.h
 * Author: Panda & Jacy
 *
 * Created on April 28, 2014, 10:08 PM
 */

#ifndef DISKIO_H
#define	DISKIO_H

#include <stdio.h>
#include <stdlib.h>
#include "filesys_hd.h"
#include "device_hd.h"


Dev* dev_create(FILE* disk);


int dev_init(Dev* device, int size);
int dev_read(void* data, int size, int pos, Dev* device);

#endif	/* DISKIO_H */

