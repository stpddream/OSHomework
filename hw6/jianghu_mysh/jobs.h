/* 
 * File:   joblist.h
 * Author: Panda & Jacy 
 *
 * Created on February 26, 2014, 11:46 PM
 */

#ifndef JOBLIST_H
#define	JOBLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>


#define JOB_BACK 4
#define JOB_FORE 5

#define JOB_COMP 0
#define JOB_STOP 1 
#define JOB_RUN 2

#define PROC_COMP 0
#define PROC_STOP 1
#define PROC_RUN 2

#define TAIL_ID -2

/**
 First time experiment great c exposed unencapsulated linked list!
 */
typedef struct Process_Node {
    char** args;
    int n_args;
    pid_t pid;
    int status;
    struct Process_Node* next;
} Process;


typedef struct {
	int id;
        int status;	
        int process_status;
        int file;
	char* path;
        pid_t pgid;
        Process* f_process;  //Process List for job
        pid_t pid;
} Job;


Job* job_create(char*, Process*, int, int);
Job* job_createc(int);
void job_free(Job*);
void job_setpgid(Job*, pid_t);

typedef struct Job_Node {
    Job* job;
    struct Job_Node* next;
} JobNode;

/*********** Job List **********/
JobNode *head;
JobNode *tail;
int size;
int id_edge; //Next id to be allocated

int jobs_init();
int jobs_add(Job*);
int jobs_remove_by_jid(int);
int jobs_remove_by_pid(pid_t);
int jobs_is_empty();
Job* jobs_get_by_jid(int);
Job* jobs_get_by_pid(pid_t);

int jobs_check_status(Job*);
int process_update_status(pid_t, int);

void print_jobs();
void jobs_print();
void job_print(Job*);

Job* get_fg_job();

#endif	/* JOBLIST_H */

