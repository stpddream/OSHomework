#include "command.h"

/* ===== Built in functions ===== */

extern HistoryList* hist_list;

int b_exit() {
    kill(getppid(), SIGTERM);   
}

int b_history() {
    int i;
    for(i = 1; i <= hist_list->size; i++) {
        printf(" %d %s\n", i, histlst_get(hist_list, i));
    }
}

int b_repeat_cmd(int n) {
    char** args = parse_args(histlst_get(hist_list, n));
    char* path = args[0];
    exec_sh(path, args);
}


/* ===== Command execution functions ===== */

int exec_sh(char* path, char** args) {

    if(exec_bcmd(path, args) == 0) return 0;
    
    if(execvp(path, args) == -1) {
        return -1;
    }          
    
}

int exec_bcmd(char* path, char** args) {
        
    if(strcmp(path, "exit") == 0) {
        b_exit();
        return 0;
    }
    else if(strcmp(path, "history") == 0) {
        b_history();
        return 0;
    }
    else if(strcmp(path, "!!") == 0) {
        b_repeat_cmd(1);
    }
    else if(strcmp(path, "!-", strlen("!-")) == 0) {
        char* num;
        strncpy(num, path + 2, strlen(path));
        int n = atoi(num);
        b_repeat_cmd(n);
    }
    
    
    return -1;
}

