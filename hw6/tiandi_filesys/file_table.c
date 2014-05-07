#include "file_table.h"



FileTable file_table;

int ft_init() {
    file_table.size = 0;
    file_table.alloc_hd = 0;
    return 0;
}


int ft_put(int inode_idx, int protection) {    
    
    if(file_table.size >= MAX_N_FILE_OPEN) return -1;
    int fd = file_table.alloc_hd;
    
    FileEntry* new_entry = (FileEntry*)malloc(sizeof(FileEntry));
    new_entry->inode_idx = inode_idx;
    new_entry->protection = protection;
    file_table.entries[fd] = new_entry;
    
    
    //Increment allocation header
    int i;
    for(i = file_table.alloc_hd + 1; i < MAX_N_FILE_OPEN; i++) {
        if(file_table.entries[i] == NULL) break;
    }        
    file_table.alloc_hd = i;
    file_table.size++;
    return fd;
}

int ft_get_idx(int fd) {
    if(file_table.entries[fd] == NULL) return -1;
    return file_table.entries[fd]->inode_idx;
}

int ft_get_perm(int fd) {
    if(file_table.entries[fd] == NULL) return FALSE;
    return file_table.entries[fd]->protection;
}

int ft_get_pos(int fd) {
    if(file_table.entries[fd] == NULL) return -1;
    return file_table.entries[fd]->pos;
}


int ft_set_pos(int fd, int pos) {
    if(file_table.entries[fd] == NULL) return -1;
    file_table.entries[fd]->pos = pos;
}



int ft_remove(int fd) {
    if(file_table.entries[fd] == NULL) return -1;
    FileEntry* entry = file_table.entries[fd];
    file_table.entries[fd] = NULL;
    free(entry);
    
    if(fd < file_table.alloc_hd) file_table.alloc_hd = fd;
    file_table.size--;
    return 0;
}


int ft_exist(int inode_idx) {
    int i;
    for(i = 0; i < MAX_N_FILE_OPEN; i++) {
        if(file_table.entries[i] == NULL) continue;
        if(file_table.entries[i]->inode_idx == inode_idx) return TRUE;
    }
    return FALSE;
}
