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
#include "cmd_control.h"
#include "cmd_history.h"
#include "util.h"

char* path;
char** args;

HistoryList* hist_list;

/**
 * Clean up before exit, prevent memory leak
 */
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

