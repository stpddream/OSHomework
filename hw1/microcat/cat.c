#include "cat.h"

/**
 * Output content of a file specified by path
 * If path equals "-", will read from stdin
 * @param read_path is the file to be displayed
 * @param write_path is the file to be written based on the content
 * of readin file
 * @return -1 if error, 0 otherwise
 */
int cat(char* read_path, char* write_path, int app_flag) {
           
    //Process path of readin file/stdin and open iostream
    int rfd = 1;
    if(read_path[0] == '-' && read_path[1] == '\0') rfd = 1;
    else if((rfd = open(read_path, O_RDONLY)) == -1) {
        return -1;        
    }   
    
     
    //Process path of output file/stdout and open iostream    
    int w_flags = O_WRONLY | O_CREAT | ((app_flag == APP_ON) ? O_APPEND : O_TRUNC);
    
    int wfd = 1;
    if(write_path != NULL && 
        (wfd = open(write_path, w_flags, 0640)) == -1) {
        return -1;           
    }
    

    //Incrementally read and write
    char buff[BUFF_SZ];
    int n;
    while((n = read(rfd, buff, BUFF_SZ)) > 0) {
        if(write(wfd, buff, n)  == -1) {                    
            return -1;
        }
    }
    
    //Clean up
    //STDIN/OUT shouldn't be closed
    if(rfd != 1) {
        if(close(rfd) == -1) return -1; 
    }
    if(wfd != 1) {
        if(close(wfd) == -1) return -1;   
    }
    
    return 0;
}
