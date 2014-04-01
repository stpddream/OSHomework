#include "mem.h"


int initflg;    //Whether Mem_Init has been called
MemHead* head;



int Mem_Init(int sizeOfRegion) {
    
    if(head != NULL) return -1;
    
    if(sizeOfRegion <= 0) {
        m_error = E_BAD_ARGS;
        return -1;
    }
    
    size_t real_size = round_to(sizeOfRegion + HEADER_SIZE, getpagesize());    //round to page size
    
    if((head = mmap(NULL, real_size, PROT_READ | PROT_WRITE, 
            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED) {
        m_error = E_NO_SPACE;
        return -1;
    }


    head-> = head->data;

    head->next = NULL;
    head->prev = NULL;
    head->status = MEM_FREE;
   
    return 0;
    
}

void *Mem_Alloc(int size) {
    
    //Traverse the memory list    
    size = round_to_eight(size);
    MemRecord* current = head;
    MemRecord* choice = NULL;
    int max_size = -1;
    while(current != NULL) {
        
        if(current->size > size && current->size > max_size) {
            max_size = current->size;
            choice = current;
        }
        
        current = current->next;
    }
    
    if(max_size == -1) {
        m_error = E_NO_SPACE;
        return NULL;
    }
    
    //Alloc Space
    
    //Not enough space for split
    if(max_size >= size + HEADER_SIZE + 8) {  
        
        choice->status = MEM_OCCUPIED;
        MemRecord* cur_next = choice->next;
        MemRecord* next_record = (MemRecord*)(choice->data + size);
        
        next_record->size = choice->size - HEADER_SIZE - size;
        choice->size = size;
                        
        next_record->next = cur_next;
        next_record->prev = choice;
        next_record->status = MEM_FREE;
        if(next_record->next != NULL) next_record->next->prev = next_record;
        choice->next = next_record;        
    }
    choice->status = MEM_OCCUPIED;
    return choice->mem_loc;
          
}

int Mem_Free(void *ptr, int coalesce){
    //check if the pointer is a valid address
    if(is_valid_addr(ptr)){
        //get the block of address, mark it free
        MemRecord* block = get_block(ptr);
        block->status = MEM_FREE;
         
        //coalesce the previous and next block
        if(coalesce){
            coalesce_block(block);
        }
        return 0;
    } else{
        return -1; // return failure
    }
}

void Mem_Dump() {
    
    MemRecord* current = head;
    
     while(current != NULL) {
        
         printf("=== Block ===\n");
         printf("Status: %s\n", p_status(current->status));
         printf("Size: %d\n", current->size);
         printf("=============>\n");
        
        current = current->next;
    }
    
    
    
}
