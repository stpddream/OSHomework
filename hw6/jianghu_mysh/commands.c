#include "commands.h"


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
                printf("---- More ----\r");     
                sleep(5);
                printf("happy\n");
                char enter = 0;
              
                // while (enter != '\r' && enter != '\n') { enter = getchar(); } 
                row = 2;
            }      
            ch++;
        }


    }
    
    
    
    
    
}
