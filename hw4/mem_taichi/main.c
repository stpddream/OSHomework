
#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#include "test_mem.h"


int m_error;

int main(int argc, char** argv) {
    

    Mem_Init(8192);
    
    
    printf("============ Starting test =============\n");
    aligned_alloc_free();
    return 0;

}
