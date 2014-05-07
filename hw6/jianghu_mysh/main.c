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
#include "commands.h"
#include <termios.h>

#define MAX_CMD 20
#define MAX_ARG_LEN 256


char** args; 
char* job_line;
char** commands;
char** proc_cmds;

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

int user;



int main(int argc, char** argv) {        

    /*
    more("super\nioiwoeifjoweifjwoeifjowijfowijefoewjfoiewjofjewofjweoifjewofjewiofjoewifjiewojf\nsuper\nsuper\n"
            "super\nseupr\n\n\n\n\njwerwe\nwefwefwe\nwe\n\n\newefqfqwfqg\nwqerqerqe\n\nadfqef\nwef\nwef\nwef\n"
            "wef\nwef\n\0");
   
    exit(0);
    */
    
    
    
    init_mysh();
    
    printf("---- Welcome to Jianghu Shell Please login ---- \n");
    char uname[20];
    char passwd[20];
    
    while(1) {
        printf("Username: ");
        scanf("%s", &uname);
        printf("Password: ");
        scanf("%s", &passwd);
    
        if(strcmp(uname, "panda") == 0 && strcmp(passwd, "123456") == 0) {
            user = 1;
            break;
        }
                        
        if(strcmp(uname, "jacy") == 0 && strcmp(passwd, "111111") == 0) {
            user = 2;
            break;
        }
        printf("Invalid password or user name\n");
    }
    
    
    printf("Welcome user %d\n", user);
    
    jobs_init();   
    int n_cmd, n_args;
    commands = malloc(MAX_CMD*sizeof(char*));
    while(1) {
        printf("TERMINAL >>  ");
        if((line = readline("")) == NULL) {
            perror("IO Error\n");
            return 1;
        }
        tcgetattr(mysh_terminal, &mysh_tmodes);

        //allocates memory to cmdlines array and parse the input       
        n_cmd = parse_args(line, commands);
             
        //further parse each commands and execute the commands
        
        int i, j;
        for(i = 0; i < n_cmd; i++) {    
            job_line = (char*)malloc(sizeof(char)*strlen(commands[i]));        
            proc_cmds = (char**)malloc(sizeof(char*)*MAX_CMD);
            strcpy(job_line, commands[i]); //Preserve the original string         
            
            int n_proc = parse_process(commands[i] + 1, proc_cmds);
            
            //Create processes for each job
            Process* dummy = (Process*)malloc(sizeof(Process)); //Dummy Head
            Process* prev = dummy;
            int n_args;
            
            for(j = 0; j < n_proc; j++) {       
                
                args = (char**)malloc(sizeof(char*)*MAX_ARG_LEN);
                Process* process = (Process*)malloc(sizeof(Process));
                                
                n_args = parse_space(proc_cmds[j], args);
                

                process->args = args;                
                process->n_args = n_args;
                process->next = NULL;
                
                prev->next = process;
                prev = process;                                                                        
            }            
            Job* job = job_create(job_line, dummy->next, 
                                  ((job_line[0] == '&') ? JOB_BACK: JOB_FORE),
                                  -1); 
            free(dummy);
            exec_job(job);                       
        }
    }
   return 0;    
}


