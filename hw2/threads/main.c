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
#include <pthread.h>
#include <time.h>

#define N 5
 
int A[N][N];
int B[N][N];
int C[N][N];

int MAX_ROW_SUM;

unsigned int seeds[N][N];
pthread_mutex_t mp;

void* write_mat(void* loc) {
    int* pos = (int*)loc;          
    A[pos[0]][pos[1]] = rand_r(&seeds[pos[0]][pos[1]]) % 5; 
    B[pos[0]][pos[1]] = rand_r(&seeds[pos[1]][pos[0]]) % 5;        
}

void* eval_mult(void* loc) {
    int* pos = (int*)loc;
    
    int i;
    int sum = 0;   
    
    for(i = 0; i < N; i++) {
        sum += A[pos[0]][i] * B[i][pos[1]];        
    }
    C[pos[0]][pos[1]] = sum;
    
}

void* update_row_sum(void* row) {
    int* r = (int*)row;
    int i;
    int sum = 0;
    for(i = 0; i < *r; i++) {
        sum += C[*r][i];
    }
    
    printf("sum: %d\n", sum);

    //update
    pthread_mutex_lock(&mp);
    if(sum > MAX_ROW_SUM) {
        MAX_ROW_SUM = sum;
    }    
    pthread_mutex_unlock(&mp);
    
    int sec = rand_r(&seeds[0][*r]) % 5 + 1;
    sleep(sec);
   
}



/**
 * Print out a matrix
 * @param mat
 * @param cols
 * @param rows
 */
void print_mat(int mat[][N]) {
    
    int i;
    int j;
    
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            printf("%d ", mat[i][j]);            
        }
        printf("\n");
    }
    
}




int main(int argc, char** argv) {
    int i;
    int j;
    
    pthread_mutex_init(&mp, NULL);
    printf("Start\n");
    
    pthread_t tid[N][N];
    
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {                               
            int* pos = (int*)malloc(sizeof(int)*2); //Memory leak?
            pos[0] = i;
            pos[1] = j;
            seeds[i][j] = (int)tid + (i + 10) * (j + 22); //Each thread has its own seed
//            int pos[2] = {i, j};   //A question to be asked why this won't work          
            pthread_create(&tid[i][j], NULL, write_mat, pos);
            
        }
    }
    
    
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            pthread_join(tid[i][j], NULL);
        }
    }
    
    printf("==== Matrix A ====\n");
    print_mat(A);
    printf("\n");
    printf("==== Matrix B ====\n");
    print_mat(B);
    
    //Print out matrix C 
    //Optimize: use DP
    
    pthread_t tids[N][N];
    
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            int* pos = (int*)malloc(sizeof(int)*2);
            pos[0] = i;
            pos[1] = j;       
            pthread_create(&tids[i][j], NULL, eval_mult, pos);
        }
    }
    
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            pthread_join(tids[i][j], NULL);
        }
    }

    printf("==== Matrix C ====\n");
    print_mat(C);

    
    /* Calculate the max row sum */
    MAX_ROW_SUM = 0;
    
    pthread_t stid[N];
    
    for(i = 0; i < N; i++) {
        int* row = (int*)malloc(sizeof(int));
        *row = i;
        pthread_create(&stid[i], NULL, update_row_sum, row);
    }
    
    for(i = 0; i < N; i++) {
        pthread_join(stid[i], NULL);
    }
    
    printf("%d\n", MAX_ROW_SUM);
    pthread_mutex_destroy(&mp);
    return (EXIT_SUCCESS);
}

