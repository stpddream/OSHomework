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
#include "inode_list.h"
#include "commands.h"
#include "usr.h"

Dev* cur_dev;
char cur_dir[MAX_PATH_LEN];
User* users[3];

int main() {

    FILE* fp;
    fp = fopen("testfile/disk", "w+");
    cur_dev = dev_create(fp);

    dev_init(cur_dev, 10240000);
    fs_init(cur_dev, 10240000);

    //Init tables
    ft_init();
    it_init();
    
    user_init();
    
    while(user_login() == -1);

    //append root to current path
    inode_append(2);
    //clear the path 
    cur_dir[0] = '\0';
    gen_path(cur_dir);


    cmd_mkdir("/test1");
    cmd_mkdir("/test2");
    cmd_mkdir("/test3");
    
    cmd_ls("Fl");

    cmd_cd("test1");
    printf("pwwwwwwwwwwwwwwwwwwddddddddddddddddddddddd:\n");
    cmd_pwd();
    cmd_mkdir("/test1/test_a");
    cmd_cd("test_a");
    printf("pwwwwwwwwwwwwwwwwwwddddddddddddddddddddddd:\n");

    cmd_pwd();

    
    user_clean();


    return 0;
}
