/* 
 * File:   device_hd.h
 * Author: Panda
 *
 * Created on May 3, 2014, 8:51 PM
 */

#ifndef DEVICE_HD_H
#define	DEVICE_HD_H

typedef struct {
    Bootblock bootblock;
    Superblock superblock;        
    FILE* phys_data;
} Dev;

#endif	/* DEVICE_HD_H */

