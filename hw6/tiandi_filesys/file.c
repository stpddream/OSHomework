#include "file.h"


extern Dev* cur_dev;
extern FileTable file_table;
extern iNodeTable inode_table;


int f_open(char* path, const char* mode) {
    
    char this_path[strlen(path)];
    strcpy(this_path, path);
    char* dirs;
        
    int cur_idx;    
    if(path[0] == '/') {
        //Set current directory
        cur_idx = 2;
    }
        
    printf("right here??? %s \n", this_path);
    dirs = strtok(this_path, "/");
    printf("current %s\n", dirs);
    
    //cur_idx = dir_lookup(cur_idx, dirs);
    int cnt = 0;
    char prev[FILE_NAME_MAX];
    while(dirs != NULL) {
        strcpy(prev, dirs);
        dirs = strtok(NULL, "/");        
        //cur_idx = dir_lookup(cur_idx);
        printf("current %s\n", dirs);        
        cnt++;
    }
            
    int inode_idx = fs_alloc_inode(cur_dev);
        
    printf("Count - 1 is %s\n", prev);
    printf("inode index is %d\n", inode_idx);
    iNode inode;
    fs_get_inode(&inode, inode_idx, cur_dev);        
    activate_inode(&inode, FT_FILE, prev);
    inode.size = 0;
             
    fs_update_inode(&inode, inode_idx, cur_dev);
    
    it_put(&inode, inode_idx);   
    int fd = ft_put(inode_idx, 0);         
    return fd;
}

int f_read(void* ptr, size_t size, size_t nmemb, int fd) {
    int inode_idx = ft_get_idx(fd);
    int cur_pos = ft_get_pos(fd);
    iNode* inode = it_get_node(inode_idx);
    return fl_read(cur_dev, inode, cur_pos, size * nmemb, ptr);          
}


int f_write(void* ptr, size_t size, size_t nmemb, int fd) {
    int inode_idx = ft_get_idx(fd);
    int cur_pos = ft_get_pos(fd);
    iNode* inode = it_get_node(inode_idx);
    fl_write(cur_dev, inode, cur_pos, size * nmemb, ptr);
    inode->size += size * nmemb;
    return 0;
}

int f_remove() {
    
    //remove datafile
    
    
}

int f_stat(int fd, char* buf) {
    int inode_idx = ft_get_idx(fd);
    iNode* inode = it_get_node(inode_idx);
    //Print stuff?? //how to do this??
    sprintf(buf, "File: %s\nSize: %d\n", 
            inode->name, inode->size);    
    return 0;
}
    

int f_close(int fd) {
    int inode_idx = ft_get_idx(fd);
    iNode* inode = it_get_node(inode_idx);
    fs_update_inode(inode, inode_idx, cur_dev);
    ft_remove(fd);
    it_remove(inode_idx);
    return 0;
}

int f_seek(int fd, long offset, int whence) {
    if(file_table.entries[fd] == NULL) return -1;
    file_table.entries[fd]->pos = offset;    
    return 0;
}


int f_rewind(int fd) {
    if(file_table.entries[fd] == NULL) return -1;
    file_table.entries[fd]->pos = 0;
    return 0;
}

/*
int f_opendir(char* path, const char* mode) {
    
}
*/


int f_mkdir(char* path) {
    int inode_idx = fs_alloc_inode(cur_dev);
    printf("inode index is %d\n", inode_idx);
    iNode inode;
    fs_get_inode(&inode, inode_idx, cur_dev);       
    activate_inode(&inode, FT_DIR, path);             
    fs_update_inode(&inode, inode_idx, cur_dev);    
    it_put(&inode, inode_idx);  
    
    iNode root_node;
    fs_get_inode(&root_node, ROOT_NODE, cur_dev);
    dir_add(&root_node, ROOT_NODE, path);  
    fs_update_inode(&root_node, ROOT_NODE, cur_dev);

    return 0;
}