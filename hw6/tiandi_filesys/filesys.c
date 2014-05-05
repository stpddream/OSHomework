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
    device->superblock.databl_count = n_datablocks;
    
    /** offsets **/
    device->superblock.ibit_offset = 0;
    device->superblock.abit_offset = n_ibit_blocks;
    device->superblock.inode_offset = superb.abit_offset + n_abit_blocks;
    device->superblock.data_offset = superb.inode_offset + n_inode_blocks;
    device->superblock.swap_offset = -1; //Invalid    
    device->superblock.size = act_size;
    device->superblock.inode_alloc_hd = 0;
    device->superblock.data_alloc_hd = 0;
    
       
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
/*int fs_remove_file(Dev* device, int inode_idx){
    // turn off the bit in the inode bitmap
    FILE* fp = device->phys_data;
    int i, j, k, abit_idx, dblock_start;
    int dblock[N_PTR];
    int dblock2[N_PTR];
    int dblock3[N_PTR];
    DataPos dp;

    
    //turn off the bit in the inode bitmap
    ibit_off(device, inode_idx);
    
    // clear all the bits in the inode
    iNode inode;
    fseek(fp, INODE_ADDR(inode_idx), SEEK_SET);
    fread(&inode, INODE_SZ, 1, fp);
    
    find_data_ptr(&inode, inode->size, &dp);
    
    //if the size of the file exceeds the direct blocks
    if(dp->size_range > DP_DBLOCK){
        //clear the data blocks pointed by dblock
        for(i = 0; i < N_DBLOCKS; i++){
            abit_idx = inode.dblocks[i];
            bm_update(fp, ABIT_BEGIN, abit_idx, BM_OFF);
        }
        
        if(dp->size_range > DP_IBLOCK){
            //clear the data blocks storing the indirect pointers
            for(i = 0; i < N_IBLOCKS; i++){
                //get block
                dblock_start= DATA_BEGIN+inode.iblocks[i]*BLOCK_SZ;
                fseek(fp, dblock_start, SEEK_SET);
                fread(&dblock, num_ptr, 1, fp);
                //turn off the bits of the current block in the alloc bitmap
                bm_update(fp, ABIT_BEGIN, inode.iblocks[i], BM_OFF);       
                //clear the bits 
                for(j = 0; j < num_ptr; j++){
                    abit_idx = dblock[j];
                    bm_update(fp, ABIT_BEGIN, abit_idx, BM_OFF);
                }
            }
        
            if(dp->size_range > DP_I2BLOCK){
                //get i2block
                dblock_start = DATA_BEGIN+inode.i2block*BLOCK_SZ;
                fseek(fp, dblock_start, SEEK_SET);
                fread(&dblock, num_ptr, 1, fp);
                bm_update(fp, ABIT_BEGIN, inode.i2block, BM_OFF);
                for(i = 0; i < num_ptr; i++){
                    //turn off the bits of the current block
                    abit_idx = dblock[i];
                    bm_update(fp, ABIT_BEGIN, abit_idx, BM_OFF);

                    dblock_start = DATA_BEGIN+dblock[i]*BLOCK_SZ;
                    fseek(fp, dblock_start, SEEK_SET);
                    fread(&dblock2, num_ptr, 1, fp);

                    for(j = 0; j < num_ptr; j++){
                        abit_idx = dblock2[j];
                        bm_update(fp, ABIT_BEGIN, abit_idx, BM_OFF);
                    }
                }
            }
        }
    
    //get i3block
    dblock_start = DATA_BEGIN+inode.i3block*BLOCK_SZ;
    fseek(fp, dblock_start, SEEK_SET);
    fread(&dblock, num_ptr, 1, fp);
    bm_update(fp, ABIT_BEGIN, inode.i3block, BM_OFF);
    for(i = 0; i < num_ptr; i++){
        //turn off the bits of the current block
        abit_idx = dblock[i];
        bm_update(fp, ABIT_BEGIN, abit_idx, BM_OFF);

        dblock_start = DATA_BEGIN+dblock[i]*BLOCK_SZ;
        fseek(fp, dblock_start, SEEK_SET);
        fread(&dblock2, num_ptr, 1, fp);
        
        for(j = 0; j < num_ptr; j++){
            abit_idx = dblock2[j];
            bm_update(fp, ABIT_BEGIN, abit_idx, BM_OFF);
            
            dblock_start = DATA_BEGIN+dblock[i]*BLOCK_SZ;
            fseek(fp, dblock_start, SEEK_SET);
            fread(&dblock3, num_ptr, 1, fp);           
            for(k = 0; k < num_ptr; k++){
                abit_idx = dblock3[k];
                bm_update(fp, ABIT_BEGIN, abit_idx, BM_OFF);        
            }
        }
    }
    
    //clear all the bytes in inode
    char inode_block[INODE_SZ];
    memcpy(&inode_block, &inode, INODE_SZ);
    for(i = 0; i < INODE_SZ; i++){
        inode_block[i] = 0;
    }
    fseek(fp, INODE_ADDR(inode_idx), SEEK_SET);
    fwrite(&inode, INODE_SZ, 1, fp);
    return 0;
}*/

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
    
    int bcnt = device->superblock.inode_alloc_hd;
    int offset;
    char byte; 
    
    // Find next free inode
    while(bcnt <= (device->superblock.inode_count / 8)) {
      dev_read(&byte, sizeof(char), IBIT_BYTE_ADDR(bcnt), device);
      if(byte != 0) break;
      bcnt = (bcnt + 1) % (device->superblock.inode_count / 8);
    }
        
    
    offset = bm_get_free(&byte);
    printf("byte addr %d\n", IBIT_BYTE_ADDR(bcnt));
    printf("inode size %d\n", INODE_SZ);
    printf("ibit begin %d\n", IBIT_BEGIN);
    
    int inode_idx = IBIT_IDX(bcnt, offset);
    
    ibit_off(device, inode_idx);    
    printf("byte: %s; offset: %d\n", bytbi(byte), offset);
    device->superblock.freeblock_count--;
    device->superblock.inode_alloc_hd = bcnt;
    return inode_idx;
}

int fs_dealloc_inode(Dev* device, int inode_idx) {
    printf("inode idx %d\n", inode_idx);
    device->superblock.freeblock_count++;    
    return ibit_on(device, inode_idx);
}

/**
 * Write an inode into disk
 */
int fs_update_inode(iNode* node, int inode_idx, Dev* device) {
    fseek(device->phys_data, INODE_ADDR(inode_idx), SEEK_SET);
    fwrite(node, INODE_SZ, 1, device->phys_data);
    return 0;
}

int fs_alloc_databl(Dev* device) {
    if(device->superblock.freeblock_count <= 0) return -1;
    
    int bcnt = device->superblock.data_alloc_hd;
    int offset;
    char byte; 
    
    // Find next free inode
    while(bcnt <= (device->superblock.databl_count / 8)) {
      dev_read(&byte, sizeof(char), ABIT_BYTE_ADDR(bcnt), device);      
      if(byte != 0) break;
      bcnt = (bcnt + 1) % (device->superblock.databl_count / 8);
    }
    offset = bm_get_free(&byte);
    
    int databl_idx = ABIT_InDX(bcnt, offset);
    abit_off(device, databl_idx);    
    device->superblock.freeblock_count--;
    printf("byte: %s; offset: %d\n", bytbi(byte), offset);
    return databl_idx;
}


int fs_dealloc_daabl(Dev* device, int databl_idx) {
    printf("data block freed idx %d\n", databl_idx);
    device->superblock.freeblock_count++;
    return abit_on(device, databl_idx);
}


/**
 * Read data from file
 * @param inode_idx index of inode for file to read
 * @param pos starting read position
 * @param bytes number of bytes to read
 * @param data 
 * @return number of bytes read
 */
int fl_read(Dev* device, int inode_idx, int pos, int bytes, char* data) {
    int valid_bytes, read_bytes, n_bytes, data_pos;
    
    //get inode
    FILE* fp = device->phys_data;
    iNode inode;
    
    dev_read(&inode, INODE_SZ, pos, device);

    //compute offset
    DataPos dp;
    if(find_data_ptr(&inode, pos, &dp) == 0) // if the given position is invalid
    {
        return 0;
    }else 
    {
        // total bytes to read
        valid_bytes = get_valid_size(&inode, pos, bytes);
        // number of bytes being read
        read_bytes = 0;

        while(read_bytes < valid_bytes){
            //calculate the physical address of the current data position
            data_pos = calc_pos(device, &inode, &dp);
            //calculate the number of bytes to read
            n_bytes = MIN(BLOCK_SZ - dp.offset, valid_bytes - read_bytes);
            //read the bytes to data
            dev_read(&data+read_bytes, n_bytes, data_pos, device);
            // increment read
            read_bytes += n_bytes;
            //advance to next data block
            find_next_block(&dp);
        }
        
        return valid_bytes;
    }
}

int fl_write(Dev* device, int inode_idx, int pos, int bytes, char* data){
    int valid_bytes, read_bytes, n_bytes, data_pos;
    
    //get inode
    FILE* fp = device->phys_data;
    iNode inode;
    dev_read(&inode, INODE_SZ, pos, device);

    //compute offset
    DataPos dp;
    if(find_data_ptr(&inode, pos, &dp) == 0) // if the given position is invalid
    {
        return 0;
    }else 
    {
        // total bytes to read
        valid_bytes = get_valid_size(&inode, pos, bytes);
        // number of bytes being read
        read_bytes = 0;

        while(read_bytes < valid_bytes){
            //calculate the physical address of the current data position
            data_pos = calc_pos(device, &inode, &dp);
            //calculate the number of bytes to read
            n_bytes = MIN(BLOCK_SZ - dp.offset, valid_bytes - read_bytes);
            //read the bytes to data
            dev_read(&data+read_bytes, n_bytes, data_pos, device);
            // increment read
            read_bytes += n_bytes;
            //advance to next data block
            find_next_block(&dp);
        }
        
        return valid_bytes;
    }
}
