
#include <stdio.h>
#include "mem.h"
#include "test_mem.h"

int m_error;

int main(int argc, char** argv) {
    
    Mem_Init(TOTAL_MEMORY);
    //MemHead m;
    //MemRecord r;

    printf("size = %ld\n", sizeof(MemHead));
    typedef struct{
        void* a;
        void* b;
        void* c;
        int d;
        char e[1];
    }Dummy;

    //Dummy d;

    Dummy* dtest = malloc(sizeof(Dummy));
    void* haha = (void*)dtest->e; 
    *((int*)haha) = 5;
    int* content = (int*)dtest->e;
    printf("ahoahohaohao %d", *content);


    Dummy* heihei = (Dummy*)dtest->e;
    heihei->d = 2223;

    Dummy* bigcontent = (Dummy*)dtest->e;

    printf("ioioioioio %d", bigcontent->d);

    printf("%ld\n", (char*)dtest - (char*)dtest->e);
    
 
    //printf("Starting test\n");
    //odd_sized_alloc_free();   

    return 0;
}
