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
    

    iNode root;
    
    printf("@@@@@@@@ Directory Test @@@@@@@@@@\n");

    //f_open("/file.h", "r");
        
    list_dir(&root);
    printf("((((((( before good happends )))))))\n");
    
    f_mkdir("/good/");        
    f_mkdir("/perfect/");
    printf("((((((( after good happends )))))))\n");
    
    fs_get_inode(&root, ROOT_NODE, cur_dev);     
    list_dir(&root);
    
    printf("@@@@@@@ Two levels @@@@@@\n");
    f_mkdir("/good/etc");
    f_mkdir("/good/quite");
    
    f_mkdir("/good/quite/super");
    f_mkdir("/good/quite/haha");
    f_mkdir("/good/quite/so");
    
    /*
    int fd = f_open("/good/quite/test.c", "r");
    f_close(fd);*/
    
    int lflag, fflag;
    
    lflag = FALSE;
    fflag = TRUE;
    
    char* curdir = "/good/quite";
    DirStream* dir_stream = f_opendir(curdir);
    DirFileEntry entry;
    iNode test_node;
    char display[FILE_NAME_MAX+1];
    
    if(!lflag && !fflag){
        while(f_readdir(dir_stream, &entry) != -1){
            if(strcmp(entry.file_name, ".") == 0) continue;
            if(strcmp(entry.file_name, "..") == 0) continue;
            strcpy(display, entry.file_name);
            printf("%s\t", display);
        }
        printf("\n");
    }else if(fflag && !lflag){
        while(f_readdir(dir_stream, &entry) != -1){
            if(strcmp(entry.file_name, ".") == 0) continue;
            if(strcmp(entry.file_name, "..") == 0) continue;
            strcpy(display, entry.file_name);
            fs_get_inode(&test_node, entry.inode_idx, cur_dev);
            if(test_node.file_type == FT_FILE){
                strcat(display, "*");
            } else if (test_node.file_type == FT_DIR){
                strcat(display, "/");
            } else if (test_node.file_type == FT_MOUNT){
                strcat(display, "@"); 
            }
            printf("%s\t", display);
        }
        printf("\n");        
    }else if(!fflag && lflag){
        
    }else{
        
    }
           
    f_closedir(dir_stream);

    return (EXIT_SUCCESS);
}

