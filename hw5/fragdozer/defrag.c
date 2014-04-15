
#include <string.h>
#include "dozer.h"
#include "util.h"



int inode_begin, inode_end;
Superblock sb;
FILE* fp_w;
FILE* fp_r;
int data_idx_w;
int in_idx_w;

int main(int argc, char** argv) {
    int i, tmp, cur_node;


    iNode* inode;
    //open the read and write files
    fp_r = fopen("datafile-frag", "r");
    fp_w = fopen("datafile-defrag", "w"); 
    data_idx_w = 0;
    
    //Copy boot block
    char boot_block[BOOT_SIZE];
    fread(boot_block, BOOT_SIZE, 1, fp_r);
    fwrite(boot_block, BOOT_SIZE, 1, fp_w);
    
    fread(&sb, sizeof(Superblock), 1, fp_r); //read the superblock
    fwrite(&sb, sizeof(Superblock), 1, fp_w);  //Copy Super Block
    /*
    printf("size = %d\n", sb.size);
    printf("inode offset = %d\n", sb.inode_offset); 
    printf("data offset = %d\n", sb.data_offset);
    printf("swap offset = %d\n", sb.swap_offset);
    printf("free inode index = %d\n", sb.free_inode);
    printf("free iblock index = %d\n", sb.free_iblock);
   
    printf("size of inode = %ld\n", sizeof(iNode)); 
    printf("number of iNodes = %d\n", (int)(sb.size/sizeof(iNode)*4));
  */
    // set the begining and end location of the iNode chunck
    inode_begin = BLOCK_BASE + sb.inode_offset * sb.size;
    inode_end = BLOCK_BASE + sb.data_offset * sb.size;
    
    printf("Inode Region starts: %d\n", inode_begin);
    printf("Data Region starts: %d\n", inode_end);
    printf("Swap Region starts: %d\n", BLOCK_BASE + sb.swap_offset * sb.size);
    
    in_idx_w = inode_begin;
            
    printf("Processing all inodes ... \n");
    for(i = 0, cur_node = inode_begin; (tmp = next_inode(cur_node)) != -1; cur_node = tmp, i++) {
        //printf("curNode [%d]\t %d \t %s\t\n", i, cur_node, (is_free_inode(cur_node)? "free   ": "occupied"));      
        //if(i != 8) continue;
        printf("->%d \t", i);
        inode = (iNode*)malloc(sizeof(iNode)); //why can not be moved outside     
        get_inode_by_addr(cur_node, inode);        
        print_inode(inode, TRUE);
        
        if(!is_free_inode(cur_node)) doze(inode);
             
        fseek(fp_w, INODE_ADDR_BY_IDX(in_idx_w++), SEEK_SET);
        fwrite(inode, INODE_SIZE, 1, fp_w);     
        free(inode); //Why cannot I free it herererere???
        //print_inode(&inode);      
        
        printf("\n\n");
    }
    
    printf("... %d Data blocks are occupied ...\n", data_idx_w);

    
    printf("\n\n");

    //close both file
    fclose(fp_r);
    fclose(fp_w);
    return 0;    

}
