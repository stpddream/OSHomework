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

/**
 * update the bitmap by turning on and off bits given a index
 * @param bm_begin the beginning index of the bitmap
 * @param idx the position of the bit to be updated in the bitmap
 * @param action turn on or turn off bits
 * @return 
 */
void bm_update(FILE* fp, int bm_begin, int idx, int action){
    char byte;
    int pos = idx / 8;
    int offset = idx % 8;
    
    fseek(fp, bm_begin+pos, SEEK_SET);
    fread(&byte, 1, 1, fp);
    if(action == BM_ON){
        bm_on(byte, offset);
    }else if(action == BM_OFF){
        bm_off(byte, offset);
    }
    fwrite(byte, 1, 1, fp);
}
