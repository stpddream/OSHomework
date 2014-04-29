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
    /* num_inode_block * 8 + num_data_block * 8 + num_inode_block + num_data_block */    
    int base = GROUP_SIZE_BASE;
    printf("base is %d\n", base);
    return rnd2sm(size, base);
}

/**
 * Round val to the closest multiple smaller than val
 */
int rnd2sm(int val, int base) {   
    return (val / base) * base;
}




