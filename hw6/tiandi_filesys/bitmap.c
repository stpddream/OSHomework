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
 * Check if offset is on
 */
boolean bm_is_on(char* map, int offset) {
    return ((*map) >> offset & 1) == 1;
}
