#ifndef __MEM_H_
#define __MEM_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include "mem_util.h"


#define E_NO_SPACE            1
#define E_CORRUPT_FREESPACE   2
#define E_PADDING_OVERWRITTEN 3
#define E_BAD_ARGS            4
#define E_BAD_POINTER         5
#define MIN_BLOCK_SIZE        8
#define BLOCK_SIZE (void*)(current->next) - current->mem_loc

extern int m_error;
extern int memSize;

MemHead* mem_head;



int Mem_Init(int sizeOfRegion);

void *Mem_Alloc(int size);

int Mem_Free(void *ptr, int coalesce);

void Mem_Dump();

#endif


