/* 
 * File:   main.c
 * Author: Panda 
 *
 * Created on February 8, 2014, 1:46 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "intr_info.h"

int intr_total_count;
int intr_second_count;
int first_sec = 0;

/**
 * Empty alarm handler that does nothing
 */
void alarm_handler() { }


/**
 * Record interrupts count from system proc/
 */
void handle_info() {
    int intr_old_count = intr_total_count;
    intr_total_count = get_intr_info();    
    intr_second_count = intr_total_count - intr_old_count;
}


int main(int argc, char** argv) {
    
    if(signal(SIGALRM, alarm_handler) == SIG_ERR) {
        fprintf(stderr, "Unable to register handler");        
        exit(3);
    }
    
    printf("==== Start recording interrupts ====\n");
    
    handle_info(); //Call once to get initial value

    //Update and output info each 1s.    
    while(1) {
        alarm(1);
        pause();
        handle_info();
        
        //Print values
        printf("[Total]: %d\n", intr_total_count);                        
        printf("[In 1s]: %d\n", intr_second_count);
        printf("........Updating........\n");      
               
    }
       
    return (EXIT_SUCCESS);
}

