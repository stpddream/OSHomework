#include "file.h"
int f_open(const char* path, const char* mode) {
    char* dirs;
    if(path[0] == '/') {
        //Set current directory
    }
        
    dirs = strtok(path, "/");
    while(dirs != NULL) {
        dirs = strtok(NULL, "/");
    }
    
}

    
    
