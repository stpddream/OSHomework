#include "dozer.h"

void doze(iNode* inode) {
        
    int i, j, k;
    int remain = inode->size;
    
    /**
     * Caution: All following address manipulation are based on DATA INDEX;
     * data index to true byte address conversion is processed in lower level
     * methods. DATA_ADDR macro call shouldn't appear except for printing purposes
     */
    
    
    printf("===== Copying to direct blocks =====\n");
    
    //Process direct blocks
    for(i = 0; i < N_DBLOCKS; i++) {
        //printf("Original data at %d ----> ", DATA_ADDR(inode->dblocks[i]));
        copy_datai(inode->dblocks[i], data_idx_w);             
        inode->dblocks[i] = data_idx_w++;       
        //printf("Write to data %d\n", DATA_ADDR(inode->dblocks[i]));      
        if((remain -= BLOCK_SIZE) <= 0) return ;
    }
  
    printf("==== Indirect blocks data ====\n");
  
    //Process indirect blocks        
    for(i = 0; i < N_IBLOCKS; i++) {    //For each indirect block
                
        //Keep tract of old block pointer
        int old_iblock = inode->iblocks[i];
        
        printf("Indirect block was at %d ---->", DATA_ADDR(old_iblock));
        inode->iblocks[i] = data_idx_w++;    //Relocate indirect block pos
        printf("Moved to %d\n", DATA_ADDR(inode->iblocks[i]));
        
        for(j = 0; j < N_INDIR_PT; j++) {
            //write data blocks                  
                                    
            //printf("Next address is %ld\n", DATA_ADDR_O(old_iblock, j));            
            int data_idx = read_int(fp_r, old_iblock, j); //Get data block address
            
            //printf("Original data at %d ----> Write to data %d\n", data_idx, data_idx_w);      
            copy_datai(data_idx, data_idx_w);
            
            //Record addr at indirect block                                
            write_addri(inode->iblocks[i], j, data_idx_w);
                        
            data_idx_w++;
            
            if((remain -= BLOCK_SIZE) <= 0) {
                //Process pointer to indirect blocks
                printf("Layer: %d; Entry: %d\n", i, j);
                return ;            
            }
        }
    }                    
    
    printf("Start writing double indirect blocks\n");
    
    //Process double indirect blocks    
    int first_idx = inode->i2block;
    int first_iblo_idx = data_idx_w++;     
    for(i = 0; i < N_INDIR_PT; i++) {            
        int sec_idx = read_int(fp_r, first_idx, i); // deref(DATA_ADDR_O(first_idx, i));
        int second_iblo_idx = data_idx_w++;
                                    
        for(j = 0; j < N_INDIR_PT; j++) {                    
            int data_idx = read_int(fp_r, sec_idx, j); 
            copy_datai(data_idx, data_idx_w);                              
            write_addri(second_iblo_idx, j, data_idx_w);
            data_idx_w++;          
                        
            if((remain -= BLOCK_SIZE) <= 0) {                               
                write_addri(first_iblo_idx, i, second_iblo_idx);
                inode->i2block = first_iblo_idx;    
                return ;                        
            }
        }    
        write_addri(first_iblo_idx, i, second_iblo_idx);
    }
    inode->i2block = first_iblo_idx;    
    
    //Triple indirect blocks       
    first_idx = inode->i3block;
    first_iblo_idx = data_idx_w++;
    
    for(i = 0; i < N_INDIR_PT; i++) {
        int sec_idx = read_int(fp_r, first_idx, j); 
        int second_iblo_idx = data_idx_w++;
        
        for(j = 0; j < N_INDIR_PT; j++) {            
            int third_idx = read_int(fp_r, sec_idx, j); 
            int third_iblo_idx = data_idx_w++;
                                    
            for(k = 0; k < N_INDIR_PT; k++) {                                   
                int data_idx = read_int(fp_r, third_idx, k);
                
                copy_datai(data_idx, data_idx_w);   
                write_addri(third_iblo_idx, k, data_idx_w);
                data_idx_w++;
                
                if((remain -= BLOCK_SIZE) <= 0) {
                    write_addri(second_iblo_idx, j, third_iblo_idx);
                    write_addri(first_iblo_idx, i, second_iblo_idx);
                    inode->i3block = first_iblo_idx; 
                    return ;    
                }
            }
            write_addri(second_iblo_idx, j, third_iblo_idx);
        }
        write_addri(first_iblo_idx, i, second_iblo_idx);
    }
    inode->i3block = first_iblo_idx; 
}


/*
 * All following functions if ends with a "i", takes in data index as the paramter
 * Only low level functions take in byte position
 */



/**
 * Copy data from position from_idx to to_idx (in data seg index)
 * @param from_idx
 * @param to_idx
 * @return 
 */
int copy_datai(int from_idx, int to_idx) {
    char* data = read_data(DATA_ADDR(from_idx));
    write_data(DATA_ADDR(to_idx), data);
    printf("Copy data from %d --> to %d\n", DATA_ADDR(from_idx), DATA_ADDR(to_idx));
    
    free(data);        //Why can't I free it here???
    return 0;
}

/**
 * Write address into memory at data index idx
 * @param pos
 * @param addr
 * @return 
 */
int write_addri(int base_idx, int item, int addr) {
    return write_addr(DATA_ADDR_O(base_idx, item), addr);
}


/**
 * fseek to data index idx
 * @param stream
 * @param idx
 * @return 
 */
int fseeki(FILE* stream, long idx) {
    return fseekio(stream, idx, 0);
}

/**
 * fseek to data index and ith item (integer)
 * @param stream
 * @param idx
 * @param item
 * @return 
 */
int fseekio(FILE* stream, long idx, int item) {
    return fseek(stream, DATA_ADDR_O(idx, item), SEEK_SET);
}


/**
 * Read a integer from a file
 * Warning size_t info is ignored
 * @param stream
 * @return 
 */
int read_int(FILE* stream, long idx, int item) {
    int data;    
    fseekio(stream, idx, item);
    fread(&data, sizeof(int), 1, stream);
    return data;
}


//////////// Low Level Disk Operation Functions //////////////

/**
 * Low Level Function to read data from byte position byte_pos in disk image
 * @param pos
 * @return 
 */
char* read_data(int byte_pos) {
    fseek(fp_r, byte_pos, SEEK_SET);    
    char* data = (char*)malloc(BLOCK_SIZE);    
    fread(data, BLOCK_SIZE, 1, fp_r);
    
    return data;    
}

/**
 * Low Level Function to write data to byte position byte_pos in disk image
 * @param byte_pos
 * @param data
 * @return 
 */
int write_data(int byte_pos, char* data) {
    fseek(fp_r, byte_pos, SEEK_SET);    
    fwrite(data, BLOCK_SIZE, 1, fp_r);
    return 0;
}


/**
 * Low Level Function to write address into position pos (in bytes) in file fp_w
 * @param pos
 * @param addr
 * @return 
 */
int write_addr(int byte_pos, int addr) {
    fseek(fp_w, byte_pos, SEEK_SET);
    fwrite(&addr, sizeof(int), 1, fp_w);
    return 0;
}

/**
 * Low level function to dereference a position points to a address
 * @param pos
 * @return 
 */
int deref(int pos) {
    int data;
    fseek(fp_r, pos, SEEK_SET);    
    fread(&data, sizeof(int), 1, fp_r);
    return data;
}


int get_inode_by_index(int idx, iNode* cur){
  get_inode_by_addr(INODE_ADDR_BY_IDX(idx), cur);
  return 0;
}

int get_inode_by_addr(int curNode, iNode* cur){
  fseek(fp_r, curNode, SEEK_SET);
  fread(cur, sizeof(iNode), 1, fp_r);
  return 0;
}

/* return true if the current inode is free
 * false otherwise */
int is_free_inode(int curNode){
  iNode cur;
  get_inode_by_addr(curNode, &cur);
  return (cur.nlink == 0 ? TRUE : FALSE);
}

/* find the next inode in the list,
 * return -1 when there is no nextNode (curNode is the tail */
int next_inode(int curNode){
  int nextNode = curNode + INODE_SIZE;
  if(nextNode > inode_begin && nextNode < inode_end){
    return nextNode;
  }
  return -1;
}

/* find the next occupied inode in the list
 * return -1 when there is no next occupied node */
int next_occupied_inode(int curNode){
  while((curNode = next_inode(curNode)) != -1 && is_free_inode(curNode));
  return curNode;
}

