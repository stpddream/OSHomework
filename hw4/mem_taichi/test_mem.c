#include "test_mem.h"

/* Test 01 Check for Eight byte Alignment */
int check_for_eight_byte() {
    printf("==== Check for eight byte test ====\n");
    
    Mem_Dump();
    printf("Alloc p\n");
    void* p = Mem_Alloc(200);
    Mem_Dump();
    printf("Address: %p\n", p);
    
    printf("Free p\n");
    Mem_Free(p, 1);
    
    Mem_Dump();
    
    end_test();
    
    return 0;
}

/* Test 02 Simple Eight Byte */
int simple_8_byte_alloc() {
    int result = 0;
    printf("==== Simple eight byte alloc test ====\n");
    
    action("Initial");
    Mem_Dump();
    
    action("Alloc pt");
    void* pt = Mem_Alloc(8);
    Mem_Dump();
    
    action("Free pt");
    Mem_Free(pt, 1);
    Mem_Dump();
    
    end_test();
    return result;

}


/* Test 03 Aligned Alloc*/
int aligned_alloc() {
    
    printf("==== Alligned Allocation Test ====\n");

 
    action("alloc pt1");
    void* pt1 = Mem_Alloc(8);
    Mem_Dump();
    
    action("alloc pt2");
    void* pt2 = Mem_Alloc(16);
    Mem_Dump();
    
    action("alloc pt3");
    void* pt3 = Mem_Alloc(24);
    Mem_Dump();
    
    
    Mem_Free(pt1, 1);
    Mem_Free(pt2, 1);
    Mem_Free(pt3, 1);            
    
    
    return 0;

}


/* Test 04 Odd Size Allocation */
int odd_sized_alloc() {
    
    printf("==== Odd Size Allocation Test ====\n");

    
    action("alloc pt1");
    void* pt1 = Mem_Alloc(2222);
    Mem_Dump();
    
    action("alloc pt2");
    void* pt2 = Mem_Alloc(3333);
    Mem_Dump();
    
    action("alloc pt3");
    void* pt3 = Mem_Alloc(1);
    Mem_Dump();
    
    action("alloc pt4");
    void* pt4 = Mem_Alloc(88);
    Mem_Dump();
    
    Mem_Free(pt1, 1);
    Mem_Free(pt2, 1);
    Mem_Free(pt3, 1);
    Mem_Free(pt4, 1);
//    Mem_Dump();
    
    end_test();
    return 0;
    
}



/* Test 06 */
int bad_args_to_mem_init() {
    

    printf("==== Bad Args to Mem Test ====\n");
    Mem_Destroy();
   
    //Re mem init
    Mem_Init(-200);
    printf("Error: %s", p_merror(m_error));
    Mem_Init(0);
    printf("Error: %s", p_merror(m_error));
    
    end_test();
    
    return 0;
}




/* Test 07: Coalesce free space */
int worst_fit_alloc() {
    

    printf("==== Worst Fit Allocation Test ====\n");

    action("alloc pt1");

    void* pt1 = Mem_Alloc(4096);
    void* pt2 = Mem_Alloc(8);
    void* pt3 = Mem_Alloc(512);
        
    Mem_Free(pt1, 0);
    Mem_Free(pt3, 0);
    
    Mem_Dump();
        
    void* pt4 = Mem_Alloc(128);
    
    Mem_Free(pt4, 0);    
    Mem_Free(pt2, 0);
    
    end_test();
    
    return 0;
    
    
    
}




/* Test 07: Coalesce free space */
int coalesce_of_space() {
    

    printf("==== Coalesce free space Test ====\n");
    
    action("alloc pt1, pt2, pt3, pt4, pt5");
    void* pt1 = Mem_Alloc(8);        
    void* pt2 = Mem_Alloc(10);
    void* pt3 = Mem_Alloc(20);
    void* pt4 = Mem_Alloc(40);
    void* pt5 = Mem_Alloc(23);
    Mem_Dump();
    
    action("free pt 2, pt 4");
    Mem_Free(pt2, 1);
    Mem_Free(pt4, 1);
    Mem_Dump();
    
    action("free 3 coal!");
    Mem_Free(pt3, 1);
    Mem_Dump();
    
    action("free 1 no coal");
    Mem_Free(pt1, 0);
    Mem_Dump();
    
    //Clean up
    Mem_Free(pt5, 1);
    Mem_Free(pt1, 1);
    
    end_test();
    return 0;
    
}






/* Test 08: Simple Allocation and Free */
int simple_alloc_free() {
    
    printf("==== Simple Allocation and Free Test ====\n");

    
    action("alloc pt to 1");

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
    
    action("TEST 9: Malloc ptr1(8), ptr2(32), ptr3(16), ptr4(256)");
    void* test1 = Mem_Alloc(8);
    void* test2 = Mem_Alloc(32);
    void* test3 = Mem_Alloc(16);
    void* test4 = Mem_Alloc(256);
    
    Mem_Dump();

    action("Free ptr1, coalesce = False");
    Mem_Free(test1, 0);
    Mem_Dump();

    action("Free ptr4(256), coalesce = False");
    Mem_Free(test4, 0);
    Mem_Dump();

    action("Free ptr2(32), coalesce = False");
    Mem_Free(test2, 0);
    Mem_Dump();

    action("Free ptr3(16), coalesce = False");
    Mem_Free(test3, 0);
    Mem_Dump();
     
    action("Coalesce everything");
    Mem_Free(test1,1);
    Mem_Free(test2,1);
    Mem_Free(test3,1);
    Mem_Free(test4,1);
    Mem_Dump();
    printf("End of Test\n");

    return result;
}

/* TEST 10: odd-sized-allocation and free */
int odd_sized_alloc_free(){
    
    int result = 0;
    printf("==== Initialize and round up to one page test ====\n");
    
    action("TEST 9: Malloc ptr1(3), ptr2(119), ptr3(1), ptr4(89), ptr5(37)");
    void* test1 = Mem_Alloc(3);
    void* test2 = Mem_Alloc(119);
    void* test3 = Mem_Alloc(1);
    void* test4 = Mem_Alloc(89);
    void* test5 = Mem_Alloc(37);
    
    Mem_Dump();
    
    action("Free ptr3(1), coalesce = False");
    Mem_Free(test3, 0);
    action("Free ptr1(3), coalesce = False");
    Mem_Free(test1, 0);
    action("Free ptr5(37), coalesce = True");
    Mem_Free(test5, 1);
    action("Free ptr4(89), coalesce = False");
    Mem_Free(test4, 0);
    action("Free ptr2(119), coalesce = True");
    Mem_Free(test2, 1);
    
    Mem_Dump();
     
    action("Coalesce everything");
    Mem_Free(test1,1);
    Mem_Free(test2,1);
    Mem_Free(test3,1);
    Mem_Free(test4,1);
    Mem_Free(test5,1);

    Mem_Dump();
    
    printf("End of Test\n");
    
    return result;
}

/* TEST 11: initialize with size of one page */
int init_size_one_page(){
    int result = 0;
    printf("==== Initialize with size of one page test ====\n");
    
    int pagesize = getpagesize();
    action("Request to Mem_Init(pageSize)");
    printf("Page Size = %d\n", pagesize);
    Mem_Init(pagesize);
    int real_size = (pagesize/MIN_BLOCK_SIZE+1)*HEADER_SIZE+pagesize;
    int desired_size =  (real_size/pagesize+1)*pagesize;
    printf("Actual Size Requested: %d\n", mem_head->mem_size);
    printf("Desired Size Requested: %d\n", desired_size);

    result = (mem_head->mem_size == desired_size ? TEST_SUCCESS : TEST_FAIL);

    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    action("End of Test\n");

    return result;
}

/* TEST 12: initialize and round up to one page */
int init_size_round_one_page(){
    int result = 0;
    printf("==== Initialize and round up to one page test ====\n");
    
    action("Request to Mem_Init(1024)");
    Mem_Init(1024);
    int real_size = (1024/MIN_BLOCK_SIZE+1)*HEADER_SIZE+1024;
    int pagesize = getpagesize();
    int desired_size = (real_size/pagesize+1)*pagesize;
    
    printf("Actual Size Requested: %d\n", mem_head->mem_size);
    printf("Page Size : %d\n", pagesize);
    printf("Desired Size Requested: %d\n", desired_size);

    result = (mem_head->mem_size == desired_size ? TEST_SUCCESS : TEST_FAIL);

    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    action("End of Test");

    return result;
}

/* TEST 13: no space left to allocate */
int no_space_left_allocate(){
    int result = 0;
    printf("==== No space left allocation test ====\n");
    
    void* request = Mem_Alloc(TOTAL_MEMORY+1);
    result = (request == NULL ? TEST_SUCCESS : TEST_FAIL);
    printf("Malloc Fail: %s\n", p_merror(m_error)); 

    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    action("End of Test");

    return result;
}

/* TEST 14: try to free a NULL pointer */
int free_null(){
    int result = 0;
    printf("==== Free NULL pointer test ====\n");
    
    result = (Mem_Free(NULL, 0) == 0 ? TEST_SUCCESS : TEST_FAIL);
    
    printf("%s!\n", (result == TEST_SUCCESS? "TEST SUCCESS" : "TEST FAIL"));
    
    end_test();
    return result;
}

/* TEST 15: check that memory can be written to an allocation*/
int check_memory_written_after_allocation(){
     int result = 0;
    printf("==== Check Memory writte after allocation test ====\n");
    
    action("alloc testInt to integer size");
    int* testInt = Mem_Alloc(sizeof(int));
    testInt[0] = 32767;
    printf("Wrote Integer: %d\n", testInt[0]);
    Mem_Dump();    
    Mem_Free(testInt, 1);
   
    end_test();
    return result;   
}

void end_test() {    
    printf("========== End of Test ==========\n\n\n");
}

void action(char* action) {
    printf("|------> %s <------|\n", action);
}
