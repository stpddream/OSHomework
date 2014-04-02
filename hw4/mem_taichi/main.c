
#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include "test_mem.h"


int m_error;

int main(int argc, char** argv) {
    
    Mem_Init(TOTAL_MEMORY);
    
    printf("~~~~~~~~~~~~~~ Everything starts here ~~~~~~~~~~~~~~~\n\n\n");
    
    //Start Running Tests
    check_for_eight_byte();
    simple_8_byte_alloc();
    aligned_alloc();
    odd_sized_alloc();
    bad_args_to_mem_init();
    worst_fit_alloc();
    coalesce_of_space();
    simple_alloc_free();
    aligned_alloc_free();
    odd_sized_alloc_free();
    init_size_one_page();
    init_size_round_one_page();
    no_space_left_allocate();
    free_null();
    check_memory_written_after_allocation();
    
    printf("Success!\n");

    return 0;

}
