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
#include "libs/device_ctrl.h"
#include "libs/kernel_mem.h"
#include <termios.h>
#include "usr.h"

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

void init_mysh();
void clean_up();

User* users[3];
int cur_usr;

int main(int argc, char** argv) {

    init_mysh();

    printf("---- Welcome to Jianghu Shell Please login ---- \n");

    user_init();
    while ((cur_usr = user_login()) == -1);

    printf("Welcome user %d\n", cur_usr);

    jobs_init();
    int n_cmd;
    commands = malloc(MAX_CMD * sizeof (char*));
    while (1) {
        printf("TERMINAL >>  ");
        if ((line = readline("")) == NULL) {
            perror("IO Error\n");
            return 1;
        }
        tcgetattr(mysh_terminal, &mysh_tmodes);

        //allocates memory to cmdlines array and parse the input       
        n_cmd = parse_args(line, commands);

        //further parse each commands and execute the commands

        int i, j;
        int writeMode, writeStart;
        int readMode, readFrom;
        for (i = 0; i < n_cmd; i++) {
            job_line = (char*) malloc(sizeof (char)*strlen(commands[i]));
            proc_cmds = (char**) malloc(sizeof (char*)*MAX_CMD);
            printf("%s\n", commands[i]);
            
            while(commands[i][j] != '\0'){ //while not at the end of the command
                if(commands[i][j] == '>'){
                    //check ahead to see if it is >>
                    if(commands[i][j+1] == '>'){
                        writeMode = WRITE_APND;
                        writeStart = j+2;
                        commands[i][j] = '\0';
                        commands[i][j+1] = '\0';
                        j++;
                    }else{
                        writeMode = WRITE_OVRWT;
                        writeStart = j+1;
                    }
                }else if(commands[i][j] == '<'){
                    readMode = READ_MODE;
                    readFrom = j+1;
                    commands[i][j] = '\0';
                }
                j++;
            }

        }
    }

    user_clean();

    return 0;
}

void init_mysh() {


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
    if (sigaction(SIGCHLD, &action, 0) == -1) {
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
    if (setpgid(mysh_pgid, mysh_pgid) < 0)
        perror("Cound't put the shell in its own process group\n");
    tcsetpgrp(mysh_terminal, mysh_pgid);
    tcgetattr(mysh_terminal, &mysh_tmodes);

    sigaddset(&chld_mask, SIGCHLD);
}

void clean_up() {
   
}