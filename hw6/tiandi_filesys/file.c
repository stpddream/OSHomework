#include "file.h"


Dev* cur_dev;



int f_open(const char* path, const char* mode) {
    char* dirs;
    
    
    int inode_idx = fs_alloc_inode(cur_dev);
    iNode* inode = fs_get_inode(cur_dev, inode_idx);
    
    inode->nlink = 1;
    inode->file_type = FT_FILE;
    inode->mtime = time(0);
    inode->ctime = time(0);
    inode->atime = time(0);
    inode->name = path;
    inode->size = 0;
    fs_update_inode(cur_dev, inode);
    
    /*
    if(path[0] == '/') {
        //Set current directory
    }
        
    dirs = strtok(path, "/");
    while(dirs != NULL) {
        dirs = strtok(NULL, "/");
        
    }*/
    
}

    
    
