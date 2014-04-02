#include "mem.h"


MemHead* mem_head;

int Mem_Init(int sizeOfRegion) {
    
    //If already init memory
    if(mem_head != NULL) return -1;
   
    //Invalid size 
    if(sizeOfRegion <= 0) {   
        m_error = E_BAD_ARGS;
        return -1;
    }
    

    //Calculate actual space needed 
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
    
    //Not enough memory
    if(size > mem_head->mem_request - mem_head->mem_alloc) {
        m_error = E_NO_SPACE;
        return NULL;
    }
    
    
    //Traverse the free list of memories
    size = round_to_eight(size);
    MemRecord* current = mem_head->head_free;
    MemRecord* prev_free = NULL;     //Choice's previous free block 
    MemRecord* choice = NULL;    //Memory block selected to alloc
    int max_size = -1;
    while(current != NULL) {
        
        //If block has enough free space, update max size and block
        if(BLOCK_SIZE > size && BLOCK_SIZE > max_size) {                 
            max_size = BLOCK_SIZE;
            prev_free = choice;
            choice = current;
        }
       
        current = current->nextFree;
    }
    
    //No block has enough memory to alloc
    if(max_size == -1) {
        printf("No space!!!\n");
        m_error = E_NO_SPACE;
        return NULL;
    }
    
    //If need to split
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
        else {
            mem_head->head_free = next_record;         
        }
                        
        choice->next = next_record;    
        //choice->prev = remain the same
    }
    
    //No need to split
    else {        
        //Check if need to update head of free list
        if(prev_free == NULL) {
            mem_head->head_free = choice->nextFree;
        }        
    }
    choice->nextFree = NULL;
    choice->status = MEM_OCCUPIED;
    mem_head->mem_alloc += size;
    return (void*)choice->data;
          
}

int Mem_Free(void *ptr, int coalesce){
    if(ptr == NULL) return 0;
    //check if the pointer is a valid address
    if(is_valid_addr(ptr)){             
        int cflag = 0;

        //get the header of the requested block
        MemRecord* current = get_block(ptr);
        if(current->status == MEM_OCCUPIED) mem_head->mem_alloc -= BLOCK_SIZE; 
     
        //if coalesce, coalesce the previous and next block and update the link
        if(coalesce){            
            int sizeBefore, sizeAfter;
            MemRecord* tmp = current;

            sizeBefore = BLOCK_SIZE;
            current = coalesce_block(current);
            sizeAfter = BLOCK_SIZE;
            
            cflag = (sizeAfter - sizeBefore == 0 || tmp != current);
        }  
        //if it is already a free block, return success
        if(current->status == MEM_FREE) return 0;

        //otherwise, set the status to be free, update the free list
        current->status = MEM_FREE;
         
        //traverse backwards to find the previous free node
        MemRecord* prevFree = current->prev;
        while(prevFree && prevFree->status != MEM_FREE){
            prevFree = prevFree->prev;
        }
        //update the free list link if prevFree is not NULL
        if(prevFree){
            if(!coalesce || cflag) current->nextFree = prevFree->nextFree;
            prevFree->nextFree = current;
        }else{
            //if there is no previous free node
            //then the current node is the head of the free list
            if(!coalesce || cflag) current->nextFree = mem_head->head_free;
            mem_head->head_free = current;
        }

        return 0;
    } else{
        return -1; // return failure, if given an invalid pointer
    }
}

void Mem_Dump() {
    
    MemRecord* current = mem_head->head;

    printf("[** MEMORY LIST **]\n");
    while(current != NULL) {
        printf("(%s, %ld)-->>  ", p_status(current->status), BLOCK_SIZE);
        current = current->next;
    }
    printf("\n\n");
    
    current = mem_head->head_free;
    printf("[** FREE LIST **]\n");
    while(current != NULL) {
        printf("(%s, %ld)-->> ", p_status(current->status), BLOCK_SIZE);
        current = current->nextFree;
    }
    printf("\n\n\n");
}

int Mem_Destroy() {   
   int size = mem_head->mem_size;
   int result = munmap(mem_head,size); 

   mem_head = NULL; //set the head pointer to NULL
   return result;
}
