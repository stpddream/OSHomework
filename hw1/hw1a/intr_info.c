#include "intr_info.h"


const char* INTR_PATH = "/proc/stat";
const char* INTERRUPT_ITEM = "intr";


/**
 * Read from /proc/stat file and extract number of interrupts 
 * @return number of total interrupts recorded by system since last boot
 */
int get_intr_info() {
  
    int total_count;
    FILE* fp;

    char item[60];
    if((fp = fopen(INTR_PATH, "r")) != NULL) {
        
        while(!feof(fp)) {        
            fscanf(fp, "%s %d\n", item, &total_count);
            if(strcmp(item, INTERRUPT_ITEM) == 0) {
                return total_count;
            }
        }        
        
    }          
    fclose(fp);
    return -1;
    
}
