/* 
 * File:   test_main.c
 * Author: Panda & Jacy
 *
 * Created on April 28, 2014, 8:00 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "bitmap.h"
#include "util.h"
#include "device_ctrl.h"
#include "filesys_util.h"
#include "file_table.h"
#include "file.h"
#include "ft_dir.h"

extern FileTable file_table;

Dev* cur_dev;

/*
 * 
 */
int main(int argc, char** argv) {
    

    FILE* fp;
    fp = fopen("testfile/disk", "w+");    
    cur_dev = dev_create(fp);    
    dev_init(cur_dev, 10240000);
    fs_init(cur_dev, 10240000);
              
    //Init tables
    
    ft_init();
    it_init();      
    

    print_superblock(&cur_dev->superblock);
    iNode root;
    
    printf("@@@@@@@@ Directory Test @@@@@@@@@@\n");    
    printf("((((((( before good happends )))))))\n");
    
    f_mkdir("/good/");        
    f_mkdir("/perfect/");

    printf("((((((( after good happends )))))))\n");

    printf("@@@@@@@ Two levels @@@@@@\n");
    f_mkdir("/good/etc");
    f_mkdir("/good/quite");
    
    //f_mkdir("/good/quite/super");
    //f_mkdir("/good/quite/haha");
    //f_mkdir("/good/quite/so");
    
    int fd = f_open("/good/super.c", "w");
    f_open("/good/hahah.o", "w");
    

    int idx = ft_get_idx(fd);    
    
    f_remove_dir("/good/");
       
    fs_get_inode(&root, ROOT_NODE, cur_dev);    
    list_dir(&root);
    
    
    printf("fd is %d\n", f_open("/good/super.c", "w"));
    printf("not exist %p\n", f_opendir("/good/"));
    printf("not exist %p\n", f_opendir("/good/quite/"));
    
   
    printf("index is %d\n", idx);


//   ibit_on(cur_dev, 7);
    
         
  /*
    int good_idx = dir_lookup(&root, "good");
    
    printf("Processing good\n");
    iNode good;
    fs_get_inode(&good, good_idx, cur_dev);
    list_dir(&good);
    
    int quite_idx = dir_lookup(&good, "quite");
    iNode quite;
    fs_get_inode(&quite, quite_idx, cur_dev);
    list_dir(&quite);
    
    printf("===================================\n");
    
    
    printf("readf here\n");
    /* Read file doesn't exist */
    /*
    int readf = f_open("/superfile.h", "r");    
    printf("Readf %d\n", readf);
    char* perfect = "hohoho";
    printf("Status is %d\n", f_write(perfect, sizeof(perfect), 1, readf));
    */

    /* Read to write only file */    
    /*
    int writef = f_open("/supergre.h", "w");
    int writef2 = f_open("/hihihihi.h", "w");
    
    int iidx = ft_get_idx(writef2);
    printf("what about writef %d\n", writef);
    
     
    printf("===== Before Reading ======\n");
    
    fs_get_inode(&root, ROOT_NODE, cur_dev);    
    list_dir(&root);
    

 
    printf("which one??\n");
    printf("after\n");
       
    
    printf("before removing\n");
    f_remove("/hihihihi.h");
    
    printf("===== After removing =====\n");
    fs_get_inode(&root, ROOT_NODE, cur_dev);
    list_dir(&root);
    
    
    iNode hohoho;
    
    */
    /*
    fs_get_inode(&removed, iidx, cur_dev);
    
    printf("index %d\n", iidx);
    
    
    
    printf("is on %d\n", ibit_is_on(cur_dev, iidx));


    Dev* device = cur_dev;

    char bits[4096];
    dev_read(bits, sizeof(bits), IBIT_BEGIN, cur_dev);

    printf("ibit begin %d\n", IBIT_BEGIN);
    int s;
    for(s = 0; s < 4096; s++) printf("%c ", bits[s]);
    
    */
    /*
    char* stuff = "great job\n";
    printf("size of stuff %d\n", sizeof(stuff));
    f_write(stuff, sizeof(stuff), 1, writef);
   */
    /*
    
    char readout[20];        
    printf("Status: %d \n", f_read(readout, sizeof(stuff), 1, writef));   
    

        
    int inode_idx = ft_get_idx(writef);

    iNode* inode = it_get_node(inode_idx);
    printf("size of node %d", inode->size);
    printf("Inode another here %d\n", inode->file_type);        
    f_close(writef);
    
    fl_read(cur_dev, inode, 0, sizeof(stuff), readout);
    printf("read out something?? %s\n", readout);
    
    
    print_filetable();
   
    /* Write to read only file */
    /*
    int readf = f_open("/supergreat.h", "r");
    printf("read f is %d\n", readf);
    f_read(readout, sizeof(stuff), 1, readf);
    printf("Read out!! %s\n", readout);
    printf("seg!!\n");
    
    f_remove("/supergreat.h");
    
    printf("===== Before removal =====\n");
    list_dir(&root);    
    printf("===== After removal =====\n");
    list_dir(&root);
    */
    
    //Test iNode table
    /*    printf("Inode table test\n");
    iNode* inode = (iNode*)malloc(sizeof(iNode));
    printf("ioioi\n");
    inode->file_type = 23;
    it_put(inode, 23);
    printf("before??\n");
    
    iNode* hahanode = it_get_node(23);
    printf("hahahahho %d\n", hahanode->file_type);
    
    */
    
    /*
    iNode another;    
    fs_get_inode(&another, 4, cur_dev);       
    printf("file name is %s\n", another.name);
    
    DirFileEntry entry;
    fl_read(cur_dev, &root, 0, DIR_ENTRY_SZ, &entry);
    
    
    printf("Entry name is %s\n", entry.file_name);        
    f_open("/file/quick/ha", "w");
    
    
    int sub_idx = dir_lookup(&root, "good");
    printf("index is %d\n", sub_idx);
    */
    
    
    
    
    
    
    /*
    int inode_idx = fs_alloc_inode(cur_dev);    
    iNode inode;
    int fd = f_open("super.h", "r");
    
    int num = 46;
    
    char* good = "this is a very long long long long long long long long long long string";
    f_write(good, sizeof(good), 1, fd);
    
    printf("File Descr %d\n", fd);
    
    char a[300];
    f_read(&a, sizeof(good), 1, fd);
    
    printf("read out %s\n", good);
    
    
    char perfect[10] = "hahahahaha";
    int another_idx = fs_alloc_inode(cur_dev);
    iNode another_inode;
    fs_get_inode(&another_inode, another_idx, cur_dev);
    f_write(perfect, sizeof(perfect), 1, fd);
    
    char b[200];
    f_read(&b, sizeof(perfect), 1, fd);
    printf("another: %s\n", b);
    */
    
    
    
    
    

    
    
    /*
    fseek(cur_dev->phys_data, 9728, SEEK_SET);     
    
    for(i = 0; i < 20; i++) {
        fread(&inode, 128, 1, cur_dev->phys_data);
        printf("inode blabla %d\n", inode.file_type);
    }*/    
    
//  printf("FD is %d\n", fd);

/*
    DirStream* res = f_opendir("/");
    DirFileEntry dir;
    printf("open dir inode = %d\n", res->inode_idx);
    printf("open dir pos = %d\n", res->pos);
    
    while(f_readdir(res, &dir) != -1){
        printf("filename: %s\n", dir.file_name);
    }
    
    f_closedir(res);*/
    return (EXIT_SUCCESS);
}

