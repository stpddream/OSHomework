#include "file_table.h"



FileTable filetable;

int ft_init() {
    filetable.size = 0;
    filetable.alloc_hd = 0;
    return 0;
}


int ft_put(int inode_idx, int protection) {    
    
    if(filetable.size >= MAX_N_FILE_OPEN) return -1;
    int fd = filetable.alloc_hd;
    
    FileEntry* new_entry = (FileEntry*)malloc(sizeof(FileEntry));
    new_entry->inode_idx = inode_idx;
    new_entry->protection = protection;
    filetable.entries[fd] = new_entry;
    
    
    //Increment allocation header
    int i;
    for(i = filetable.alloc_hd + 1; i < MAX_N_FILE_OPEN; i++) {
        if(filetable.entries[i] == NULL) break;
    }        
    filetable.alloc_hd = i;
    filetable.size++;
    return fd;
}

int ft_remove(int fd) {
    if(filetable.entries[fd] == NULL) return -1;
    FileEntry* entry = filetable.entries[fd];
    filetable.entries[fd] = NULL;
    free(entry);
    
    if(fd < filetable.alloc_hd) filetable.alloc_hd = fd;
    filetable.size--;
    return 0;
}


int ft_exist(int inode_idx) {
    int i;
    for(i = 0; i < MAX_N_FILE_OPEN; i++) {
        if(filetable.entries[i] == NULL) continue;
        if(filetable.entries[i]->inode_idx == inode_idx) return TRUE;
    }
    return FALSE;
}
