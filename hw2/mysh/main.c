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
#include <errno.h>
#include <sys/signal.h>

#include "parser.h"
#include "command.h"
#include "cmd_history.h"

char* path;
char* args[MAX_ARG_NUM];
HistoryList* hist_list;



void clean_up() {
    int i = 0;
    while(!args[i]) {
        free(args[i]);
    }
    
    free(hist_list);
}

void term_handler(int sig_num) {
    clean_up();
    exit(0);
}





/*
 * 
 */
int main(int argc, char** argv) {

    //Register handler
    if(signal(SIGTERM, term_handler) == SIG_ERR) {
        fprintf(stderr, "Unable to register handler\n");
        b_exit(3);
    }
    
    hist_list = histlst_create(MAX_HIST);

    printf("======== Welcome to ^ ^ ST Terminal! ========= \n");
        
    while(1) {
        printf(">> ");      
        
        char* cmd = NULL;
        size_t size;
  
          
        if(getline(&cmd, &size, stdin) == -1) {
            fprintf(stderr, "IO Error\n");
        }
                              
        //Parse arguments
        parse_args(cmd, args);
        path = args[0];
        
        //Program execution
          
        pid_t pid;
        if((pid = fork()) > 0) {
            //Parent
            wait();            
            histlst_add(hist_list, strip_space(cmd));
        }
        else if(pid == 0) {                       
            //Child          
            
            if(exec_sh(path, args) == -1) {
                fprintf(stderr, "Program Execution Error\n");
            } 
            return (EXIT_SUCCESS);
        }
          
    }
    
    
    
    return (EXIT_SUCCESS);
}

