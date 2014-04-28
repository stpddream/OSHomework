#include <string.h>
#include <unistd.h>
#include "dreader.h"
#include "dwriter.h"
#include "dozer.h"
#include "util.h"



int inode_begin, inode_end;
Superblock sb;
FILE* fp_w;
FILE* fp_r;
extern int data_idx_w;
int in_idx_w;

int main(int argc, char** argv) {
    int i, opt;
    
    /// Test
    in_idx_w = 0; 
    /// Test
    
    char filename[100];
    if(argc == 1){
      printUsage();
      exit(0);
    }

    while((opt = getopt(argc, argv, "h"))!=-1){
      if(opt == 'h'){
        printUsage();
      }else{
        printf("Please type -h to see usage\n");
      }
      exit(0);
    }
    
    for(i = 1; i < argc; i++){
      if(argv[i][0]!='-'){
        strcpy(filename, argv[i]);
        break;
      }
    }
    
    printf("Start defraging ... \n");
       
    //open the read and write files
    fp_r = fopen(filename, "r");
    fp_w = fopen("datafile-defrag", "w"); 
    //fp_w = fopen("def", "w");

  
    
    //Init buffer    
    dw_init_buffer();
    dr_init_buffer();
    
   
    //Copy boot block
    char boot_block[BOOT_SIZE];

    fread(boot_block, BOOT_SIZE, 1, fp_r);  
    fwrite(boot_block, BOOT_SIZE, 1, fp_w);
    
    fread(&sb, sizeof(Superblock), 1, fp_r); //read the superblock
    init_inode_arr();
    
  
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
    
    printf("Inode Region starts: %d\n", inode_begin);
    printf("Data Region starts: %d\n", inode_end);
    printf("Swap Region starts: %d\n", BLOCK_BASE + sb.swap_offset * sb.size);
    printf("Free block start: %d\n", sb.free_iblock);
    
    printf("Processing all inodes ... \n");
    
    for(i = 0; i <INODE_SEC_SIZE/INODE_SIZE; i++){
                                
        
        if(i != 8) continue;
        print_inode(&inode_arr[i], TRUE);
        if(inode_arr[i].nlink != 0) doze(&inode_arr[i]);
        printf("dmp!! %d\n", data_idx_w);
    }
        
    printf("\n\n");

   
    sb.free_iblock = data_idx_w;
    fseek(fp_w, BOOT_SIZE, SEEK_SET);
    fwrite(&sb, sizeof(Superblock), 1, fp_w);  //Copy Super Block
     
    printf("In total %d blocks\n", data_idx_w);
    
    // Inode now is
    for(i = 0; i < INODE_SEC_SIZE / INODE_SIZE; i++) {
        print_inode(&inode_arr[i], TRUE);
    }
    
    
    dw_flush_inode_arr();
    //dw_close();
    //dr_close();
    //close both file
    fclose(fp_r);
    fclose(fp_w);
    return 0;    

}
