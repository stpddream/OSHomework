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




