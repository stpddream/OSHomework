
#include <stdio.h>
#include "mem.h"
#include "test_mem.h"

int m_error;

int main(int argc, char** argv) {
    
    Mem_Init(TOTAL_MEMORY);

    printf("Starting test\n");
    odd_sized_alloc_free();   

    return 0;
}
