#include "inode_table.h"

iNodeTable inode_table;


void it_init() {
    inode_table.size = 0;
}

int it_put(iNode* inode, int inode_idx) {
    
    iNodeEntry* entry = (iNodeEntry*)malloc(sizeof(iNodeEntry));    
    inode_table.entries[inode_table.size++] = entry;
    entry->inode = inode;
    entry->inode_idx = inode_idx;
    return inode_table.size;
}


iNode* it_get_node(int inode_idx) {
    int i;
    for(i = 0; i < inode_table.size; i++) {
        if(inode_idx == inode_table.entries[i]->inode_idx) 
            return inode_table.entries[i]->inode;
    }
    return NULL;        
}

int it_exist(int inode_idx) {
    int i;
    for(i = 0; i < inode_table.size; i++) {
        if(inode_idx == inode_table.entries[i]->inode_idx) return TRUE;
    }
    return FALSE;    
}

int it_remove(int inode_idx) {  
    iNode* inode = it_get_node(inode_idx);            
    if(inode == NULL) return -1;
    inode_table.size--;
    free(inode);           
    return 0;
}