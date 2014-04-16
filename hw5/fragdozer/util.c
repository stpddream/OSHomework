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


