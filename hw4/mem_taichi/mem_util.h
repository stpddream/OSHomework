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
    
#define HEADER_SIZE 20


typedef struct MemRecord_Node {
    int status;
    void* mem_loc;
    struct MemRecord_Node* next;
    struct MemRecord_Node* prev;       
    struct MemRecord_Node* nextFree;
    char data[1];
} MemRecord;    


typedef struct ListInfo_Node {
    MemRecord* head;
    MemRecord* head_free;
    int MemSize;
    int MemAlloc;
} MemHead;

extern MemRecord* mem_head;  
 
int round_to(int val, int base);
int round_to_eight(int val);
MemRecord* get_block(void*);
int is_valid_addr(void*);
MemRecord* coalesce_block(MemRecord*);
char* p_status(int status);

#endif	/* UTIL_H */
