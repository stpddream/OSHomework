#include "mem.h"


MemHead* mem_head;

int Mem_Init(int sizeOfRegion) {
    
    if(mem_head != NULL) return -1;
    
    if(sizeOfRegion <= 0) {
        m_error = E_BAD_ARGS;
        return -1;
    }
    
    size_t real_size = round_to(sizeOfRegion + HEADER_SIZE, getpagesize());    //round to page size
    
    if((mem_head = mmap(NULL, real_size, PROT_READ | PROT_WRITE, 
            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED) {
        m_error = E_NO_SPACE;
        return -1;
    }


    mem_head->head = mem_head;
    mem_head->head->status = MEM_FREE;
    mem_head->head->next = NULL;
    mem_head->head->prev = NULL;
    mem_head->head_free = mem_head->head;
    mem_head->head_free->prevFree = NULL;
    mem_head->head_free->nextFree = NULL;
   
    return 0;
    
}

void *Mem_Alloc(int size) {
    
    //Traverse the memory list    
    size = round_to_eight(size);
    MemRecord* current = mem_head->head;
    MemRecord* prev_free = NULL;
    MemRecord* choice = NULL;
    int max_size = -1;
    while(current != NULL) {
        
        if(BLOCK_SIZE > size && BLOCK_SIZE > max_size) {
            max_size = BLOCK_SIZE;
            prev_free = choice;
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
    if(max_size >= size + HEADER_SIZE + MIN_BLOCK_SIZE) {  
        
        choice->status = MEM_OCCUPIED;
        MemRecord* cur_next = choice->next;
        MemRecord* next_record = (MemRecord*)(choice->data + size);
                               
        next_record->next = cur_next;
        if(cur_next != NULL) cur_next->prev = next_record;
        
        next_record->prev = choice;
        next_record->status = MEM_FREE;
        next_record->nextFree = choice->nextFree;        
        
        if(prev_free != NULL) prev_free->nextFree = next_record;
        else mem_head->head_free = next_record;
                
        choice->next = next_record;    
        //choice->prev = remain the same
    }
    else {        
        if(prev_free == NULL) {
            mem_head->head_free = choice->nextFree;
        }        
    }
    choice->nextFree = NULL;
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
    
    MemRecord* current = mem_head;
    
     while(current != NULL) {
        
         printf("=== Block ===\n");
         printf("Status: %s\n", p_status(current->status));
         printf("Size: %d\n", BLOCK_SIZE);
         printf("=============>\n");
        
        current = current->next;
    }
    
    
    
}
