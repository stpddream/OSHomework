#include "parser.h"
#include "jobs.h"

extern HistoryList* hist_list;

int parse_args(char* cmdline, char** cmdlines ){
    char* prv;
    int i = 0;
    int flag;  
	
    i = 0;
    while(*cmdline != '\0'){
        if(*cmdline == '&' || *cmdline == ';'){
            printf("-mysh:\tsyntax error\n");
            return 0;
        }

        prv = cmdline;

        while(*cmdline != '&' && *cmdline != ';' && *cmdline != '\0'){
            cmdline++;
        }

        if(*cmdline == '&'){
            flag = JOB_BACK;
        }else{
            flag = JOB_FORE;
        }

        if(*cmdline!= '\0') *cmdline++ = '\0';
        cmdlines[i] = malloc((2+strlen(prv))*sizeof(char));
        cmdlines[i][0] = (flag == JOB_FORE? '%' : '&');
        strcpy(cmdlines[i]+1, prv);            
        if(flag == JOB_BACK){
            printf("char is %c\n", cmdlines[i][strlen(prv)]);
            cmdlines[i][strlen(prv)+1] = '&';
            cmdlines[i][strlen(prv)+2] = '\0';
        }
        i++;
    }

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
