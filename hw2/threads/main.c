/* 
 * Project: threads
 * File:   main.c
 * Author: Panda
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

/**
 * Randomly write a value of matrix A and B
 * @param loc x: loc[0], y:loc[1]
 * @return 
 */
void* write_mat(void* loc) {
    int* pos = (int*)loc;          
      
    A[pos[0]][pos[1]] = rand_r(&seeds[pos[0]][pos[1]]) % 899 + 100; 
    B[pos[0]][pos[1]] = rand_r(&seeds[pos[0]][pos[1]]) % 899 + 100;        
}


/**
 * Thread func that claculate one cell (x, y) of mult of two matrix
 * @param loc: x: loc[0], y: loc[1]
 * @return 
 */
void* eval_mult(void* loc) {
    int* pos = (int*)loc;    
    int i;
    int sum = 0;   
    
    for(i = 0; i < N; i++) {
        sum += A[pos[0]][i] * B[i][pos[1]];        
    }
    C[pos[0]][pos[1]] = sum;
}


/**
 * Update row sum thread
 * @param row
 * @return 
 */
void* update_row_sum(void* row) {
    int* r = (int*)row;
    int i;
    int sum = 0;
    for(i = 0; i < *r; i++) {
        sum += C[*r][i];
    }
       
    //Sleep for some random seconds
    int sec = rand_r(&seeds[0][*r]) % 5 + 1;
    sleep(sec);
    
    //Mutual exclusion
    pthread_mutex_lock(&mp);
    if(sum > MAX_ROW_SUM) {
        MAX_ROW_SUM = sum;
    }    
    pthread_mutex_unlock(&mp);
}



/**
 * Print out a N*N matrix
 * @param mat 
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

    /* Fill in matrix A and B with random numbers */
    pthread_t tid[N][N];
    int pos[N][N][2]; 
        
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {                               
            pos[i][j][0] = i;
            pos[i][j][1] = j;
            
            //Generate seed for each thread             
            struct timeval tv;            
            gettimeofday(&tv,NULL);
            seeds[i][j] = (unsigned int)tid + i * 10 + j * 13 + tv.tv_usec; 
            
            pthread_create(&tid[i][j], NULL, write_mat, pos[i][j]);            
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
    printf("\n");

    
    /* Calculate C = A x B */    
    //TODO: Optimize: use DP 
    //Too lazy to optimize, not sure how DP works in multithread
    pthread_t tids[N][N];
    
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {            
            pos[i][j][0] = i;
            pos[i][j][1] = j;       
            pthread_create(&tids[i][j], NULL, eval_mult, pos[i][j]);
        }
    }
    
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            pthread_join(tids[i][j], NULL);
        }
    }

    printf("==== Matrix C ====\n");
    print_mat(C);
    printf("\n");

    
    /* Calculate the max row sum */
    MAX_ROW_SUM = 0;    
    pthread_t stid[N];
        
    int row[N];
    for(i = 0; i < N; i++) {
        row[i] = i;
        pthread_create(&stid[i], NULL, update_row_sum, &row[i]);
    }
    
    for(i = 0; i < N; i++) {
        pthread_join(stid[i], NULL);
    }
    
    printf("Max Sum: %d\n", MAX_ROW_SUM);
    pthread_mutex_destroy(&mp);
    
    return (EXIT_SUCCESS);
}

