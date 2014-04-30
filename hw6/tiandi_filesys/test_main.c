/* 
 * File:   test_main.c
 * Author: Panda & Jacy
 *
 * Created on April 28, 2014, 8:00 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "bitmap.h"
#include "util.h"
#include "diskio.h"
#include "filesys_util.h"
char n = 0;

/*
 * 
 */
int main(int argc, char** argv) {
    /*
    printf("new results\n");
    int i = 0;
    for(i = 0; i < 8; i++) {
        bm_on(&n, i);
        printf("first: n: %s\n", bytbi(n));        
    }
    
    for(i = 7; i >= 0; i--) {
        bm_off(&n, i);
        printf("second: n: %s\n", bytbi(n));                
    }*/
    
    /*
    printf("size round to \n");
    printf("Smallest multiple: %d", round_sz(512));
    
    int i;
    for(i = 0; i < 1000; i += 65) {
        printf("%d -> %d\n", i, round_sz(i));        
    }
    
    for(i = 0; i < 1000; i += 81) {
        printf("%d, ", i);
    }
    
    printf("\n");
    */
    
    FILE* fp;
    //fp = fopen("testfile/disk", "w");
    //init_disk(fp, 512);
    round_sz(512);

    
    printf("N_BIT_E_BLOCK: %d", N_BIT_E_BLOCK);
    
    return (EXIT_SUCCESS);
}

