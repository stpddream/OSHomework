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
#include <termios.h>

#include "parser.h"
#include "cmd_control.h"
#include "cmd_history.h"
#include "util.h"
#include "jobs.h"
#include "inode_list.h"
#include "commands.h"

#include "libs/device_ctrl.h"
#include "libs/kernel_mem.h"
#include "libs/bitmap.h"
#include "libs/util.h"
#include "libs/filesys_util.h"
#include "libs/file_table.h"
#include "libs/file.h"
#include "libs/ft_dir.h"



#define MAX_CMD 20
#define MAX_ARG_LEN 256

/***HEADERS***/
void init_mysh();
void clean_up();


/*** GLOBAL VARIABLES ***/
extern Dev* cur_dev;

char cur_dir[MAX_PATH_LEN];
//User* users[3]

char** args;
char* job_line;
char** commands;
char** proc_cmds;


char gl_cmds[MAX_PATH_LEN];
char gl_file[MAX_PATH_LEN];

char* line;

int mysh_terminal;
pid_t mysh_pgid;
struct termios mysh_tmodes;
sigset_t chld_mask; //Sig set that contains only SIG_CHLD


void init_mysh();
void clean_up();

int cur_usr;

extern Dev* cur_dev;

int main(int argc, char** argv) {
    ///////////////// INITIALIZE EVERYTHING /////////////////////
    FILE* fp;
    fp = fopen("testfile/disk", "w+");
    cur_dev = dev_create(fp);

    dev_init(cur_dev, 10240000);  
    fs_init(cur_dev, 10240000);  

    //Init tables
    ft_init();
    it_init();

    //user_init();
    init_mysh();

    //append root to current path
    inode_append(2);
    //clear the path 
    cur_dir[0] = '\0';
    gen_path(cur_dir);

    //////////////////////// INIT END ////////////////////////////

    printf("---- Welcome to Jianghu Shell Please login ---- \n");
    
    user_init();
    while ((cur_usr = user_login()) == -1);

    printf("Welcome user %d\n", cur_usr);

    jobs_init();
    set_cur_idx(2); //Current directory to root.
    int n_cmd;
   
    ////////////// Manual file write
   
    
    int mfd = f_open("file", "w+");
    
    char* data = "hahahaha";
    int rt2 = f_write(data, strlen(data), 1, mfd);

    f_close(mfd);
    
/*
    
    char another[20];
    f_seek(mfd, 0, SEEK_SET);
    int rt = f_read(another, strlen(data), 1, mfd);
    printf("another is: %s\n", another);
    printf("returns %d\n", rt);

    */
    
    /////////////////////////////////
    
    
    
    
    
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

        int i, res, fd, n_args;

        for (i = 0; i < n_cmd; i++) {

            args = (char**) malloc(sizeof (char*)*MAX_ARG_LEN);

            // parse redirection
            n_args = parse_redirection(commands[i], args, gl_file, &res);
            Process* process = (Process*) malloc(sizeof (Process));

            process->args = args;
            process->n_args = n_args;
            process->next = NULL;

            if (res == READ_MODE) {
                fd = f_open(gl_file, "r");
            } else if (res == WRITE_OVRWT) {
                fd = f_open(gl_file, "w+");
            } else if (res == WRITE_APND) {
                fd = f_open(gl_file, "a+");
            }

            Job* job = job_create(gl_cmds, process,
                    ((gl_cmds[0] == '&') ? JOB_BACK : JOB_FORE),
                    fd, res);
            exec_job(job);
        }
    }

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