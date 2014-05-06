#include "util.h"

/**
 * Print a number is binary form
 * @param x number to print
 * @return character contains the binary form of a number
 */
const char *bytbi(int x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

/**
 * Turn all bytes on in an array
 */
void arr_on(char* arr, int size) {
    int i;
    for(i = 0; i < size; i++) {
        arr[i] = ~0;
    }    
}

void arr_init(char* arr, int size, int val) {
    int i;
    for(i = 0; i < size; i++) {
        arr[i] = val;
    }  
}


void print_superblock(Superblock* sb) {
       
    printf("==== Superblock ==== \n");
    printf("Num of inodes: %d\n", sb->inode_count);
    printf("Num of data blocks: %d\n", sb->databl_count);
    
    printf("Num of free inodes: %d\n", sb->freeinode_count);
    printf("Num of free data blocks: %d\n", sb->freeblock_count);
  
    printf("Ibit offset: %d\n", sb->ibit_offset);
    printf("Abit offset: %d\n", sb->abit_offset);
    printf("Inode offset: %d\n", sb->inode_offset);
    printf("Data offset: %d\n", sb->data_offset);
    
    printf("Block size: %d\n", sb->block_size);
    printf("Disk size: %d\n", sb->size);
    printf("====    ====\n");
}

// Debug functions
void print_ibit(Dev* device) {
    printf("=== Ibit === \n");
    int i;
    char ibit[BLOCK_SZ];
    fseek(device->phys_data, IBIT_BEGIN, SEEK_SET);
    fread(ibit, sizeof(ibit), 1, device->phys_data);   
    for(i = 0; i < BLOCK_SZ; i++) printf("%s ", bytbi(ibit[i]));
    printf("===      === \n");
}


extern FileTable file_table;
void print_filetable() {    
    int i;
    printf("===== File Table =====\n");
    for(i = 0; i < MAX_N_FILE_OPEN; i++) {
        if(file_table.entries[i] != NULL) {
            printf("[Index: %d, Pos: %d]\n", file_table.entries[i]->inode_idx, file_table.entries[i]->pos);
        }
    }    
    printf("======================\n");
}

extern iNodeTable inode_table;

void print_inodetable() {
    int i;
    printf("===== inode table ======\n");
    for(i = 0; i < MAX_N_FILE_OPEN; i++) {
        if(inode_table.entries[i] != NULL) {
            printf("[Index: %d]\n", inode_table.entries[i]->inode_idx);
        }
    }    
    printf("========================\n");
}

