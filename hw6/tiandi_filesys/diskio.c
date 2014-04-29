#include "diskio.h"

/**
 * Create a disk simulation file of size size, with all bytes default value "0"
 */
int init_disk(FILE* disk, int size) {
    int i;
    char zero = 0;
    for(i = 0; i < size; i++) {
        fwrite(&zero, sizeof(char), 1, disk);        
    }    
    return 0;
}
