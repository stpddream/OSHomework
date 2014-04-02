#include "mem.h"


MemHead* mem_head;

int Mem_Init(int sizeOfRegion) {
    
    if(mem_head != NULL) return -1;
    
    if(sizeOfRegion <= 0) {
        m_error = E_BAD_ARGS;
        return -1;
    }
    
    
    size_t alloc_size = round_to(sizeOfRegion, MIN_BLOCK_SIZE) / MIN_BLOCK_SIZE * HEADER_SIZE + sizeOfRegion;
    
    size_t real_size = round_to(alloc_size + DAZONGGUAN_SIZE, getpagesize());    //round to page size
    
    if((mem_head = mmap(NULL, real_size, PROT_READ | PROT_WRITE, 
            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED) {
        m_error = E_NO_SPACE;
        return -1;
    }
    
    
    //Set up DA ZONG GUAN header
    mem_head->mem_alloc = 0;
    mem_head->mem_request = sizeOfRegion;
    mem_head->mem_size = real_size;
    
    printf("Size of initial %d", mem_head->mem_size);


    //Set up first block   
    mem_head->head = (MemRecord*)((char*)mem_head + DAZONGGUAN_SIZE);
    mem_head->head->status = MEM_FREE;
    mem_head->head->next = NULL;
    mem_head->head->prev = NULL;
    mem_head->head_free = mem_head->head;
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
    return (void*)choice->data;
          
}

int Mem_Free(void *ptr, int coalesce){
    if(ptr == NULL) return 0;
    //check if the pointer is a valid address
    if(is_valid_addr(ptr)){
        
        printf("hahahah\n");
        
        //get the header of the requested block
        MemRecord* current = get_block(ptr);
        if(current->status == MEM_OCCUPIED) mem_head->mem_alloc -= BLOCK_SIZE; 
        printf("ioioioi\n");
        //if coalesce, coalesce the previous and next block and update the link
        if(coalesce){            
            current = coalesce_block(current);
        }  
        //if it is already a free block, return success
        if(current->status == MEM_FREE) return 0;

        
        printf("hohohoh\n");
        //otherwise, set the status to be free, update the free list
        current->status = MEM_FREE;
         
        //traverse backwards to find the previous free node
        MemRecord* prevFree = current->prev;
        while(prevFree && prevFree->status != MEM_FREE){
            prevFree = prevFree->prev;
        }
        //update the free list link if prevFree is not NULL
        if(prevFree){
            if(!coalesce) current->nextFree = prevFree->nextFree;
            prevFree->nextFree = current;
        }else{
            //if there is no previous free node
            //then the current node is the head of the free list
            if(!coalesce) current->nextFree = mem_head->head_free;
            mem_head->head_free = current;
        }

        return 0;
    } else{
        return -1; // return failure, if given an invalid pointer
    }
}

void Mem_Dump() {
    
    MemRecord* current = mem_head->head;
    printf("/*********************MEMORY LIST************************/\n");
    while(current != NULL) {
         printf("=== Block ===\n");
         printf("Status: %s\n", p_status(current->status));
         printf("Size: %ld\n", BLOCK_SIZE);
         printf("=============>\n");
        
        current = current->next;
    }  
    
    current = mem_head->head_free;
    printf("/*********************FREE LIST************************/\n");
    while(current != NULL){
         printf("=== Block ===\n");
         printf("Status: %s\n", p_status(current->status));

         printf("Size: %ld\n", BLOCK_SIZE);
         printf("=============>\n");
        
        current = current->nextFree;
    }
}

int Mem_Destroy() {
   int size = mem_head->mem_size;
   int result = munmap(mem_head,size); 
   mem_head = NULL; //set the head pointer to NULL
   return result;
}
