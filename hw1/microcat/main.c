/* 
 * File:   main.c
 * Author: Panda
 *
 * Created on February 9, 2014, 3:40 PM
 */

#include <stdlib.h>
#include <unistd.h>
#include <sys/signal.h>
#include "cat.h"


int sig_flag;

/**
 * Signal handler
 * @param sig_num
 */
void sig_handler(int sig_num) {
    sig_flag = 1;
}


/**
 * Slow slow printing function to stdout
 * CAUTION: Slow. Manual, brutal, inelegant calculation of string length
 * @param content
 */
void std_print(char* content) {    
    int length = 0;
    char ch = 'o';  //place holder
    while((ch = content[++length]) != '\0') ; //Calculate string length    
    write(1, content, length);
}


/**
 * Throws an file exception to system. Prints error message and exit the program
 * @param errcode
 */
void throw_file_exception(int errcode) {
    char* message;     
    
    switch(errcode) {
        case 1:
            message = "Error: file not found\n";      
            break;
        case 2:
            message = "Error: invalid argument\n";      
            break;
        default:
            message = "Unknown Error\n";      
    }
    
    std_print(message);
    _exit(1);
}



int main(int argc, char** argv) {
    
    //Register signal handler
    if(signal(SIGALRM, sig_handler) == SIG_ERR) {        
        std_print("Unable to register handler\n");
        _exit(3);
    }
          
    int red_flag = 0;        //Redirection flag
    char *red_path = NULL;   //Redirection path
    int app_flag = APP_OFF;        //Append flag
        
    int i;
      
    //Scan through arguments for redirection
    for(i = 1; i < argc; i++) {               
        if(red_flag) {       //If user specified redirection                  
            red_path = argv[i];
            break;           //Any argument beyond this point will be dumped
        }      
        
        if(argv[i][0] == '=') {            
            
            if(argv[i][1] == '=') app_flag = APP_ON; //Set append flag
            
            red_flag = i;    //Set flag to be index of ">"
        }
    }
    
 
    if(!red_flag) red_flag = argc;           

    //Loop over files and read AND write file
    //Read until position of a "<" (redflag)
    for(i = 1; i < red_flag; i++) {   
        if(cat(argv[i], red_path, app_flag) != 0) {           
            //If file does not exist
            throw_file_exception(1);   
        }          
    }
    
    //If non argument provided for source file, read from stdin
    if(i == 1 && cat("-", red_path, app_flag) != 0) {
        throw_file_exception(1);
    }
    
    //Send some signal to increase running time for this program
    alarm(1);
    pause();    
       
    //Diana's Ending Theme
    if(sig_flag) std_print("Help! I think I've been shot!!!\n");
    
    //Done!  
    return (EXIT_SUCCESS);
}

