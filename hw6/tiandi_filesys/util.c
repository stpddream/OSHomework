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
 * Clear an array. Assign all elements to 0
 */
void arr_clear(char* arr, int size) {
    int i;
    for(i = 0; i < size; i++) {
        arr[i] = 0;
    }    
}