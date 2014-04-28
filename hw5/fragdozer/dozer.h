#ifndef DOZER_H
#define DOZER_H

#include "dwriter.h"
#include "dreader.h"
#include <stdio.h>
#include <stdlib.h>
#include "filesys.h"



extern int inode_begin, inode_end;
extern Superblock sb;
extern FILE* fp_w;
extern FILE* fp_r;


void doze(iNode* inode);
int copy_datai(int idx);

int get_inode_by_addr(int, iNode*);
int get_inode_by_index(int, iNode*);
int is_free_inode(int);
int next_inode(int);
int next_occupied_inode(int);

#endif