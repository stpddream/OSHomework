#include "ft_dir.h"

extern Dev* cur_dev;


int dir_add(iNode* dir_inode, int inode_file_idx, char* name) {    
    DirFileEntry* entry = (DirFileEntry*)malloc(sizeof(DirFileEntry));
    strcpy(entry->file_name, name);
    entry->inode_idx = inode_file_idx;    
    fl_write(cur_dev, dir_inode, dir_inode->size, DIR_ENTRY_SZ, entry);    
    dir_inode->size += DIR_ENTRY_SZ;    
    return 0;
}


int dir_lookup(iNode* dir_inode, char* file_name) {
    int i;
    DirFileEntry entry;
    for(i = 0; i < dir_inode->size / DIR_ENTRY_SZ; i++) {
        fl_read(cur_dev, dir_inode, i * DIR_ENTRY_SZ, DIR_ENTRY_SZ, &entry);
        if(strcmp(entry.file_name, file_name) == 0) return entry.inode_idx;
    }
    return -1;    
}


int dir_remove_file(iNode* dir_inode, int dir_inode_idx, int inode_file_idx) {
    
    int i;
    DirFileEntry cur_entry;
    for(i = 0; i < dir_inode->size / DIR_ENTRY_SZ; i++) {
        fl_read(cur_dev, dir_inode, i * DIR_ENTRY_SZ, DIR_ENTRY_SZ, &cur_entry);
        if(cur_entry.inode_idx == inode_file_idx) break;                  
    }
    
    if(i == dir_inode->size / DIR_ENTRY_SZ) return -1;
       
    DirFileEntry entry;    
    fl_read(cur_dev, dir_inode, dir_inode->size - DIR_ENTRY_SZ, DIR_ENTRY_SZ, &entry);    
    fl_write(cur_dev, dir_inode, i * DIR_ENTRY_SZ, DIR_ENTRY_SZ, &entry);
    
    dir_inode->size -= DIR_ENTRY_SZ;        
    fs_update_inode(dir_inode, dir_inode_idx, cur_dev);
    return 0;
}



/*** Debug func ***/
void list_dir(iNode* node) {
    int i;
    DirFileEntry entry;
    
    printf("size is %d\n", node->size);
    for(i = 0; i < node->size / DIR_ENTRY_SZ; i++) {
        printf("newnew\n");
        fl_read(cur_dev, node, i * DIR_ENTRY_SZ,  DIR_ENTRY_SZ, &entry);
        printf("file: %d %s\n", entry.inode_idx, entry.file_name);
    }
}
