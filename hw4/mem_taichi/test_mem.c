#include "test_mem.h"
int check_for_eight_byte() {
    int result = 0;
    printf("==== Check for eight byte test ====\n");
    Mem_Init(4096);
    Mem_Alloc(200);
    
    printf("End of Test\n");
    return result;
}

int simple_8_byte_alloc() {
    int result = 0;
    printf("==== Simple eight byte alloc test ====\n");
    
    printf("End of Test\n");

    return result;

}

/* TEST 09: Aligned allocation and free */
int aligned_alloc_free(){
    int result = 0;
    printf("==== Initialize and round up to one page test ====\n");
    
    void* test1 = Mem_Alloc(8);
    void* test2 = Mem_Alloc(32);
    void* test3 = Mem_Alloc(16);
    void* test4 = Mem_Alloc(256);
    void* test5 = Mem_Alloc(8);
    
    Mem_Dump();

    Mem_Free(test1, 1);
    Mem_Free(test5, 1);
    Mem_Free(test4, 1);
    Mem_Free(test2, 1);
    Mem_Free(test3, 1);

    Mem_Dump();
     

    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    printf("End of Test\n");

    return result;
}

/* TEST 10: odd-sized-allocation and free */
int odd_sized_alloc_free(){
    int result = 0;
    printf("==== Odd sized allocation and free test ====\n");
    
    void* test1 = Mem_Alloc(3);
    void* test2 = Mem_Alloc(119);
    void* test3 = Mem_Alloc(1);
    void* test4 = Mem_Alloc(89);
    void* test5 = Mem_Alloc(39);
    
    Mem_Dump();

    Mem_Free(test2, 1);
    Mem_Free(test3, 1);
    Mem_Free(test5, 1);
    Mem_Free(test4, 1);
    Mem_Free(test1, 1);

    Mem_Dump();
    
    printf("End of Test\n");

    return result;
}

/* TEST 11: initialize with size of one page */
int init_size_one_page(){
    int result = 0;
    printf("==== Initialize with size of one page test ====\n");
    
    int pagesize = getpagesize();
    Mem_Init(pagesize);
    int real_size = (pagesize/MIN_BLOCK_SIZE+1)*HEADER_SIZE+pagesize;
    result = (mem_head->memSize == (real_size/pagesize+1)*pagesize ? TEST_SUCCESS : TEST_FAIL);

    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    printf("End of Test\n");

    return result;
}

/* TEST 12: initialize and round up to one page */
int init_size_round_one_page(){
    int result = 0;
    printf("==== Initialize and round up to one page test ====\n");
    
    Mem_Init(1024);
    int real_size = (1024/MIN_BLOCK_SIZE+1)*HEADER_SIZE+1024;
    int pagesize = getpagesize();
    result = (mem_head->memSize == (real_size/pagesize+1)*pagesize ? TEST_SUCCESS : TEST_FAIL);

    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    printf("End of Test\n");

    return result;
}

/* TEST 13: no space left to allocate */
int no_space_left_allocate(){
    int result = 0;
    printf("==== No space left allocation test ====\n");
    
    void* request = Mem_Alloc(TOTAL_MEMORY+1);
    p_merror(merror); 

    printf("End of Test\n");

    return result;
}

/* TEST 14: try to free a NULL pointer */
int free_null(){
    int result = 0;
    printf("==== Free NULL pointer test ====\n");
    
    result = (Mem_Free(NULL, 0) == 0 ? TEST_SUCCESS : TEST_FAIL);
    
    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    printf("End of Test\n");
    return result;
}

/* TEST 15: check that memory can be written to an allocation*/
int check_memory_written_after_allocation(){
     int result = 0;
    printf("==== No space left allocation test ====\n");
    
    int* testInt = Mem_Alloc(sizeof(int));
    testInt[0] = 1;
    printf("Wrote Integer: %d\n", testInt[0]);
    Mem_Dump();
    Mem_Free(testInt, 1);
   
    printf("End of Test\n");

    return result;   
}

