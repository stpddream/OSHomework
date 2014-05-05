/* 
 * File:   filetable.h
 * Author: Panda & Jacy
 *
 * Created on May 3, 2014, 11:03 PM
 */

#ifndef FILETABLE_H
#define	FILETABLE_H

#include <stdio.h>


#define MAX_N_FILE_OPEN 20

extern FileTable filetable;

typedef struct {   
    int inode_idx;
    int pos;
    int protection;
    
} FileEntry;



typedef struct {
    FileEntry* entries[MAX_N_FILE_OPEN];
    int size;
} FileTable;

int ft_put(int fd, int inode_idx, int protection) {    
    if(filetable.entries[fd] != NULL) return -1;
    FileEntry* new_entry = (FileEntry*)malloc(sizeof(FileEntry));
    new_entry->inode_idx = inode_idx;
    new_entry->protection = protection;
    filetable.entries[fd] = new_entry;
    return 0;
}

int ft_remove(int fd) {
    if(filetable.entries[fd] == NULL) return -1;
    FileEntry* entry = filetable;
    filetable.entries[fd] = NULL;
    free(entry);
    return 0;
}


int ft_exist() {
    
}


#endif	/* FILETABLE_H */

