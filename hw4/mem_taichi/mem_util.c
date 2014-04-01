#include "mem_util.h"

int round_to(int val, int base) {   
    return (val / base) * base + base;   
}

int round_to_eight(int val) {
    return (((val - 1) >> 3) << 3) + 8;
}


MemRecord* get_block(void *ptr){
    char* tmp = ptr;
    return (ptr = tmp -= HEADER_SIZE);
}

int is_valid_addr(void* ptr){
    if((char* )ptr > (char* )head && (char* )ptr < (char* )head+memSize){
        return (ptr == (get_block(ptr))->mem_loc); //check if ptr corresponds to the mem_loc in the header
    }
    return 0; //return false
}

MemRecord* coalesce_block(MemRecord *ptr){
    //coalesce the current node with its next if the next exists and is free 
    if(ptr->next && ptr->next->status == MEM_FREE){
        ptr->size += (HEADER_SIZE + ptr->next->size);
        ptr->next = ptr->next->next;
        if(ptr->next)
            ptr->next->prev = ptr;
    }
    
    //coalesce the current node with its previous node if the previous exists and is free
    if(ptr->prev && ptr->prev->status == MEM_FREE){
        ptr->prev->size += (HEADER_SIZE+ptr->size);
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        return ptr->prev;
    }
    return ptr;
}

char* p_status(int status) {
    return (status == MEM_FREE) ? "free" : "occupied";
}

