/* 
 * File:   main.c
 *
 *
 * Created on March 6, 2014, 8:08 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>

/*
 * 
 */
int main(int argc, char** argv) {

    
    sem_unlink("key");
      pid_t pid;
      printf("hello, world\n");
    if((pid = fork()) > 0) {
        
        sem_t* mutex;
//        if((mutex = sem_open("smp", O_CREAT, S_IRUSR|S_IWUSR, 1) == SEM_FAILED)) {
//          printf("failed\n");
//    }
        mutex = sem_open("key", O_CREAT, S_IRUSR|S_IWUSR, 2);
      //  sem_post(mutex);
        sem_wait(mutex);
        printf("passed.\n");

         
    }
    else if(pid == 0) {  
        /*
        sem_t* mutex;
        if((mutex = sem_open("semaphore", O_CREAT, 0644, 1) == SEM_FAILED)) {
            printf("failed\n");
        }
        sem_post(mutex);
        printf("posted!!");
         */
        sem_t* mutex;
        mutex = sem_open("key", O_CREAT, S_IRUSR|S_IWUSR, 2);                       
        //sem_post(mutex);
        printf("done!\n");
    }
    
    
    return (EXIT_SUCCESS);
}

