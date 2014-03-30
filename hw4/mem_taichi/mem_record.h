/* 
 * File:   mem_record.h
 * Author: Panda
 *
 * Created on March 30, 2014, 2:08 PM
 */

#ifndef MEM_RECORD_H
#define	MEM_RECORD_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MEM_OCCUPIED 1
#define MEM_FREE 0
    
#define HEADER_SIZE 20
    
    typedef struct MemRecord_Node {
        int size;
        int status;
        void* mem_loc;
        struct MemRecord_Node* next;
        struct MemRecord_Node* prev;
        char data[1];      
    } MemRecord;    
    
    



#ifdef	__cplusplus
}
#endif

#endif	/* MEM_RECORD_H */

