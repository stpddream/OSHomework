
#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include "test_mem.h"


int m_error;

int main(int argc, char** argv) {
    

    Mem_Init(8192);
    
    
    printf("============ Starting test =============\n");
        
    //check_for_eight_byte();
    //simple_8_byte_alloc();
    //aligned_alloc();
    odd_sized_alloc();

    /*
    Mem_Init(4096);
    
    Mem_Dump();
    
    printf("Before\n");
    Mem_Alloc(8);
    printf("In mem alloc\n");
    Mem_Alloc(500);   
    Mem_Dump();
    */
    
 
    //printf("Starting test\n");
    //odd_sized_alloc_free();   
    return 0;

}