/* 
 * File:   main.c
 * Author: Panda
 *
 * Created on February 9, 2014, 3:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cat.h"

/**
 * Throws an file exception to system. Prints error message and exit the program
 * @param errcode
 */
void throw_file_exception(int errcode) {
    char* buff;     
    int n = 22;
    
    switch(errcode) {
        case 1:
            buff = "Error: file not found\n";
            n = 22;
            break;
        case 2:
            buff = "Error: invalid argument\n";
            n = 24;                    
            break;
        default:
            buff = "Unknown Error\n";
            n = 14;
    }
    
    write(1, buff, n);
    _exit(1);
}



int main(int argc, char** argv) {
        
    int red_flag = 0;        //Redirection flag
    char *red_path = NULL;   //Redirection path
    
    //If no arguments, read and output from stdin
    if(argc < 2) {
        cat("-", red_path);
    }
    
    int i;
    
    //Scan through arguments for redirection
    for(i = 1; i < argc; i++) { 
              
        if(red_flag) {       //If user specified redirection
            red_path = argv[i];
            break;           //Any argument beyond this point will be dumped
        }
        
        if(strcmp(argv[i], ">") == 0) {            
            if(i == 1) {
                throw_file_exception(2);
            }            
            red_flag = i;    //Set flag to be index of ">"
        }
    }
    
 
    if(!red_flag) red_flag = argc;           
    

    //Loop over files and read AND write file
    //Read until position of a "<" (redflag)
    for(i = 1; i < red_flag; i++) {   
        if(cat(argv[i], red_path) == -1) {
            //If file does not exist
            throw_file_exception(1);   
        }
    }
    
  
    return (EXIT_SUCCESS);
}

