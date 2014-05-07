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
#include "kernel_usr.h"
#include "kernel_mem.h"

extern Dev* cur_dev;

extern FileTable file_table;
extern User* users[3];

int main(int argc, char** argv) {
    
    
    FILE* fp;
    fp = fopen("testfile/disk", "w+");
    cur_dev = dev_create(fp);

    dev_init(cur_dev, 10240000);
    fs_init(cur_dev, 10240000);
    
    //Init tables
    ft_init();
    it_init();
    user_init();
    
    set_user(users[0]);
    set_cur_idx(2);
    int cur_dir_idx = 2;
    f_mkdir("home");
    iNode node;
    fs_get_inode(&node, ROOT_NODE, cur_dev);
    set_cur_idx(3);
    f_mkdir("happy");
    
    iNode another;
    fs_get_inode(&another, 3, cur_dev);
    
    
    list_dir(&node);
    list_dir(&another);
    
    return 0;
}

