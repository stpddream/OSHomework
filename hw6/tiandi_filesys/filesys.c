#include "filesys.h"

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
 * Read data from file
 * @param inode_idx index of inode for file to read
 * @param pos starting read position
 * @param bytes number of bytes to read
 * @param data 
 * @return 0 if success
 */
int fl_read(int inode_idx, int pos, int bytes, char* data) {
    
   
    //Convert pos to 
    
    
    
       
}