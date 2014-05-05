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
    /* Calculations */
    int n_inode = cal_n_inode(size);
    int n_datablock = n_inode * DATABL_INODE_RATIO;
    
    
   
    
    /* Init Bootblock */
    Bootblock bootblock;
    strcpy(bootblock.have_fun, "Hidden Virus!!!!");
    
    /* Write Superblock */
    fseek(group, 0, SEEK_SET);
    fwrite(&bootblock, sizeof(bootblock), 1, group);
    
    
    /* Init Superblock */    
    Superblock superblock;
    superblock.inode_count = n_inode;
    superblock.freeinode_count = n_inode;
    superblock.system_type = TIANDI_FS_ID;
    superblock.freeblock_count = n_datablock;
    superblock.ibit_offset = 0;
//    superblock.abit_offset = 
    int superblock_offset = BOOT_SZ;
    fseek(group, superblock_offset, SEEK_SET);
    
}

/**
 * unlink inode, clears all parameters within the given 
 * @param inode_idx
 * @return 0 if success
 */
int fs_remove_file(int inode_idx, int dev_id){
    // turn off the bit in the inode bitmap
    FILE* fp;
    int i, j, k, abit_idx, dblock_start;
    int num_ptr = BLOCK_SZ/sizeof(int);
    int dblock[num_ptr];
    int dblock2[num_ptr];
    int dblock3[num_ptr];

    
    bm_update(fp, IBIT_BEGIN, IBIT_ADDR(inode_idx), BM_OFF);
    // clear all the bits in the inode
    iNode inode;
    fseek(fp, INODE_ADDR(inode_idx), SEEK_SET);
    fread(&inode, INODE_SZ, 1, fp);
    
    
    
    //clear the data blocks pinted by block
    for(i = 0; i < N_DBLOCKS; i++){
        abit_idx = inode.dblocks[i];
        bm_update(fp, ABIT_BEGIN, abit_idx, BM_OFF);
    }
    
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
    char* inode_block = (char*)inode;
    for(i = 0; i < INODE_SZ; i++){
        inode_block[i] = 0;
    }
    fseek(fp, INODE_ADDR(inode_idx), SEEK_SET);
    fwrite(&inode, INODE_SZ, 1, fp);
    return 0;
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