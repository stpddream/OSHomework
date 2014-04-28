#include "dwriter.h"

int data_idx_w;
char* buffer_w;
int buffer_ptr_w;
int data_addr_w;

/* initializes the writer buffer */
int dw_init_buffer() {
  if((buffer_w = (char*)malloc(BUFFER_SIZE_W*sizeof(char))) != NULL){
      buffer_ptr_w = 0;
      return 0;
  } else {
      return -1;
  }
}

int dw_close(){
  dw_flush();
  free(buffer_w);
  return 0;
}


/* flush function is called when the buffer_w is full,
 * this function writes all the buffer to file and reset the buffer pointer*/
void dw_flush(){
  //write the buffer_w to file
  fseek(fp_w, data_addr_w, SEEK_SET);
  fwrite(buffer_w, buffer_ptr_w, 1, fp_w);
  //update the data ind
  data_addr_w += BUFFER_SIZE_W;
  //move the buffer pointer to the beginning of the buffer
  buffer_ptr_w = 0; 
}

/* this function copies the data from the reader buffer with the given address
 * to the writer buffer */
int dw_write2buf(int chunk_addr){
  int i;
  //if the buffer is full, flush the buffer
  if(buffer_ptr_w == BUFFER_SIZE_W){
    dw_flush();
  }
  //copy the datablock from read buffer to writer buffer
  for(i = 0; i < BLOCK_SIZE; i++){
    buffer_w[buffer_ptr_w++] = buffer_r[chunk_addr+i]; 
  }

  return data_idx_w++;
}

int dw_write_arr(int* arr){
  if(buffer_ptr_w == BUFFER_SIZE_W){
    dw_flush();
  }
  
  int i;
  for(i = 0; i < N_INDIR_PT; i++) {
   memcpy(buffer_w+buffer_ptr_w, &arr[i], sizeof(int));
   printf("Writing %d...\n", arr[i]);
   buffer_ptr_w += sizeof(int); 
  }
  return data_idx_w++;
}

int dw_flush_inode_arr(){
  fseek(fp_w, INODE_BEGIN, SEEK_SET);
  fwrite(inode_arr, INODE_SEC_SIZE, 1, fp_w);
  return 0;
}
