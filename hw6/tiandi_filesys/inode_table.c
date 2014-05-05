#include "inode_table.h"

iNodeTable inode_table;


int it_init() {
    inode_table.size = 0;
}

int it_put(iNode* inode) {
    inode_table.entries[inode_table.size++] = inode;
    return inode_table.size;
}

int it_exist(int inode_idx) {
    int i;
    for(i = 0; i < inode_table.size; i++) {
        if(inode_idx == inode_table.entries[i]->inode_idx) return True;
    }
    return False;    
}