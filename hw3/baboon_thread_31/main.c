/* 
 * File:   main.c
 * Author: Panda
 *
 * Created on March 5, 2014, 2:37 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10

pthread_t tid[N];
pthread_mutex_t customs[2];
pthread_mutex_t cnt_lock[2];
pthread_mutex_t rope_lock;
pthread_mutex_t big_lock;
int count[2];

void baboon_info(int n, int dir, char* status) {
    printf("[#%d, %s]\t%s\n", n, (dir) ? "East" : "West", status);    
} 

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


void* train(void* arg) {
    
    int* pos = (int*)arg;
    
    arrives();

    int dir = rand() % 2;
    baboon_info(pos[0], dir, "arrives");
    
    //printf("Baboon %d arrives. %s\n", pos[0], (dir) ? "East" : "West");    
   
    pthread_mutex_lock(&cnt_lock[dir]); 

    count[dir]++;
    if(count[dir] == 1) {
        pthread_mutex_lock(&rope_lock);
    }
    
    get_on_the_rope();
    baboon_info(pos[0], dir, "get on the rope");
    pthread_mutex_unlock(&cnt_lock[dir]);
    
    //Cross the river
    cross();
    baboon_info(pos[0], dir, "crossing");
    
    pthread_mutex_lock(&cnt_lock[dir]);
    count[dir]--;
    if(count[dir] == 0) pthread_mutex_unlock(&rope_lock);
    baboon_info(pos[0], dir, "crossed");
    pthread_mutex_unlock(&cnt_lock[dir]);
    
    
}



/*
 * 
 */
int main(int argc, char** argv) {
    int i;
    
    count[0] = 0;
    count[1] = 0;
    
    pthread_mutex_init(&customs[0], NULL);
    pthread_mutex_init(&customs[1], NULL);
    int pos[N];
    for(i = 0; i < N; i++) {
        pos[i] = i;
        pthread_create(&tid[i], NULL, train, &pos[i]);        
    }
    
    for(i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }
    
    
    return (EXIT_SUCCESS);
}

