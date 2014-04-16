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
        inode->dblocks[i] = copy_datai(inode->dblocks[i]);                     
        //printf("Write to data %d\n", DATA_ADDR(inode->dblocks[i]));      
        if((remain -= BLOCK_SIZE) <= 0) return ;
    }
  
    printf("==== Indirect blocks data ====\n");
  
    //Process indirect blocks        
    for(i = 0; i < N_IBLOCKS; i++) {    //For each indirect block
       
        int indir_data[N_INDIR_PT];        
        arr_clear(indir_data);
        
        //Keep tract of old block pointer
        //int old_iblock = inode->iblocks[i];
        
        printf("Indirect block was at %d ---->", DATA_ADDR(old_iblock));
        //inode->iblocks[i] = data_idx_w++;    //Relocate indirect block pos
        
        printf("Moved to %d\n", DATA_ADDR(inode->iblocks[i]));
        
        for(j = 0; j < N_INDIR_PT; j++) {
            //write data blocks                  
                                    
            //printf("Next address is %ld\n", DATA_ADDR_O(old_iblock, j));            
            int data_idx = dr_read_indir(inode->iblocks[i], j);            
                                 
            //printf("Original data at %d ----> Write to data %d\n", data_idx, data_idx_w);      
            indir_data[j] = copy_datai(data_idx);           
            
            if((remain -= BLOCK_SIZE) <= 0) {
                //Process pointer to indirect blocks
                printf("Layer: %d; Entry: %d\n", i, j);
                return ;            
            }
        }        
        inode->iblocks[i] = dw_write_arr(indir_data);
        
    }                    
    
    printf("Start writing double indirect blocks\n");
    
    //Process double indirect blocks    
    int first_indir_data[N_INDIR_PT];
    arr_clear(first_indir_data);
    int first_idx = inode->i2block;
    
    for(i = 0; i < N_INDIR_PT; i++) {            
        int sec_idx = dr_read_indir(first_idx, i);
        int sec_indir_data[N_INDIR_PT];
        arr_clear(sec_indir_data);        
                                        
        for(j = 0; j < N_INDIR_PT; j++) {                        
            int data_idx = dr_read_indir(sec_idx, j);                                
            sec_indir_data[j] = copy_datai(data_idx);                                              
                        
            if((remain -= BLOCK_SIZE) <= 0) {                               
                first_indir_data[i] = dw_write_arr(sec_indir_data);
                inode->i2block = dw_write_arr(first_indir_data);                               
                return ;                        
            }
        }    
        first_indir_data[i] = dw_write_arr(sec_indir_data);                
    }
    inode->i2block = dw_write_arr(first_indir_data);
    
    //Triple indirect blocks       
    first_idx = inode->i3block;
    arr_clear(first_indir_data);
     
    for(i = 0; i < N_INDIR_PT; i++) {
        int sec_idx = dr_read_indir(first_idx, i);
        int sec_indir_data[N_INDIR_PT];
        arr_clear(sec_indir_data);        
                                              
        for(j = 0; j < N_INDIR_PT; j++) {            
            int third_idx = dr_read_indir(sec_idx, j);
            int third_indir_data[N_INDIR_PT];
            arr_clear(third_indir_data);
                                    
            for(k = 0; k < N_INDIR_PT; k++) {                                   
                int data_idx = dr_read_indir(third_idx, k);                
                third_indir_data[k] = copy_datai(data_idx);   
                
                if((remain -= BLOCK_SIZE) <= 0) {
                    sec_indir_data[j] = dw_write_arr(third_indir_data);
                    first_indir_data[i] = dw_write_arr(sec_indir_data);
                    inode->i3block = dw_write_arr(first_indir_data);
                    return ;    
                }
            }
            sec_indir_data[j] = dw_write_arr(third_indir_data);
        }
        first_indir_data[i] = dw_write_arr(sec_indir_data);
    }
    inode->i3block = dw_write_arr(first_indir_data);
}


/*
 * All following functions if ends with a "i", takes in data index as the parameter
 * Only low level functions take in byte position
 */



/**
 * Copy data from position from_idx (in data seg index)
 * @param idx
 * @return 
 */
int copy_datai(int idx) {
    int data_idx_buf = dr_read_block(idx);
    dw_write2buf(data_idx_buf);
    
    //printf("Copy data from %d --> to %d\n", DATA_ADDR(from_idx), DATA_ADDR(to_idx));
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



////////// Inode Helper Functions ////////////


int get_inode_by_index(int idx, iNode* cur) {
  get_inode_by_addr(INODE_ADDR(idx), cur);
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
