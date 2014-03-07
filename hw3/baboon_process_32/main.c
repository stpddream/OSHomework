/* 
 * File:   main.c
 * Author: Panda
 *
 * Created on March 5, 2014, 2:37 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

#define N 20

int* count;    

//Printing helper
void baboon_info(int n, int dir, char* status) {
    printf("[#%d, %s]\t%s\n", n, (dir) ? "East" : "West", status);    
} 

/**** Baboon behavior ****/
void arrives() {
    int n = rand() % 9;  
    sleep(n);
}

void get_on_the_rope() {
    sleep(1);
}

void cross() {
    sleep(4);
}



/*** ! travel ! ***/
void perform(int pos) {
    
    sem_t* cnt_lock[2];
    cnt_lock[0] = sem_open("cnt_lock0", O_CREAT, S_IRUSR | S_IWUSR, 1);
    cnt_lock[1] = sem_open("cnt_lock1", O_CREAT, S_IRUSR | S_IWUSR, 1);       
    
    sem_t* customs_lock[2];
    customs_lock[0] = sem_open("customs_lock0", O_CREAT, S_IRUSR | S_IWUSR, 1);
    customs_lock[1] = sem_open("customs_lock1", O_CREAT, S_IRUSR | S_IWUSR, 1);
    
    sem_t* rope_lock;
    rope_lock = sem_open("rope_lock", O_CREAT, S_IRUSR | S_IWUSR, 1);

    // Determine direction    
    arrives();
    srand(time(NULL)^(getpid() << 16));
    int dir = rand() % 2;    
    baboon_info(pos, dir, "arrives");    

    // Start queuing and travelling
   
    sem_wait(cnt_lock[dir]); 
    count[dir]++;
    if(count[dir] == 1) {
        sem_wait(customs_lock[dir]);
        sem_wait(rope_lock);       
    }    
    get_on_the_rope();
    baboon_info(pos, dir, "get on the rope");
    sem_post(cnt_lock[dir]);
    
    // Cross the river
    cross();
    baboon_info(pos, dir, "crossing");
    
    //Crossed
    sem_wait(cnt_lock[dir]);
    count[dir]--;
    printf("count + %d", count[dir]);
    if(count[dir] == 0) {
        sem_post(customs_lock[1 - dir]);
        sem_post(rope_lock);
    }
    baboon_info(pos, dir, "crossed");
    sem_post(cnt_lock[dir]);        
}


int main(int argc, char** argv) {
    int i;
    
    printf("\n"); //Start a new line
      
    //In case previous semaphores aren't released
    sem_unlink("cnt_lock0");
    sem_unlink("cnt_lock1");
    sem_unlink("rope_lock");
    sem_unlink("customs_lock0");
    sem_unlink("customs_lock1");
  
    /* Create shared memory that stores baboon count */
    key_t key = 8888;   //lucky number
    int shmid;
    if((shmid = shmget(key, sizeof(int)*2, IPC_CREAT | 0660)) == -1) {
        perror("shmget");
        exit(-1);
    }
    
    if((count = (int*)shmat(shmid, NULL, 0)) == (int*) -1) {
        perror("shmat");
        exit(-1);
    }
    
    count[0] = 0;
    count[1] = 0;
    
    pid_t pid[N];
    
    /* Fork process */
    for(i = 0; i < N; i++) {        
        if((pid[i] = fork()) == 0) {          
            perform(i);         
            _Exit(0);            
        }        
    }
    
    for(i = 0; i < N; i++) waitpid(pid[i], NULL, 0);
    
    sem_unlink("cnt_lock0");
    sem_unlink("cnt_lock1");
    sem_unlink("rope_lock");
           
    shmctl(shmid, IPC_RMID, NULL);        
    return (EXIT_SUCCESS);
}

