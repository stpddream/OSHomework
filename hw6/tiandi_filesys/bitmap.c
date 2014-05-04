#include "bitmap.h"



/**
 * Turn on bit at offset
 */
int bm_on(char* map, int offset) {
    (*map) =  (1 << offset) | (*map);
    return 0;
}

/**
 * Turn off bit at offset
 */
int bm_off(char* map, int offset) {
    (*map) = (~(1 << offset)) & (*map);
    return 0;
}

/**
 * Get the first off bit in the one byte map
 * @param map
 * @return 
 */
int bm_get_free(char* map) {
    int offset;
    char byte = *map;
    for(offset = 0; offset < 8; offset++) {
        printf("looploop\n");
        printf("byte: %d\n", byte);
        if((byte & 1) == 1) return offset;
        byte = byte >> 1;
    }    
    return -1;
}


/**
 * Check if offset is on
 */
boolean bm_is_on(char* map, int offset) {
    return ((*map) >> offset & 1) == 1;
}
