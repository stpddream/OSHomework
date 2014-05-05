#include "bitmap.h"


int ibit_on(Dev* device, int inode_idx) {    
    int byte_idx = inode_idx / 8;
    int offset = inode_idx % 8;
    return bit_turn(device, IBIT_BYTE_ADDR(byte_idx), offset, bm_on);
}

int ibit_off(Dev* device, int inode_idx) {
    int byte_idx = inode_idx / 8;
    int offset = inode_idx % 8;
    printf("byte idx: %d; offset: %d", byte_idx, offset);
    printf("ibit byte: %d\n", IBIT_BYTE_ADDR(byte_idx));
    
    return bit_turn(device, IBIT_BYTE_ADDR(byte_idx), offset, bm_off);
}

int bit_turn(Dev* device, int byte_addr, int offset, int (* func)(char*, int)) {
    char byte;    
    dev_read(&byte, sizeof(char), byte_addr, device);    
    func(&byte, offset);
    dev_write(&byte, sizeof(char), byte_addr, device);    
    return 0;    
}


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
