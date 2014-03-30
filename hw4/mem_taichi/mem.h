#ifndef __MEM_H_
#define __MEM_H_

#include <unistd.h>
#include <sys/mman.h>
#include "mem_util.h"


#define E_NO_SPACE            1
#define E_CORRUPT_FREESPACE   2
#define E_PADDING_OVERWRITTEN 3
#define E_BAD_ARGS            4
#define E_BAD_POINTER         5






extern int m_error;
extern int memSize;

MemRecord* head;
int initflg;


int Mem_Init(int sizeOfRegion);

void *Mem_Alloc(int size);

int Mem_Free(void *ptr, int coalesce);

void Mem_Dump();

#endif


