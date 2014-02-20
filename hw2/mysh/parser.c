#include "parser.h"

extern HistoryList* hist_list;

void parse_args(char* cmd_str, char** args) {
    
        int i = 0;
        char* token;        //Temporary token
        token = strtok(cmd_str, " ");                    
        while(token) {           
            args[i++] = strip_space(token);
            token = strtok(NULL, " ");                              
        }        
        args[i] = NULL;
        
}


char* strip_space(char *str) {
    
    int i = -1;
    int wr = 0;    
    char ch;
    char* res_str = (char*)malloc(sizeof(char)*(strlen(str)));
    
    //Skip white space characters at the beginning
    while((ch = str[++i]) != '\0' && (isspace(ch) || ch == '\n')) ;
       
    //Move nonspace to the start of string
    while((ch = str[i++]) != '\0' && (!isspace(ch)) && ch != '\n') {     
        res_str[wr++] = ch;
    }
    res_str[wr] = '\0';        //Append '\0'
    return res_str;
    
}
