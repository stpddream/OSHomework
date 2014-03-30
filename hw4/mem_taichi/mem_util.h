/* 
 * File:   util.h
 * Author: Panda & Jacy
 *
 * Created on March 30, 2014, 2:43 PM
 */

#ifndef UTIL_H
#define	UTIL_H

#define MEM_OCCUPIED 1
#define MEM_FREE 0
    
#define HEADER_SIZE sizeof(MemRecord)
    typedef struct MemRecord_Node {
        int size;
        int status;
        void* mem_loc;
        struct MemRecord_Node* next;
        struct MemRecord_Node* prev;
    } MemRecord;    


extern MemRecord* head;  
extern int memSize;
 
int round_to(int val, int base);
MemRecord* get_block(void*);
int is_valid_addr(void*);
MemRecord* coalesce_block(MemRecord*);

#endif	/* UTIL_H */

