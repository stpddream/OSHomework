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

void file_table_test() {
    ft_init();
    int i;
    for(i = 0; i < 10; i++) printf("fd: %d %d \n", ft_put(i, 0), file_table.size);
    
    
    ft_remove(5);
    ft_remove(7);
    ft_remove(3);
    
    printf("Current size is %d\n", file_table.size);
    
    printf("Printing right now\n");
}

void rw_test() {
     /*
    int inode_idx = fs_alloc_inode(cur_dev);    
    iNode inode;
    int fd = f_open("super.h", "r");
    
    int num = 46;
    
    char* good = "this is a very long long long long long long long long long long string";
    f_write(&good, sizeof(good), 1, fd);
    
    printf("File Descr %d\n", fd);
    
    char a[300];
    f_read(&a, sizeof(good), 1, fd);
    
    printf("read out %s\n", good);
    
    print_filetable();
    print_inodetable();
    */
}

void test_print_ibit() {
    
    char bits[4096];
    dev_read(bits, sizeof(bits), 1024, cur_dev);
    int s;
    for(s = 0; s < 4096 / 8; s++) printf("%s ", bytbi(bits[s]));
    printf("is on?? %d\n", ibit_is_on(cur_dev, 7)); 
    
}