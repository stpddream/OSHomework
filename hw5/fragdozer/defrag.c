#include <stdio.h>

#define SUPER_ITEMS 6
#define BLOCK_BASE 1024
#define INODE_ITEMS 25
#define N_DBLOCKS 10
#define N_IBLOCKS 4

typedef struct{
  int size;
  int inode_offset;
  int data_offset;
  int swap_offset;
  int free_inode;
  int free_iblock;
}Superblock;

typedef struct{
  int next_inode;
  int protect;
  int nlink;
  int size;
  int uid;
  int gid;
  int ctime;
  int mtime;
  int atime;
  int dblocks[N_DBLOCKS];
  int iblocks[N_IBLOCKS];
  int i2block;
  int i3block;
} iNode;

int main(int argc, char** argv) {
    
    FILE* fp;
    fp = fopen("datafile-frag", "r");
    
    fseek(fp, 512, SEEK_SET); //Skip the first 512 byte
    
    //int super_block[SUPER_ITEMS];    
    Superblock sb;
    fread(&sb, sizeof(Superblock), 1, fp);
    printf("size = %d\n", sb.size);
    printf("inode offset = %d\n", sb.inode_offset); 
    printf("data offset = %d\n", sb.data_offset);
    printf("swap offset = %d\n", sb.swap_offset);
    printf("free inode index = %d\n", sb.free_inode);
    printf("free iblock index = %d\n", sb.free_iblock);
   
    printf("size of inode = %ld\n", sizeof(iNode)); 
    printf("number of iNodes = %d\n", (int)(sb.size/sizeof(iNode)*4));
    /*inode free_head;
    fseek(fp, sb.free_inode*sb.size, SEEK_CUR);
    fread(&free_head, sizeof(inode), 1, fp);
    */
     
    /*
    int i;
    for(i = 0; i < SUPER_ITEMS; i++) {
        printf("%d\n", super_block[i]);
    }
    
    int block_size = super_block[0];
    int inode_pt = BLOCK_BASE + super_block[1];
    int data_pos = BLOCK_BASE + super_block[3];
    
    
  //  do {
        int inode[INODE_ITEMS];
        fread((void*)inode, sizeof(int), INODE_ITEMS, fp);*/
        
        

        
        
    //} while();
        
    
    
    
    
    
    return 0;
    
    
}
