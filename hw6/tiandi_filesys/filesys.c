#include "filesys.h"

/*SUPERBLOOOOOOOOOOOOOOOCL*/
Superblock sb;
/*SUPERBLOOOOOOOOOOOOOOOCL*/

/**
 * Init file system on disk
 * Disk file should be already initialized to the correct size
 * @param disk disk file
 * @param size size of disk, in bytes
 * @return 
 */
int fs_init(FILE* group, int size) {
    /* Disk Arrangements */
    int n_ibit_blocks = cal_n_ibit_blocks(size);
    int n_abit_blocks = n_ibit_blocks * P_ABIT_BLOCKS;
    int n_inode_blocks = n_ibit_blocks * P_INODE_BLOCKS;
    int n_datablocks = n_ibit_blocks * P_DATA_BLOCKS;
   
    int n_inodes = n_inode_blocks * N_INODE_E_BLOCK;
    
    int act_size = round_sz(size);
    printf("Actual size of disk %d\n", act_size);
    
    /* Init Bootblock */
    Bootblock bootblock;
    bootblock.fun = 1111;
    strcpy(bootblock.have_fun, "Hidden Virus!!!!");
    
    /* Write Superblock */
    fseek(group, 0, SEEK_SET);
    fwrite(&bootblock, sizeof(bootblock), 1, group);
    return 0;  
    
    /* Init Superblock */    
    Superblock superblock;
    superblock.system_type = TIANDI_FS_ID;
    
    /** Counts **/
    superblock.inode_count = n_inodes;
    superblock.freeinode_count = n_inodes;
    superblock.freeblock_count = n_datablocks;
    superblock.block_count = n_datablocks;
    
    /** offsets **/
    superblock.ibit_offset = 0;
    superblock.abit_offset = n_ibit_blocks;
    superblock.inode_offset = superblock.abit_offset + n_abit_blocks;
    superblock.data_offset = superblock.inode_offset + n_inode_blocks;
    superblock.swap_offset = -1; //Invalid    
    superblock.size = act_size;


  
    int superblock_offset = BOOT_SZ;
    fseek(group, superblock_offset, SEEK_SET);
    fwrite(&superblock, sizeof(superblock), 1, group);
    
    
    char bit_block[BLOCK_SZ];
    arr_clear(bit_block, BLOCK_SZ);
    
    /* Init Bitmap */
    int i;
    for(i = 0; i < n_ibit_blocks; i++) {
        fwrite(bit_block, sizeof(bit_block), 1, group);        
    }
        
    /* Alloc Bitmap */
    for(i = 0; i < n_abit_blocks; i++) {
        fwrite(bit_block, sizeof(bit_block), 1, group);
    }
    
    /* Inode Block */
    iNode empty_node;
    empty_node.nlink = 0;
    
    for(i = 0; i < n_inodes; i++) {
        fwrite(&empty_node, sizeof(empty_node), 1, group);
    }
     
    /* Data Block */
    //Nothing needs to do
    return 0;
}




/**
 * unlink inode, clears all parameters within the given 
 * @param inode_idx
 * @return 0 if success
 */
int fs_remove_file(int inode_idx){
    
}

iNode* fs_get_inode(int inode_idx);
int fs_alloc_inode();
int fs_update_inode(int inode_idx, iNode* node);


/**
 * Read data from file
 * @param inode_idx index of inode for file to read
 * @param pos starting read position
 * @param bytes number of bytes to read
 * @param data 
 * @return number of bytes read
 */
int fl_read(int inode_idx, int pos, int bytes, char* data) {
    
    
    
}