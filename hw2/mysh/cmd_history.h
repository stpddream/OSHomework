/* 
 * Project: mysh
 * File:   cmd_history.h
 * Author: Panda
 *
 * Created on February 17, 2014, 10:05 PM
 */

#ifndef CMD_HISTORY_H
#define	CMD_HISTORY_H

#include <stdio.h>
#include <stdlib.h>


#define MAX_HIST 3

typedef struct {
    
    char*** contents;
    int cursor;    
    int head;
    int capacity;
    int size;
    int offset;
    
} HistoryList;

HistoryList* histlst_create(int);
int histlst_add(HistoryList*, char**);
char** histlst_get_recent(HistoryList*, int);
int histlst_is_empty(HistoryList*);
int histlst_get_id(HistoryList*, int);

#endif	/* CMD_HISTORY_H */

