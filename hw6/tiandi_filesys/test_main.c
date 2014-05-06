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
    
    f_mkdir("/la"); 
    //f_mkdir("/yo"); 
    //f_mkdir("/ha"); 

    DirStream* res = f_opendir("/");
    DirFileEntry dir;
    printf("open dir inode = %d\n", res->inode_idx);
    printf("open dir pos = %d\n", res->pos);
    
    while(f_readdir(res, &dir) != -1){
        printf("filename: %s\n", dir.file_name);
    }
    
    f_closedir(res);
    return (EXIT_SUCCESS);
}

