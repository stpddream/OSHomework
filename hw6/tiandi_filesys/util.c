#include "util.h"

/**
 * Print a number is binary form
 * @param x number to print
 * @return character contains the binary form of a number
 */
const char *bytbi(int x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

/**
 * Turn all bytes on in an array
 */
void arr_on(char* arr, int size) {
    int i;
    for(i = 0; i < size; i++) {
        arr[i] = ~0;
    }    
}



// Debug functions
void print_ibit(Dev* device) {
    printf("=== Ibit === \n");
    int i;
    char ibit[BLOCK_SZ];
    fseek(device->phys_data, IBIT_BEGIN, SEEK_SET);
    fread(ibit, sizeof(ibit), 1, device->phys_data);   
    for(i = 0; i < BLOCK_SZ; i++) printf("%s ", bytbi(ibit[i]));
    printf("===      === \n");
}