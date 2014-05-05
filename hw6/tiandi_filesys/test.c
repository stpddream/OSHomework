#include "test.h"

void ibit_test(Dev* device) {
    
    int i;
    for(i = 0; i < device->superblock.inode_count; i++) {
        printf("Allocated: %d\n", fs_alloc_inode(device));
    }
    
    for(i = 25; i < 600; i++) {
        fs_dealloc_inode(device, i);
    }

    fs_dealloc_inode(device, 3);
    fs_dealloc_inode(device, 2);
    print_ibit(device);
    
    fs_alloc_inode(device);
    fs_alloc_inode(device);
    fs_alloc_inode(device);
    fs_dealloc_inode(device, 3);
    printf("Allocted %d\n", fs_alloc_inode(device));
    
    print_ibit(device);
    
    
    
}
