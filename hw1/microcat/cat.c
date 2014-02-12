#include "cat.h"

/**
 * Output content of a file specified by path
 * If path equals "-", will read from stdin
 * @param read_path is the file to be displayed
 * @param write_path is the file to be written based on the content
 * of readin file
 * @return -1 if error, 0 otherwise
 */
int cat(char* read_path, char* write_path) {
    
    //Process path of readin file/stdin and open iostream
    int rfd;
    if(strcmp(read_path, "-") == 0) rfd = 1;
    else {
        if((rfd = open(read_path, O_RDONLY)) == -1) {
            return -1;
        } 
    }
    
    //Process path of output file/stdout and open iostream
    int wfd = 1;
    if(write_path != NULL) {
        if((wfd = open(write_path, O_WRONLY)) == -1) {
            return -1;   
        }
    }
        
    //Incrementally read and write
    char buff[BUFF_SZ];
    int n;
    while((n = read(rfd, buff, BUFF_SZ)) > 0) {
        write(wfd, buff, n);
    }
    
    //Clean up
    close(rfd);
    close(wfd);
    
    return 0;
}
