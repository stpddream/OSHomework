#include "mem_util.h"

int round_to(int val, int base) {   
    return ((val - 1) / base) * base + base;   
}

int round_to_eight(int val) {
    return (((val - 1) >> 3) << 3) + 8;
}

/* return the address of the header of the requsted bock */
MemRecord* get_block(void *ptr){
    char* tmp = ptr;
    return (ptr = tmp -= HEADER_SIZE);
}

/* checks if a given pointer is a valided malloced block */
int is_valid_addr(void* ptr){
    if((char* )ptr > (char* )mem_head->head && (char* )ptr < (char* )mem_head->head+mem_head->mem_size){
        return (ptr == (void*)(get_block(ptr))->data); //check if ptr corresponds to the mem_loc in the header
    }
    return 0; //return false
}

/* coalesce the freed block */
MemRecord* coalesce_block(MemRecord *ptr){
    //coalesce the current node with its next if the next exists and is free 
    if(ptr->next && ptr->next->status == MEM_FREE){
       
        ptr->nextFree = ptr->next->nextFree;
       
       
        ptr->next = ptr->next->next;
        if(ptr->next) ptr->next->prev = ptr;
       
     
    }
    
    //coalesce the current node with its previous node if the previous exists and is free
    if(ptr->prev && ptr->prev->status == MEM_FREE) {
               
        ptr->prev->nextFree = ptr->nextFree; 
        ptr->prev->next = ptr->next;
        if(ptr->next) ptr->next->prev = ptr->prev;              
        
        return ptr->prev;
    }

    return ptr;
}

char* p_status(int status) {
    return (status == MEM_FREE) ? "free" : "occupied";
}

char* p_merror(int m_error) {
   
    
    switch(m_error) {
        case E_NO_SPACE:
            return "No space!!!!!\n";
            break;
            
        case E_CORRUPT_FREESPACE:
            return "Corrupt free space error!!!!!\n";
            break;
            
        case E_PADDING_OVERWRITTEN:
            return "Padding Overwritten error!!!!!\n";
            break;
            
        case E_BAD_ARGS:
            return "Bad arguments error\n";
            break;
            
        case E_BAD_POINTER:
            return "Bad pointer error!!!!!!\n";
            break;
            
        default:
            printf("To do or not to do....\n");
            break;
    }
    return "";
}

