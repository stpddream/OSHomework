#include "commands.h"
int more(char* content) {    
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int row = w.ws_row - 1;
    int col = w.ws_col;
    
    char* ch = content;
    while(ch != '\0') {
        
        if(ch == '\n') {
            
        }
        
    }
    
    
    
}
