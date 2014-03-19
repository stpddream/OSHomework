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
#include <signal.h>
#include <readline/readline.h>
#include <sys/types.h>


#include "parser.h"
#include "cmd_control.h"
#include "cmd_history.h"
#include "util.h"
#include "jobs.h"

#define MAX_CMD 20
#define MAX_ARG_LEN 256


char* path;
char** args; //// Deprecated
char** commands;
char* cmd;
char* line;

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

/*
void free_everything(){
    clean_cmdlines();
    clean_args();
    free(input);
    //TODO: clean up jobs list
}*/
/*
void clean_cmdlines(){
    int i;
    for(i =0; i < n_cmd; i++)
        free(cmds[i]);
    free(cmdlines);
}*/






int main(int argc, char** argv) {        
    
    /***** Block Signals *****/
    /*
    sigset_t block_mask;
    sigaddset(&block_mask, SIGINT);
    sigaddset(&block_mask, SIGTSTP);
    sigprocmask(SIG_BLOCK, &block_mask, NULL);
*/
    /***** Set signal handlers *****/
    
    signal_wrapper(SIGCHLD, sigchld_handler);  
    signal(SIGTSTP, sigtstp_handler);
            
    commands = malloc(MAX_CMD*sizeof(char*));
    
    jobs_init();   
    int n_cmd, n_args;
        
    while(1) {
        
        if((line = readline(">>> ")) == NULL) {
            perror("IO Error\n");
            return 1;
        }
                    
        //allocates memory to cmdlines array and parse the input       
        n_cmd = parse_args(line, commands);
             
        //further parse each commands and execute the commands
        int i;      
        for(i = 0; i < n_cmd; i++){    
            args = (char**)malloc(sizeof(char*)*MAX_ARG_LEN);
            cmd = (char*)malloc(sizeof(char*)*strlen(commands[i]));            
            strcpy(cmd, commands[i]); //Preserve the original string                        
            n_args = parse_space(commands[i] + 1, args);                                           
            exec_sh(args, n_args, cmd);
        }


    }
   return 0; 
    
}


