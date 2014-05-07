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