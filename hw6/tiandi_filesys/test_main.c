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
    
    
    iNode bigNode;
    int idx = fs_alloc_inode(cur_dev);
    printf("allocated inode = %d\n", idx);
    fs_get_inode(&bigNode, idx, cur_dev);
    char* testString = "abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abc abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abcdef abc";    
    int ssize = strlen(testString)+1;
    char outString[ssize];
    
    printf("size %d\n", ssize);
    
    fl_write(cur_dev, &bigNode, 0, ssize, testString);
    fl_read(cur_dev, &bigNode, 0, ssize, outString);
    
    printf("read string%s\n", outString);
    
    return (EXIT_SUCCESS);
}

