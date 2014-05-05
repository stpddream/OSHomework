/* 
 * File:   test_main.c
 * Author: Panda & Jacy
 *
 * Created on April 28, 2014, 8:00 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "bitmap.h"
#include "util.h"
#include "device_ctrl.h"
#include "filesys_util.h"
#include "file_table.h"

extern FileTable filetable;

/*
 * 
 */
int main(int argc, char** argv) {
    int i;
    FILE* fp;
    fp = fopen("testfile/disk", "w+");    
    Dev* device = dev_create(fp);            
    dev_init(device, 20480);
    fs_init(device, 20480);
  
    printf("Number is %d\n", device->bootblock.fun);
    printf("%s\n", device->bootblock.have_fun);    
    print_superblock(&device->superblock);
    
    ft_init();
    for(i = 0; i < 10; i++) printf("fd: %d %d \n", ft_put(i, 0), filetable.size);
    
    
    ft_remove(5);
    ft_remove(7);
    ft_remove(3);
    
    printf("Current size is %d\n", filetable.size);
    
    printf("Printing right now\n");
    print_filetable();
    
    
    
    
         
    
    
    /*
    printf("\n======== abits ========\n");
    
    char abit[BLOCK_SZ * 16];
    fseek(fp, ABIT_BEGIN, SEEK_SET);
    fread(abit, sizeof(abit), 1, fp);
    for(i = 0; i < BLOCK_SZ * 16; i++) printf("%d ", abit[i]);
     */   
    
    /*
    iNode inode[4096];
    
    printf("how many inodes: %d\n", sb.inode_count);
    
    iNode some_node;
     */
    /*    fseek(fp, INODE_ADDR(1), SEEK_SET);
    fread(&some_node, INODE_SZ, 1, fp);
    
    printf("Inode begin %d\n", INODE_BEGIN);
    printf("Inode first %d\n", INODE_ADDR(1));
    printf("File type is %d\n", some_node.file_type);
    */
    /*
    iNode sm_node;
    for(i = 0; i < 4096; i++) {
        //fseek(fp, INODE_ADDR(i), SEEK_SET);
        //fread(&some_node, INODE_SZ, 1, fp);   
        
        fs_get_inode(&some_node, i, fp);    
        printf("%d\n", some_node.file_type);
        some_node.file_type = 1000;
        fs_update_inode(&some_node, i, fp);
    }
    
    for(i = 0; i < 4096; i++) {          
        iNode another;
        fs_get_inode(&another, 0, fp);
        printf("Now is %d\n", another.file_type);
    }*/
   
    
    return (EXIT_SUCCESS);
}

