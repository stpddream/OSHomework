#include "util.h"

void print_inode(iNode* inode, int detail){
    printf("[inode: nlink=%d, size=%d]\n", inode->nlink, inode->size);
    if(detail) {        
        printf("Dblocks: {");
        int i = 0;
        for(; i < N_DBLOCKS; i++) {
            printf("%d, ", inode->dblocks[i]);
        }
        printf("}\n");               
        
        printf("InDblocks: {");
        for(i = 0; i < N_IBLOCKS; i++) {
            printf("%d, ", inode->iblocks[i]);
        }
        printf("}\n");               

    }
}

void printUsage(){
  printf("defrag:\t performs defragmentation on a Disk File by compacting all the blocks of a file in sequential order on disk\n");  
  printf("Usage:\n");
  printf("\t./defrag [OPTIONS] <fragemented disk file>\n");
  printf("Description:\n");
  printf("\t -h display help manual\n");
}

size_t getTotalSysMem(){
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);
    return pages * page_size;
}

size_t get_buf_size(int flag){
  if(flag == FLEX_BUF_FLAG){
    //set the buffer size to be one percent of the RAM size
    int buf_size = getTotalSysMem()*0.1;
    return buf_size * BLOCK_SIZE/BLOCK_SIZE;
  }else{
    return DEFAULT_BUF_SIZE;
  }
}

void arr_clear(int* arr, int size) {
    int i = 0;
    for(i = 0; i < size; i++) arr[i] = 0;
}
