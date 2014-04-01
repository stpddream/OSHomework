#include "test_mem.h"
int check_for_eight_byte() {

    printf("==== Check for eight byte test ====\n");
    Mem_Init(4096);
    Mem_Alloc(200);
    
    printf("End of Test\n");
    return 0;
}

int simple_8_byte_alloc() {
    printf("==== Simple eight byte alloc test ====\n");
    
    printf("End of Test\n");

    

}
