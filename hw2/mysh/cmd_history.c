#include "cmd_history.h"
#include "util.h"

HistoryList* histlst_create(int size) {
    
    HistoryList* newList = (HistoryList*)malloc(sizeof(HistoryList));
    newList->contents = (char**)malloc(sizeof(char*)*size);
    newList->cursor = 0; 
    newList->capacity = size;
    newList->size = 0;
    
    return newList;    
    
}


int histlst_add(HistoryList* list, char* cmd) {
    
    
    if(!histlst_is_empty(list) &&
            strcmp(cmd, list->contents[mod(list->cursor - 1, list->capacity)]) == 0) {
        return 0;
    }
    
    list->contents[list->cursor] = cmd;
    list->cursor = mod(list->cursor + 1, list->capacity);     
    if(list->size < list->capacity) list->size++;
    
}

char* histlst_get(HistoryList* list, int n) {
    
    if(n <= 0) return NULL;
    if(n > list->size) return NULL;  
    
    int idx = mod(list->cursor - n, list->capacity);
    return list->contents[idx];

}

int histlst_is_empty(HistoryList* list) {
    return !(list->size - 0);
}


