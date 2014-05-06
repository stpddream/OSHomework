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
#include "file.h"
#include "ft_dir.h"

extern FileTable file_table;

Dev* cur_dev;

/*
 * 
 */
int main(int argc, char** argv) {
    int i;
    FILE* fp;
    fp = fopen("testfile/disk", "w+");    
    cur_dev = dev_create(fp);
    
    printf("now changes!!\n");
    
    dev_init(cur_dev, 10240000);
    fs_init(cur_dev, 10240000);
            
  //  printf("size of %d\n", sizeof(iNode));
  
    //Init tables
    ft_init();
    it_init();      
    
    
    
    printf("Number is %d\n", cur_dev->bootblock.fun);
    printf("%s\n", cur_dev->bootblock.have_fun);    
    print_superblock(&cur_dev->superblock);          
   
    //f_open("/file/good", "r");
    //f_mkdir("good");
    
    /*
    iNode root;

   
    
    f_mkdir("good");
    f_mkdir("perfect");
    fs_get_inode(&root, ROOT_NODE, cur_dev);    
    printf("Root name is : %s\n", root.name);
    printf("Root size is: %d\n", root.size);
    
    printf("now listing...\n");
    list_dir(&root);
    
    
    iNode another;    
    fs_get_inode(&another, 4, cur_dev);       
    printf("file name is %s\n", another.name);
    
    DirFileEntry entry;
    fl_read(cur_dev, &root, 0, DIR_ENTRY_SZ, &entry);
    
    
    printf("Entry name is %s\n", entry.file_name);        
    f_open("/file/quick/ha", "w");
    
    */
    
    iNode testNode;
    int inode_idx = fs_alloc_inode(cur_dev);
    fs_get_inode(&testNode, inode_idx, cur_dev);       
    printf("inode allocated %d\n", inode_idx);
    char test[10] = "lalala";
    char testOut[10];
    fl_write(cur_dev, &testNode, 0, 10, test);
    fl_read(cur_dev, &testNode, 0, 10, testOut);
    printf("out:\t %s\n", testOut);
    
    
    /*
    fseek(cur_dev->phys_data, 9728, SEEK_SET);     
    
    for(i = 0; i < 20; i++) {
        fread(&inode, 128, 1, cur_dev->phys_data);
        printf("inode blabla %d\n", inode.file_type);
    }*/    
    
//  printf("FD is %d\n", fd);

    
    
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

