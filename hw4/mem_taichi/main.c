
#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include "test_mem.h"


int m_error;

int main(int argc, char** argv) {
    

    Mem_Init(8192);
    
    printf("~~~~~~~~~~~~~~ Everything starts here ~~~~~~~~~~~~~~~\n");
    
   

        
    //check_for_eight_byte();
    //simple_8_byte_alloc();
    //aligned_alloc();
    //odd_sized_alloc();
    //bad_args_to_mem_init();
    //worst_fit_alloc();
    coalesce_of_space();
    //simple_alloc_free();
    //no_space_left_allocate();
    //init_size_one_page();
    //free_null();
    //check_memory_written_after_allocation();    
 
    return 0;

}
