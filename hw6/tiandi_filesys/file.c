#include "file.h"
#include "filesys_hd.h"

Dev* cur_dev;



int f_open(const char* path, const char* mode) {
    char* dirs;
    
    /*
    int inode_idx = fs_alloc_inode(cur_dev);
    iNode* inode = fs_get_inode(cur_dev, inode_idx);
    
    inode->nlink = 1;
   // inode->file_type = ;
    fs_update_inode(cur_dev, inode);
    */
    /*
    if(path[0] == '/') {
        //Set current directory
    }
        
    dirs = strtok(path, "/");
    while(dirs != NULL) {
        dirs = strtok(NULL, "/");
        
    }*/
    
}

    
    
