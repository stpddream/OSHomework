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
#include "kernel_mem.h"

extern FileTable file_table;
Dev* cur_dev;

int main(int argc, char** argv) {
    

    FILE* fp;
    fp = fopen("testfile/disk", "w+");    
    cur_dev = dev_create(fp);    
    dev_init(cur_dev, 10240000);
    fs_init(cur_dev, 10240000);
              
    //Init tables
    
    ft_init();
    it_init();


    print_superblock(&cur_dev->superblock);
    iNode root;
    printf("@@@@@@@@ Directory Test @@@@@@@@@@\n");    
    printf("((((((( before good happends )))))))\n");

    f_mkdir("/good/");
    f_mkdir("/perfect/");

    printf("((((((( after good happends )))))))\n");

    printf("@@@@@@@ Two levels @@@@@@\n");
    f_mkdir("/good/etc");
    f_mkdir("/good/quite");
    
    //f_mkdir("/good/quite/super");
    //f_mkdir("/good/quite/haha");
    //f_mkdir("/good/quite/so");
    
    int fd = f_open("/good/super.c", "w");
    f_open("/good/hahah.o", "w");
    

    int idx = ft_get_idx(fd);    
    
    f_remove_dir("/good/");
       
    fs_get_inode(&root, ROOT_NODE, cur_dev);    
    list_dir(&root);
    
    
    printf("fd is %d\n", f_open("/good/super.c", "w"));
    printf("not exist %p\n", f_opendir("/good/"));
    printf("not exist %p\n", f_opendir("/good/quite/"));
    
   
    printf("index is %d\n", idx);

    return (EXIT_SUCCESS);
}

