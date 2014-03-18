#include "parse.h"

int parse_cmds(char* cmdline, char** cmdlines ){
    char* prv;
    int i = 0;
    int flag;  
	
    i = 0;
    while(*cmdline != '\0'){
        //if more than one delimiters, print syntax error and quit the loop
        if(*cmdline == '&' || *cmdline == ';'){
            printf("-mysh:\tsyntax error\n");
            return 0;
        }
        
        //set the start point of the new commandline
        prv = cmdline;
        
        //skip the non-delimiter chars
        while(*cmdline != '&' && *cmdline != ';' && *cmdline != '\0'){
            cmdline++;
        }

        //set foreground/background jobs
        if(*cmdline == '&'){
            flag = JOB_BACK;
        }else{
            flag = JOB_FORE;
        }
        
        //allocate memory and copy string to cmdlines array
        if(*cmdline!= '\0') *cmdline++ = '\0';
        cmdlines[i] = malloc((1+strlen(prv))*sizeof(char));
        cmdlines[i][0] = (flag == JOB_FORE? '%' : '&');
        strcpy(cmdlines[i++]+1, prv);            
    }
    
    //return the number of command lines parsed
    return i;
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
