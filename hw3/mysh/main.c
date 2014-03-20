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
#include <termios.h>

#define MAX_CMD 20
#define MAX_ARG_LEN 256


char** args; 
char* cmd;
char** commands;

char* line;

int mysh_terminal;
pid_t mysh_pgid;
struct termios mysh_tmodes;
sigset_t chld_mask; //Sig set that contains only SIG_CHLD


void init_mysh(){
    

     /***** Block Signals *****/
    sigset_t block_mask;

    sigaddset(&block_mask, SIGINT);
    sigaddset(&block_mask, SIGTSTP);
    sigaddset(&block_mask, SIGTERM);
    sigaddset(&block_mask, SIGQUIT);
    sigaddset(&block_mask, SIGTTOU);
    sigaddset(&block_mask, SIGTTIN);
    sigaddset(&block_mask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &block_mask, NULL);

    /***** Set signal handlers *****/

    struct sigaction action;
    action.sa_handler = sigchld_handler;
    action.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    if(sigaction(SIGCHLD, &action, 0) == -1){
        perror("Signal Error");
    }
    sigaddset(&block_mask, SIGINT);
    sigaddset(&block_mask, SIGTSTP);
    sigaddset(&block_mask, SIGTERM);
    sigaddset(&block_mask, SIGQUIT);
    sigaddset(&block_mask, SIGTTOU);
    sigaddset(&block_mask, SIGTTIN);
    sigaddset(&block_mask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &block_mask, NULL);
   
    mysh_terminal = STDIN_FILENO;
    mysh_pgid = getpid();
    if(setpgid(mysh_pgid, mysh_pgid) < 0)
        perror("Cound't put the shell in its own process group\n");
    tcsetpgrp(mysh_terminal, mysh_pgid);
    tcgetattr(mysh_terminal, &mysh_tmodes);
    
    sigaddset(&chld_mask, SIGCHLD);

    

    
    
}

        

/**
 * Clean up before exit, prevent memory leak
 */
void clean_up() {
    
   
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
            

    init_mysh();
    jobs_init();   
    int n_cmd, n_args;
    commands = malloc(MAX_CMD*sizeof(char*));
    while(1) {       
        if((line = readline("")) == NULL) {
            perror("IO Error\n");
            return 1;
        }
        tcgetattr(mysh_terminal, &mysh_tmodes);

                    
        //allocates memory to cmdlines array and parse the input       
        n_cmd = parse_args(line, commands);
             
        //further parse each commands and execute the commands
        
        int i;      
        for(i = 0; i < n_cmd; i++) {    
            args = (char**)malloc(sizeof(char*)*MAX_ARG_LEN);
            cmd = (char*)malloc(sizeof(char)*strlen(commands[i]));            
            strcpy(cmd, commands[i]); //Preserve the original string                        
            n_args = parse_space(commands[i] + 1, args);                 
            exec_sh(args, n_args, cmd);            
        }
    }
   return 0; 
    
}


