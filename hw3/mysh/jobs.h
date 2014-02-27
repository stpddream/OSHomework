/* 
 * File:   joblist.h
 * Author: Sammy Guergachi <sguergachi at gmail.com>
 *
 * Created on February 26, 2014, 11:46 PM
 */

#ifndef JOBLIST_H
#define	JOBLIST_H

#define JOB_BACK 0
#define JOB_FORE 1
#define JOB_SUSP 2

typedef struct {
	int id;
	int status;  // background, foreground, suspended
	char* path;
        pid_t pid;
} Job;


ListNode *head;
ListNode *tail;

typedef struct {
    Job job;
    ListNode next;
} ListNode;

int jobs_add(Job);
int jobs_remove(int);
int jobs_is_empty();
Job jobs_get(int);



#endif	/* JOBLIST_H */

