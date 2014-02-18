/* 
 * Project: threads
 * File:   main.c
 * Author: Panda
 *
 * Created on February 17, 2014, 4:42 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 
 */
int main(int argc, char** argv) {

    printf("Welcome to ST Terminal!!!\n");
    
    char** args;
 
    
    while(1) {
        char cmd[200];
        scanf("%s", cmd);
        
        char* token;
        token = strtok(cmd, " ");
                
            while(token) {
                printf("Token %s\n", token);
                token = strtok(NULL, " ");
            }
        
    }
    
    
    
    return (EXIT_SUCCESS);
}

