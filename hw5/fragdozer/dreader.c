#include "dreader.h"

int chunk_id;
char* buffer_r;
iNode* inode_arr;

int dr_init_buffer() {
    buffer_r = (char*)malloc(BUFFER_SIZE_R);    
    chunk_id = -1;
    return 0;
}


/**
 * Find 
 * @param data_idx
 * @return 
 */
int find_chunk(int data_idx) {            
    return (data_idx * BLOCK_SIZE) / BUFFER_SIZE_R;
}

int find_datablock(int data_idx) {
    return (data_idx * BLOCK_SIZE) % BUFFER_SIZE_R;
}


/**
 * Read chunk from buffer
 * @param idx
 * @return 
 */
int dr_read_buf(int idx) {
    int this_chunk;
    if((this_chunk = find_chunk(idx)) != chunk_id) {       
        chunk_id = this_chunk;
        load_chunk(this_chunk);
    }
    return find_datablock(idx);    
}

/**
 * Read one block at #idx
 * @param idx
 * @return 
 */
int dr_read_block(int idx) {
    return dr_read_buf(idx);       
}


/**
 * Read the #item address at indirect block idx 
 * @param idx
 * @param offset
 * @return 
 */
int dr_read_indir(int block_idx, int item_idx) {
    int data_buf_pos = dr_read_buf(block_idx);
    printf("Block %d %d %d\n", block_idx, data_buf_pos, item_idx);
    int addr;    
    memcpy(&addr, buffer_r + data_buf_pos + item_idx * sizeof(int), sizeof(int));
    printf("Address is %d\n", addr);
    return addr;    
}


/**
 * @diskread
 * Load chunk #idx into memory buffer
 * @param chunk_idx
 * @return 0 if success
 */
int load_chunk(int idx) {
    printf("Memory from %d loaded\n", idx);
    fseek(fp_r, CHUNK_ADDR(idx), SEEK_SET);    
    fread(buffer_r, BUFFER_SIZE_R, 1, fp_r);   
    return 0;
}

/**
 * Close reader stream
 * @return 
 */
int dr_close() {
    free(buffer_r);
    return 0;
}

int init_inode_arr(){
  char tmp_inode_buf[DATA_BEGIN-INODE_BEGIN];
  fseek(fp_r, INODE_BEGIN,SEEK_SET);
  fread(tmp_inode_buf, DATA_BEGIN-INODE_BEGIN,1,fp_r);

  if((inode_arr = (iNode*)malloc((DATA_BEGIN - INODE_BEGIN)*sizeof(char)))!= NULL){
    iNode cur_node;
    int tmp_buf_ptr, i;
    for(i = 0, tmp_buf_ptr = 0; tmp_buf_ptr < DATA_BEGIN-INODE_BEGIN; tmp_buf_ptr+=sizeof(iNode), i++){    
      memcpy(&cur_node, tmp_inode_buf+tmp_buf_ptr, sizeof(iNode));
      inode_arr[i] = cur_node;
    }
    return 0;
  }else{
    return -1;
  }
}
