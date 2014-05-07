#include "file_util.h"

extern User* cur_user;
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
         
    inode->uid = cur_user->uid;
    inode->gid = cur_user->gid;    
    inode->permission = get_pm_val(PM_READ | PM_WRITE, PM_READ | PM_WRITE, PM_READ);
    
        
    strcpy(inode->name, name);
    inode->size = 0;
    return 0;
}


int check_permission(iNode* inode, int mode) {
    
    char pch;
    
    //By owner
    if(cur_user->uid == inode->uid) {
        pch = inode->permission / 100;
    }
    //By group member
    else if(cur_user->gid == inode->gid) {
        pch = inode->permission / 10 % 10;
    }
    //Random user
    else {
        pch = inode->permission % 10;
    }
    
    //PM_READ
    if((((mode >> 2) & 1) == 1) && ((pch >> 2) & 1) == 0) {
        return FALSE;
    } 
    if(((mode >> 1) & 1) == 1 && ((pch >> 1) & 1) == 0) {
        return FALSE;
    }
    return TRUE;    
}