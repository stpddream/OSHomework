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



#define JOB_BACK 0
#define JOB_FORE 1
#define JOB_SUSP 2

typedef struct {
	int id;
	int status;  // background, foreground, suspended
	char* path;
        pid_t pid;
} Job;


Job* job_create(int, char*, pid_t);
Job* job_createc(int);

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
int jobs_remove(int);
int jobs_is_empty();
Job* jobs_get(int);


void print_jobs();


#endif	/* JOBLIST_H */

