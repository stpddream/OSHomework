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
   
    
    
    //print_ibit(device);
/*
    int which = fs_alloc_inode(device);
    printf("which is %d\n", which);
    
    //iNode node;
    //fs_get_inode(&node, which, device);
    //node.file_type = 3333;
    
    int which2 = fs_alloc_inode(device);
    printf("another which %d\n", which2);
    
   
   
    fs_dealloc_inode(device, which);
    
    //printf("Second print\n");
    print_ibit(device);
  */  
        
    for(i = 0; i < device->superblock.inode_count; i++) {
        printf("Allocated: %d\n", fs_alloc_inode(device));
        //    print_ibit(device);

    }       
    
    for(i = 25; i < 600; i++) {
        fs_dealloc_inode(device, i);
    }

    fs_dealloc_inode(device, 3);
    fs_dealloc_inode(device, 2);
    print_ibit(device);
    
    //fs_alloc_inode(device);
    print_ibit(device);
    
    
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
   /*
    iNode sm_node;
    fs_get_inode(&sm_node, 0, fp);
   
    printf("File type is %d\n", sm_node.file_type);
    sm_node.file_type = 50;
    
    fs_update_inode(&sm_node, 0, fp);
  
    iNode another;
    fs_get_inode(&another, 0, fp);
    printf("Now is %d\n", another.file_type);
*/
    
    /*
    fseek(fp, SUPERBL_BEGIN, SEEK_SET);
    fread(data, sizeof(data), 1, fp);
    int i;
    for(i = 0; i < 1024; i++) printf("%d ", data[i]);
     */   
    
    
    return (EXIT_SUCCESS);
}

