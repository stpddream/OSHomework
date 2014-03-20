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


#define JOB_BACK 0
#define JOB_FORE 1
#define JOB_SUSP 2
#define JOB_DONE 3

#define TAIL_ID -2

typedef struct {
	int id;
	int status;  // background, foreground, suspended
	char* path;
        pid_t pid;
} Job;


Job* job_create(int, char*, pid_t);
Job* job_createc(int);
void job_free(Job*);
typedef struct List_Node {
    Job* job;
    struct List_Node* next;
} ListNode;

/*********** Job List **********/
ListNode *head;
ListNode *tail;
int size;
int id_edge; //Next id to be allocated

int jobs_init();
int jobs_add(Job*);
int jobs_remove_by_jid(int);
int jobs_remove_by_pid(pid_t);
int jobs_is_empty();
Job* jobs_get_by_jid(int);
Job* jobs_get_by_pid(pid_t);

void print_jobs();
void jobs_print();
void job_print(Job*);

Job* get_fg_job();

#endif	/* JOBLIST_H */

