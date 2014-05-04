#include "filesys.h"


/**
 * Init file system on disk
 * Disk file should be already initialized to the correct size
 * @param disk disk file
 * @param size size of disk, in bytes
 * @return 
 */
int fs_init(Dev* device, int size) {
    /* Disk Arrangements */
    int n_ibit_blocks = cal_n_ibit_blocks(size);
    int n_abit_blocks = n_ibit_blocks * P_ABIT_BLOCKS;
    int n_inode_blocks = n_ibit_blocks * P_INODE_BLOCKS;
    int n_datablocks = n_ibit_blocks * P_DATA_BLOCKS;
   
    int n_inodes = n_inode_blocks * N_INODE_E_BLOCK;
    
    int act_size = round_sz(size);
    printf("Actual size of disk %d\n", act_size);
    printf("Ibit blocks %d\n", n_ibit_blocks);
    
    /* Init Bootblock */
    device->bootblock.fun = 8888;
    strcpy(device->bootblock.have_fun, "Hidden Virus!!!!");
    
    /* Write Bootblock */
    fseek(device->phys_data, 0, SEEK_SET);
    fwrite(&device->bootblock, sizeof(Bootblock), 1, device->phys_data);
    
    /* Init Superblock */    
    Superblock superb;
    device->superblock.system_type = TIANDI_FS_ID;
    
    /** Counts **/
    device->superblock.inode_count = n_inodes;
    device->superblock.freeinode_count = n_inodes;
    device->superblock.freeblock_count = n_datablocks;
    device->superblock.block_count = n_datablocks;
    
    /** offsets **/
    device->superblock.ibit_offset = 0;
    device->superblock.abit_offset = n_ibit_blocks;
    device->superblock.inode_offset = superb.abit_offset + n_abit_blocks;
    device->superblock.data_offset = superb.inode_offset + n_inode_blocks;
    device->superblock.swap_offset = -1; //Invalid    
    device->superblock.size = act_size;
    
       
    fseek(device->phys_data, SUPERBL_BEGIN, SEEK_SET);
    fwrite(&device->superblock, sizeof(device->superblock), 1, device->phys_data);
    
    char bit_block[BLOCK_SZ];
    arr_on(bit_block, BLOCK_SZ);
       
    fseek(device->phys_data, IBIT_BEGIN, SEEK_SET);
    
    /* Init Bitmap */
    int i;
    for(i = 0; i < n_ibit_blocks; i++) {
        fwrite(bit_block, sizeof(bit_block), 1, device->phys_data);        
    }
        
    
    /* Alloc Bitmap */
    for(i = 0; i < n_abit_blocks; i++) {
        fwrite(bit_block, sizeof(bit_block), 1, device->phys_data);
    }
    
    printf("abit begin: %d\n", ABIT_BEGIN);
    printf("Content begin: %d\n", CONTENT_BEGIN);
        
    /* Inode Block */   
    iNode empty_node;
    empty_node.nlink = 100;        

    for(i = 0; i < n_inodes; i++) {
        fseek(device->phys_data, INODE_ADDR(i), SEEK_SET);
        empty_node.file_type = i + 1;
        fwrite(&empty_node, sizeof(empty_node), 1, device->phys_data);
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

/**
 * Get inode from disk
 * @param node (need user to allocate memory)
 * @param group disk group
 * @param inode_idx 
 * @return 0 if success
 */
int fs_get_inode(iNode* node, int inode_idx, Dev* device) {        
    dev_read(node, INODE_SZ, INODE_ADDR(inode_idx), device);
    return 0;
}

/** Optimize: read a chunk at a time **/
int fs_alloc_inode(Dev* device) {
    if(device->superblock.freeinode_count <= 0) return -1;
    
    int bcnt;
    int offset;
    char byte; 
    
    // Check bytes
    while(bcnt <= (device->superblock.inode_count / 8)) {
      dev_read(&byte, sizeof(char), IBIT_BYTE_ADDR(bcnt), device);
      if(byte != 0) break;
      bcnt++;
    }
    
    
    bm_off(&byte, offset);    //Mark as occupied    
    dev_write(&byte, sizeof(char), IBIT_BYTE_ADDR(bcnt), device);
    printf("byte: %s; offset: %d\n", bytbi(byte), offset);
    return IBIT_IDX(byte, offset);     
}


/**
 * Write an inode into disk
 */
int fs_update_inode(iNode* node, int inode_idx, Dev* device) {
    fseek(device->phys_data, INODE_ADDR(inode_idx), SEEK_SET);
    fwrite(node, INODE_SZ, 1, device->phys_data);
    return 0;
}


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