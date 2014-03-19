#include "parser.h"
#include "jobs.h"

int parse_args(char* line, char** commands) {
    char* prv;
    int count = 0;
    int back_flag = 0;
	
    while(*line != '\0'){
        
        while(*line == ' ' && *line != '\0') line++;    //Skip white spaces        
        
        if(*line == '&' || *line == ';'){
            printf("-mysh:\tsyntax error\n");
            return 0;
        }

        prv = line; //Start of command        
           
        //Find the next delimiter
        while(*line != '&' && *line != ';' && *line != '\0') line++;
        
        if(*line == '&') back_flag = 1;
        else back_flag = 0;
        
        //Set the end of command flag
        if(*line != '\0') *line++ = '\0';
        commands[count] = malloc((1 + strlen(prv))*sizeof(char));      
        
        //Set background flag
        if(back_flag) commands[count][0] = '&';     
        else commands[count][0] = '%';
                     
        strcpy(commands[count++] + 1, prv);            
    }
    
    return count;
}


int parse_space(char* cmd_str, char** args){
    int i = 0;
    char* tok;
    tok = strtok(cmd_str, " \t\n");
    while(tok!=NULL){
        args[i] = malloc(strlen(tok)*sizeof(char));
        strcpy(args[i++], tok);
        tok = strtok(NULL, " \t\n");
    }
    return i;
}

