#include "filesys_util.h"

/**
 * Calculate number of inode in disk of size size
 * @param size
 * @return 
 */
int cal_n_ibit_blocks(int size) {
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
    printf("base is %d\n", GROUP_SIZE_BASE);
    return rnd2sm(size - GRP_HEAD_SZ, GROUP_SIZE_BASE) + GRP_HEAD_SZ;
}

/**
 * Round val to the closest multiple smaller than val
 */
int rnd2sm(int val, int base) {   
    return (val / base) * base;
}








/*
int inode_clr(iNode* node) {
    node->file_type = 0;
    node->permission = 0;
    node->nlink = 0;
    node->size = 0;
    node->uid
    
}*/




