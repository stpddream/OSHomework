#include "dozer.h"

int inode_begin, inode_end;
Superblock sb;
FILE* fp_w;
FILE* fp_r;
int data_idx_w;
int in_idx_w;

int main(int argc, char** argv) {
    int i, tmp, cur_node;
    iNode inode;
    //open the read and write files
    fp_r = fopen("datafile-frag", "r");
    fp_w = fopen("datafile-defrag", "w"); 

    //Copy boot block
    char boot_block[BOOT_SIZE];
    fread(boot_block, BOOT_SIZE, 1, fp_r);
    fwrite(boot_block, BOOT_SIZE, 1, fp_w);
    
    fread(&sb, sizeof(Superblock), 1, fp_r); //read the superblock
    fwrite(&sb, sizeof(Superblock), 1, fp_w);  //Copy Super Block
    
    printf("size = %d\n", sb.size);
    printf("inode offset = %d\n", sb.inode_offset); 
    printf("data offset = %d\n", sb.data_offset);
    printf("swap offset = %d\n", sb.swap_offset);
    printf("free inode index = %d\n", sb.free_inode);
    printf("free iblock index = %d\n", sb.free_iblock);
   
    printf("size of inode = %ld\n", sizeof(iNode)); 
    printf("number of iNodes = %d\n", (int)(sb.size/sizeof(iNode)*4));
  
    // set the begining and end location of the iNode chunck
    inode_begin = BLOCK_BASE + sb.inode_offset * sb.size;
    inode_end = BLOCK_BASE + sb.data_offset * sb.size;
    
    in_idx_w = inode_begin;
    
    printf("printing inode list ... \n");
    for(i = 0, cur_node = inode_begin; (tmp = next_inode(cur_node)) != -1; cur_node = tmp, i++) {
        printf("curNode [%d]\t %d \t %s\t", i, cur_node, (is_free_inode(cur_node)? "free   ": "occupied"));
        get_inode_by_addr(cur_node, &inode); 
        printf("here !!\n");
        if(!is_free_inode(cur_node)) doze(&inode);
        printf("ioioioi\n");
        fseek(fp_w, INODE_ADDR_BY_IDX(in_idx_w++), SEEK_SET);
        fwrite(&inode, INODE_SIZE, 1, fp_w);     
        
        print_inode(&inode);
        printf("%d\n", tmp);
        printf("iwoeirjwoiefjweiofjweiof\n");
    }

    
    printf("\n\n");
    /*
    for(i = 0; i < 20; i++){
        int inode_addr = 1024+i*100;
        get_inode_by_addr(inode_addr, &inode);
        printf("curNode[%d]\t %d\t %s\t", i, inode_addr, (is_free_inode(inode_addr)? "free   ": "occupied"));
        print_inode(&inode);
    }
    
    iNode freehead, tmpfree;
    get_inode_by_index(sb.free_inode, &freehead);
    tmpfree = freehead;
    
    while(tmpfree.next_inode != -1) {
      printf("freenode idx: %d\n", tmpfree.next_inode);
      get_inode_by_index(tmpfree.next_inode, &tmpfree);
    }*/

    //close both file
    fclose(fp_r);
    fclose(fp_w);
    return 0;    
}
