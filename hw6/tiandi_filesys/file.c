#include "file.h"



Dev* cur_dev;
extern FileTable file_table;
extern iNodeTable inode_table;


int f_open(const char* path, const char* mode) {
    //char* dirs;
        
    int inode_idx = fs_alloc_inode(cur_dev);
    iNode inode;
    fs_get_inode(&inode, inode_idx, cur_dev);
    
    inode.nlink = 1;
    inode.file_type = FT_FILE;
    inode.mtime = time(0);
    inode.ctime = time(0);
    inode.atime = time(0);
    strcpy(inode.name, path);
    inode.size = 0;
    fs_update_inode(&inode, inode_idx, cur_dev);
    
    it_put(&inode);
    int fd = ft_put(inode_idx, 0);
    
    /*
    if(path[0] == '/') {
        //Set current directory
    }
        
    dirs = strtok(path, "/");
    while(dirs != NULL) {
        dirs = strtok(NULL, "/");
        
    }*/
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
    return 0;
}

int f_remove();

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
