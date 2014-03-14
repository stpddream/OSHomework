#include "cmd_history.h"
#include "util.h"

/**
 * Create a new history list
 * @param size capacity of the list
 * @return list created
 */
HistoryList* histlst_create(int size) {
    
    HistoryList* newList = (HistoryList*)malloc(sizeof(HistoryList));
    newList->contents = (char***)malloc(sizeof(char**)*size);
    newList->cursor = 0; 
    newList->capacity = size;
    newList->size = 0;
    newList->offset = 0;
    
    return newList;    
    
}

/**
 * Add args to history list
 * @return 0 if success
 */
int histlst_add(HistoryList* list, char** args) {
    
    if(!histlst_is_empty(list) &&
            cmd_compare(args, 
                list->contents[mod(list->cursor - 1, list->capacity)]
               ) == 0) {        
        return 0;
    }
    
    list->contents[list->cursor] = args;
    list->cursor = mod(list->cursor + 1, list->capacity);     
    if(list->size < list->capacity) list->size++;
    else list->offset++;
      
    return 0;
}

/**
 * Get the nth most recent command in history
 * @param list
 * @param n
 * @return NULL is n is out of bound; command otherwise
 */
char** histlst_get_recent(HistoryList* list, int n) {
      
    if(n <= 0) return NULL;    
    if(n > list->size) return NULL;  
    
    int idx = mod(list->cursor - n, list->capacity);
    return list->contents[idx];

}

/**
 * Get the #n command in history. Ranked in chronological order.
 * @param list
 * @param n
 * @return NULL is n is out of bound; command otherwise
 */
char** histlst_get(HistoryList* list, int n) {    
    return histlst_get_recent(list, list->size - n + list->offset + 1);
}


/**
 * Check if list is empty
 * @return 0 if not. 1 otherwise.
 */
int histlst_is_empty(HistoryList* list) {
    return !(list->size - 0);
}



/**
 * Get the id for the nth command in the history list 
 */
int histlst_get_id(HistoryList* list, int n) {    
    return n + list->offset;
}



