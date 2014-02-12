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
#include <sys/time.h>

#include "intr_info.h"

int intr_total_count;
int intr_second_count;
int first_sec = 0; 
int sec = 1; //Timer interval in second

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


/**
 * Exception handler for invalid timer argument
 */
void timer_fallback() {
    fprintf(stderr, "Invalid timer setting. Interval will be set to default\n");
    sec = 1;
}


int main(int argc, char** argv) {
    
    /* Set Options */
    char* ch_sec = "1";  
    int c;
   
    while((c = getopt(argc, argv, "s:")) != -1) {      
       if(c == 's') {        
           ch_sec = optarg;     
       }
       else if(c == '?') {
           timer_fallback();
           opterr = 0;
       }     
    }
    
    char* end = NULL;
    sec = strtol(ch_sec, &end, 10);
    
    //Check invalid input
    if(end == ch_sec || *end != '\0' || sec <= 0) {
        timer_fallback(); 
    }
    
    printf("Update Interval: %ds\n", sec);
    
    
    /* Set up timer */
    struct itimerval timerval;
    timerval.it_interval.tv_sec = sec;
    timerval.it_interval.tv_usec = 0;

    timerval.it_value.tv_sec = sec;
    timerval.it_value.tv_usec = 0;
    
    if(setitimer(ITIMER_REAL, &timerval, NULL) == -1) {
        fprintf(stderr, "Unable to set timer\n");
        exit(3);
    }
    
     
    /* Set up alarm handler */
    if(signal(SIGALRM, alarm_handler) == SIG_ERR) {        
        fprintf(stderr, "Unable to register handler\n");
        exit(3);
    }
    
   
    printf("==== Start recording interrupts ====\n");
    
    handle_info(); //Call once to get initial value

    /* Update and output info every interval */
    while(1) {
       
        pause();
        handle_info();
        
        //Print values
        printf("[Total]: %d\n", intr_total_count);                        
        printf("[In 1s]: %d\n", intr_second_count);
        printf("........Updating........\n");
               
    }
       
    return (EXIT_SUCCESS);
}

