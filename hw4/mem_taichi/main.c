
#include <stdio.h>
#include "mem.h"

int m_error;

int main(int argc, char** argv) {
    printf("Init Memory\n");
        
    Mem_Init(4096);
    
    Mem_Dump();
    
    printf("Before\n");
    Mem_Alloc(8);
    printf("In mem alloc\n");
    Mem_Alloc(500);   
    Mem_Dump();
    
    
    return 0;
}