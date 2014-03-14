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

#include "parser.h"
#include "cmd_control.h"
#include "cmd_history.h"
#include "util.h"
#include "jobs.h"

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
    
    printf("Nothing in the list %d\n", jobs_remove(20));
    
    jobs_add(job_createc(10));
    print_jobs();
    jobs_add(job_createc(20));
    print_jobs();
    jobs_add(job_createc(50));
    print_jobs();
    jobs_add(job_createc(100));
    print_jobs();
    
    jobs_remove(20);
    print_jobs();
   

    printf("Remove a null job: %d", jobs_remove(23));
    
    
    
    
    
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

