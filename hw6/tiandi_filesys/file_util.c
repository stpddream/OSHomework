#include "file_util.h"


/**
 * Fill default inode info
 * @param inode
 * @param file_type
 * @param name
 * @return 
 */
int activate_inode(iNode* inode, int file_type, char* name) {    
    inode->nlink = 1;
    inode->file_type = file_type;
    inode->mtime = time(0);
    inode->ctime = time(0);
    inode->atime = time(0);
    strcpy(inode->name, name);
    inode->size = 0;
    return 0;
}

/*
int f_remove_file(char* path) {
    
    /* Parse Path */
    char* dirs;/*
    int cur_idx;    
    char this_path[strlen(path) + 1];
    
    if(path[0] == '/') {
        //Set current directory
        cur_idx = 2;
        strcpy(this_path, path + 1);
    }
    else {
        cur_idx = cur_dir_idx;
        strcpy(this_path, path);
    }
        
    dirs = strtok(this_path, "/");
   
    iNode cur_node;    
    int parent_idx = cur_idx;
    int prev_idx = cur_idx;
    fs_get_inode(&cur_node, cur_idx, cur_dev);            
    cur_idx = dir_lookup(&cur_node, dirs);*/
/*
    int cnt = 0;
    char prev_name[FILE_NAME_MAX];*/
    //printf("[%s, %d, %d, %d]\n", dirs, cur_idx, prev_idx, parent_idx);
    //printf("so it's here?? cur_idx %d\n", cur_idx);
    //printf("right now examining %s\n", dirs);
    /*
    if(cur_idx == -1) return -1;

    while(dirs != NULL) {        
        parent_idx = prev_idx;
        prev_idx = cur_idx;       
        strcpy(prev_name, dirs);
        dirs = strtok(NULL, "/");         

        if(dirs == NULL) break;
        fs_get_inode(&cur_node, cur_idx, cur_dev);
        cur_idx = dir_lookup(&cur_node, dirs);    
        if(cur_idx == -1) return -1;          
        cnt++;
    }    
    
    fs_remove_file(cur_dev, prev_idx);                
    return 0;
}
*/
