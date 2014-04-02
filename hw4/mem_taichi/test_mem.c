#include "test_mem.h"
int check_for_eight_byte() {
    int result = 0;
    printf("==== Check for eight byte test ====\n");
    
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


/* Test 03 Aligned Alloc*/
int aligned_alloc() {
 
    void* pt1 = Mem_Alloc(8);
    Mem_Dump();
    void* pt2 = Mem_Alloc(16);
    Mem_Dump();
    void* pt3 = Mem_Alloc(24);
    Mem_Dump();
    
    Mem_Free(pt1, 1);
    Mem_Free(pt2, 1);
    Mem_Free(pt3, 1);
            
    
    
    return 0;

}


/* Test 04 Odd Size Allocation */
int odd_sized_alloc() {
    void* pt1 = Mem_Alloc(2222);
    Mem_Dump();
    void* pt2 = Mem_Alloc(3333);
    Mem_Dump();
    void* pt3 = Mem_Alloc(1);
    Mem_Dump();
    void* pt4 = Mem_Alloc(88);
    
    Mem_Free(pt1, 1);
    Mem_Free(pt2, 1);
    Mem_Free(pt3, 1);
    Mem_Free(pt4, 1);
    Mem_Dump();
    
    return 0;
    
}



/* Test 06 */
int bad_args_to_mem_init() {
    
    //Re mem init
    Mem_Init(-200);
    printf("Error: %s", p_merror(m_error));
    Mem_Init(0);
    printf("Error: %s", p_merror(m_error));
    
    return 0;
}




/* Test 07: Coalesce free space */
int worst_fit_alloc() {
    
    void* pt1 = Mem_Alloc(4096);
    void* pt2 = Mem_Alloc(8);
    void* pt3 = Mem_Alloc(512);
        
    Mem_Free(pt1, 0);
    Mem_Free(pt3, 0);
    
    Mem_Dump();
        
    void* pt4 = Mem_Alloc(128);
    
    Mem_Free(pt4, 0);    
    Mem_Free(pt2, 0);
    
    return 0;
    
    
    
}




/* Test 07: Coalesce free space */
int coalesce_of_space() {
    
    void* pt = Mem_Alloc(8);
    Mem_Dump();
    Mem_Free(pt, 1);
    Mem_Dump();
    
    return 0;
    
}






/* Test 08: Simple Allocation and Free */
int simple_alloc_free() {
    
    void* pt = Mem_Alloc(1);
    Mem_Dump();
    Mem_Free(pt, 0);
    Mem_Dump();
    
    return 0;
    
}










/* TEST 09: Aligned allocation and free */
int aligned_alloc_free(){
    int result = 0;
    printf("==== Initialize and round up to one page test ====\n");
    


    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    printf("End of Test\n");

    return result;
}

/* TEST 10: odd-sized-allocation and free */
int odd_sized_alloc_free(){
    int result = 0;
    printf("==== Odd sized allocation and free test ====\n");
    


    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    printf("End of Test\n");

    return result;
}

/* TEST 11: initialize with size of one page */
int init_size_one_page(){
    int result = 0;
    printf("==== Initialize with size of one page test ====\n");
    


    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    printf("End of Test\n");

    return result;
}

/* TEST 12: initialize and round up to one page */
int init_size_round_one_page(){
    int result = 0;
    printf("==== Initialize and round up to one page test ====\n");

        


    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    printf("End of Test\n");

    return result;
}

/* TEST 13: no space left to allocate */
int no_space_left_allocate(){
    int result = 0;
    printf("==== No space left allocation test ====\n");
    
    void* request = Mem_Alloc(TOTAL_MEMORY+1);
    result = (request == NULL? TEST_SUCCESS : TEST_FAIL); 

    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
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
    


    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    printf("End of Test\n");

    return result;   
}

