#include <stdio.h>

#define SUPER_ITEMS 6
#define BLOCK_BASE 1024
#define INODE_ITEMS 25

int main(int argc, char** argv) {
    
    FILE* fp;
    fp = fopen("datafile-frag", "r");
    
    fseek(fp, 512, SEEK_SET); //Skip the first 512 byte
    
    int super_block[SUPER_ITEMS];    
    fread((void*)super_block, sizeof(int), SUPER_ITEMS, fp);
    
    int i;
    for(i = 0; i < SUPER_ITEMS; i++) {
        printf("%d\n", super_block[i]);
    }
    
    int block_size = super_block[0];
    int inode_pt = BLOCK_BASE + super_block[1];
    int data_pos = BLOCK_BASE + super_block[3];
    
    
  //  do {
        int inode[INODE_ITEMS];
        fread((void*)inode, sizeof(int), INODE_ITEMS, fp);
        
        

        
        
    //} while();
        
    
    
    
    
    
    return 0;
    
    
}
