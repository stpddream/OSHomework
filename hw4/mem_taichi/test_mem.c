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

/* TEST 09: Aligned allocation and free */
int aligned_alloc_free(){
    int result;
    printf("==== Initialize and round up to one page test ====\n");
    


    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    printf("End of Test\n");

    return result;
}

/* TEST 10: odd-sized-allocation and free */
int odd_sized_alloc_free(){
    int result;
    printf("==== Odd sized allocation and free test ====\n");
    


    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    printf("End of Test\n");

    return result;
}

/* TEST 11: initialize with size of one page */
int init_size_one_page(){
    int result;
    printf("==== Initialize with size of one page test ====\n");
    


    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    printf("End of Test\n");

    return result;
}

/* TEST 12: initialize and round up to one page */
int init_size_round_one_page(){
    int result;
    printf("==== Initialize and round up to one page test ====\n");

        


    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    printf("End of Test\n");

    return result;
}

/* TEST 13: no space left to allocate */
int no_space_left_allocate(){
    int result;
    printf("==== No space left allocation test ====\n");
    
    void* request = Mem_Alloc(TOTAL_MEMORY+1);
    result = (request == NULL? TEST_SUCCESS : TEST_FAIL); 

    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    printf("End of Test\n");

    return result;
}

/* TEST 14: try to free a NULL pointer */
int free_null(){
    int result;
    printf("==== Free NULL pointer test ====\n");
    
    result = (Mem_Free(NULL) == 0 ? TEST_SUCCESS : TEST_FAIL);
    
    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    printf("End of Test\n");
    return result;
}

/* TEST 15: check that memory can be written to an allocation*/
int check_memory_written_after_allocation(){
     int result;
    printf("==== No space left allocation test ====\n");
    


    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    printf("End of Test\n");

    return result;   
}

