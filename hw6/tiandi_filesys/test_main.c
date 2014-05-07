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
    
    int mfd = f_open("file", "w+");

    
    char* data = "wordisgoodl";
    char* another = "hohohohoh"; 
    
    int rt2 = f_write(data, strlen(data), 1, mfd);
    
    printf("rt2 %d\n", rt2);
    f_close(mfd);
    int hahafd = f_open("file", "a+");
    
    int rt3 = f_write(another, strlen(another), 1, hahafd);
    printf("rt3 is %d\n", rt3);
    printf("content: %s\n", another);
    
    
    f_close(hahafd);
    
    char result[50];
    int outfd = f_open("file", "r");
    int bytesss = f_read(result, strlen(another) + strlen(another), 1, outfd);
    printf("read %d\n", bytesss);
    printf("Actual is %s\n", result);
    
    
    /*
    
    char result[30];
    //f_seek(hahafd, 0, SEEK_SET);
    int rt4 = f_read(result, strlen(another) + strlen(data), 1, hahafd);
    printf("rt4 is %d\n", rt4);
    printf("actual data is %s\n", result);
     */
    
    
    /*
    f_mkdir("home");
    iNode node;
    fs_get_inode(&node, ROOT_NODE, cur_dev);
    set_cur_idx(3);
    f_mkdir("happy");
    
    iNode another;
    fs_get_inode(&another, 3, cur_dev);
    
    
    list_dir(&node);
    list_dir(&another);
    */
    return 0;
}

