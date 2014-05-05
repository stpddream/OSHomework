#include "filesys_util.h"

/**
 * Calculate number of inode in disk of size size
 * @param size
 * @return 
 */
int cal_n_inode(int size) {
    int act_size = round_sz(size);
    printf("Actual disk size: %d\n", act_size);
    return act_size / GROUP_SIZE_BASE;    
}


/**
 * Calculate actual valid size of the disk
 * @param size
 * @return 
 */
int round_sz(int size) {    
    /* 1 byte has 8 bits */
    int base = GROUP_SIZE_BASE;
    printf("base is %d\n", base);
    return rnd2sm(size - GRP_HEAD_SZ, base) + GRP_HEAD_SZ;
}

/**
 * Round val to the closest multiple smaller than val
 */
int rnd2sm(int val, int base) {   
    return (val / base) * base;
}

int remain_bytes();

int find_data_ptr(iNode* inode, int pos, DataPos* dp){
    int remainder, data_pos;
    if(pos > inode->size || pos < 0) {
        return -1;
    }
        
    if(pos >= 0 && pos < DBLOCK_SZ) // if the position is within the direct blocks
    {
        dp->layers[0] = pos/BLOCK_SZ;
        dp->offset = pos % BLOCK_SZ;;
    } //if the position is within the indirect blocks
    else if(pos >= DBLOCK_SZ && pos < IBLOCK_SZ){
        data_pos = pos - DBLOCK_SZ;
        dp->layers[0] = data_pos/ (N_PTR*BLOCK_SZ);
        remainder = data_pos % (N_PTR*BLOCK_SZ);
        dp->layers[1] = remainder / BLOCK_SZ;
        dp->offset = remainder % BLOCK_SZ;
    } // if the position is within the second layer indirect blocks
    else if(pos >= IBLOCK_SZ && pos < I2BLOCK_SZ){
        data_pos = pos - DBLOCK_SZ - IBLOCK_SZ;
        dp->layers[0] = dapa_pos
        
    }
    
    return 0;
}
