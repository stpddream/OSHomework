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
        dp->layers[0] = 0; //there is only one second layer indirect pointer, so it is always zero
        dp->layers[1] = data_pos / (N_PTR*BLOCK_SZ);
        remainder = data_pos % (N_PTR*BLOCK_SZ);
        dp->layers[2] = remainder /(BLOCK_SZ);
        dp->offset = remainder % BLOCK_SZ;
    } // if the position is within triple indirect blocks
    else if(pos >= I2BLOCK_SZ || pos < I3BLOCK_SZ){
        data_pos = pos - DBLOCK_SZ - IBLOCK_SZ - I2BLOCK_SZ; //there is only one third layer indirect pointer, so it is always zero
        dp->layers[0]  = 0;
        dp->layers[1] = data_pos/(N_PTR*N_PTR*BLOCK_SZ);
        remainder = data_pos % (N_PTR*N_PTR*BLOCK_SZ);
        dp->layers[2] = remainder / (N_PTR*BLOCK_SZ);
        remainder = remainder % (N_PTR*BLOCK_SZ);
        dp->layers[3] = remainder / BLOCK_SZ;
        dp->offset = remainder % BLOCK_SZ;
    } // if the position exceeds the triple indirect blocks
    else {
        return -1;
    }
    
    return 0;
}

/*
int inode_clr(iNode* node) {
    node->file_type = 0;
    node->permission = 0;
    node->nlink = 0;
    node->size = 0;
    node->uid
    
}*/


/**** Debug Printing ****/
/*
void superbl_print(Superblock* sb) {
    
    printf("==== Superblock ==== \n");
    printf("Num of inodes: %d\n", sb.inode_count);
    printf("Num of data blocks: %d\n", sb.block_count);
    
    printf("Num of free inodes: %d\n", sb.freeinode_count);
    printf("Num of free data blocks: %d\n", sb.freeblock_count);
  
    printf("Ibit offset: %d\n", sb.ibit_offset);
    printf("Abit offset: %d\n", sb.abit_offset);
    printf("Inode offset: %d\n", sb.inode_offset);
    printf("Data offset: %d\n", sb.data_offset);
    
    printf("Block size: %d\n", sb.block_size);
    printf("Disk size: %d\n", sb.size);
    printf("====    ====\n");
    
}*/