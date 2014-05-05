#include "device_ctrl.h"


/* Attach a simulation file to a new device */
Dev* dev_create(FILE* disk) {
    Dev* new_dev = (Dev*)malloc(sizeof(Dev));
    new_dev->phys_data = disk;
    return new_dev;
}


/**
 * Init disk simulation file to size size, with all bytes default value "0"
 */
int dev_init(Dev* device, int size) {
    int i;
    char zero = 0;
    for(i = 0; i < size; i++) {
        fwrite(&zero, sizeof(char), 1, device->phys_data);        
    }    
    return 0;
}



int dev_read(void* data, int size, int pos, Dev* device) {
    fseek(device->phys_data, pos, SEEK_SET);    
    fread(data, size, 1, device->phys_data);    
    return 0;
}

int dev_write(void* data, int size, int pos, Dev* device) {
    fseek(device->phys_data, pos, SEEK_SET);    
    fwrite(data, size, 1, device->phys_data);    
    return 0;
}
