/* 
 * Project: mysh
 * File:   main.c
 * Author: Panda
 *
 * Created on February 17, 2014, 4:42 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <sys/types.h>


#include "parser.h"
#include "cmd_control.h"
#include "cmd_history.h"
#include "util.h"
#include "jobs.h"

#define MAX_CMD 20

char* path;
char** args;

HistoryList* hist_list;

/**
 * Clean up before exit, prevent memory leak
 */
void clean_up() {
    
    int i = 0;
    
    while(i < hist_list->size) {
        int j = 0;
        while(hist_list->contents[i][j] != NULL) {
            free(hist_list->contents[i][j]);
            j++;
        }
        i++;
    }
    free(hist_list);
    free(args);
}


int main(int argc, char** argv) {        
    
    jobs_init();
        
    char* input;
    char** cmdlines = malloc(MAX_CMD*sizeof(char*));
    char** args = malloc(MAX_CMD*sizeof(char*));
    int i, j;
    int n_cmd, n_args;
    
    while(1){
        if((input = readline(""))!=NULL){
            jobs_init();
            n_cmd = parse_args(input, cmdlines);
            printf("Command num: %d", n_cmd);
            for(i = 0; i < n_cmd; i++){
                
                Job* new_job = job_create((cmdlines[i][0] == '&'? JOB_BACK:JOB_FORE),cmdlines[i]+1,0);  
                jobs_add(new_job);
                /*
                n_args = parse_space(cmdlines[i]+1, args);
                for(j = 0; j < n_args; j++){
                    printf("%s\n",args[j]);
                }*/

            }
            
	    //print_jobs();
              jobs_print(); 
        }
        // Free input.
        free(input);
    }
   return 0; 

    
    


    exit(0);
    
    
    char* hist_size_ch = getenv("HISTSIZE");
    int hist_size;
    if(hist_size_ch == NULL || int_valueof(hist_size_ch, &hist_size) == -1) {
        hist_size = MAX_HIST;
    }
    hist_list = histlst_create(hist_size);    

    printf("======== Welcome to ^ ^ ST Terminal! ========= \n");
    
    while(1) {
        char* curDir = getenv("PWD");     
        printf("%s >> ", curDir);      
        
        char* cmd = NULL;   
        args = (char**)malloc(sizeof(char*)*MAX_ARG_NUM);
        size_t size;
          
        if(getline(&cmd, &size, stdin) == -1) {
            fprintf(stderr, "IO Error\n");
        }
                              
        //Parse arguments
        parse_args(cmd, args);
        
        //Execute 
        path = args[0];
        exec_sh(path, args);        
             
    }
    
    clean_up();
    
    return (EXIT_SUCCESS);
}

