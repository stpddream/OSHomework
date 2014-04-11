#include "dozer.h"

void doze(iNode* inode) {
        
    int i, j, k;
    int remain = inode->size;   
    
    //write direct blocks
    for(i = 0; i < N_DBLOCKS; i++) {
        copy_data(inode->dblocks[i], data_idx_w);             
        inode->iblocks[i] = data_idx_w++;       
        if((remain -= BLOCK_SIZE) <= 0) return ;
    }
  
  
    //write indirect blocks        
    for(i = 0; i < N_IBLOCKS; i++) {
        int iblo_idx = data_idx_w++;
        
        fseek(fp_r, DATA_IDX(inode->iblocks[i]), SEEK_SET);
        for(j = 0; j < N_INDIR_PT; j++) {
            //write indirect blocks                  
            int data_idx;
            fread((void*)&data_idx, sizeof(int), 1, fp_r);   
            copy_data(data_idx, data_idx_w);

            //Record addr at in direct block            
            write_addr(iblo_idx + j * sizeof(int), data_idx_w);
            if((remain -= BLOCK_SIZE) < 0) return ;            
        }
        inode->iblocks[i] = iblo_idx;                                  
    }                    
    
    //Write double indirect blocks
    int first_idx = deref(ADDR_IDX(inode->i2block, i));
    int first_iblo_idx = data_idx_w++;     
    for(i = 0; i < N_INDIR_PT; i++) {            
        int sec_idx = deref(ADDR_IDX(first_idx, i));
        int second_iblo_idx = data_idx_w++;
                                    
        for(j = 0; j < N_INDIR_PT; j++) {                    
            int data_idx = deref(ADDR_IDX(sec_idx, j));
            fread((void*)&data_idx, sizeof(int), 1, fp_r);                
            copy_data(data_idx, data_idx_w);                  
            write_addr(second_iblo_idx + j * sizeof(int), data_idx_w);
            data_idx_w++;
        }    
        write_addr(first_iblo_idx + i * sizeof(int), second_iblo_idx);
    }
    inode->i2block = first_iblo_idx;    
    
    //Triple indirect blocks       
    first_idx = deref(ADDR_IDX(inode->i2block, i));
    first_iblo_idx = data_idx_w++;
    
    for(i = 0; i < N_INDIR_PT; i++) {
        int sec_idx = deref(ADDR_IDX(first_idx, j));
        int second_iblo_idx = data_idx_w++;
        
        for(j = 0; j < N_INDIR_PT; j++) {            
            int third_idx = deref(ADDR_IDX(sec_idx, j));
            int third_iblo_idx = data_idx_w++;
                                    
            for(k = 0; k < N_INDIR_PT; k++) {                    
                int data_idx = deref(ADDR_IDX(third_idx, k));                         
                copy_data(data_idx, data_idx_w);   
                write_addr(third_iblo_idx + k * sizeof(int), data_idx_w);                               
            }
            write_addr(second_iblo_idx + j * sizeof(int), third_iblo_idx);
        }
        write_addr(first_iblo_idx + i * sizeof(int), second_iblo_idx);
    }
    inode->i3block = first_iblo_idx; 
}

/**
 * Write address into position pos (in bytes) in file fp_w
 * @param pos
 * @param addr
 * @return 
 */
int write_addr(int pos, int addr) {
    fseek(fp_w, pos, SEEK_SET);
    fwrite(&addr, sizeof(int), 1, fp_w);
    return 0;
}


int copy_data(int from_idx, int to_idx) {
    char* data = read_data(from_idx);
    write_data(to_idx, data);
    free(data);       
    return 0;
}


char* read_data(int index) {
    fseek(fp_r, DATA_POS, SEEK_SET);    
    char* data = (char*)malloc(BLOCK_SIZE);    
    fread(data, BLOCK_SIZE, 1, fp_r);
    return data;    
}

int write_data(int index, char* data) {
    fseek(fp_r, DATA_POS, SEEK_SET);    
    fwrite(data, BLOCK_SIZE, 1, fp_r);
    return 0;
}


int deref(int index) {
    int data;
    fseek(fp_r, index, SEEK_SET);    
    fread((void*)&data, sizeof(int), 1, fp_r);
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

void print_inode(iNode* inode){
  printf("nlink = %d \t", inode->nlink);
  printf("size = %d\n", inode->size);
}

