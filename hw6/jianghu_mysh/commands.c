#include "commands.h"

int ls(char* flags) {
    
    
}


int cat(int fd) {
    char buffer[512];
    int act_size;
    do {
       // act_size = f_read(buffer, sizeof(buffer), 1, fd);
        printf("%s", buffer);
    } while(act_size != 0);
    return 0;
}





/** More coming */
int more(char* content) {    
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int row = w.ws_row - 1;
    int col = w.ws_col;
    
    char* ch = content;
    
    while(1) {
        while(ch != '\0') {                
            putchar(*ch);
            switch(*ch) {
                case '\n':
                    row--;
                    col = w.ws_col;
                    break;
                default:
                    col--;       
                    if(col == 0) {
                        row--;
                        col = w.ws_col;
                    }
            }
            if(row == 1) {
                printf("---- More ----");                     
                sleep(3);
                printf("\r");
                int i;
                for(i = 0; i < w.ws_col; i++) printf(" ");
                //while (enter != '\r' && enter != '\n') { enter = getchar(); } 
                row = 2;
            }      
            ch++;
        }


    }
    
}



