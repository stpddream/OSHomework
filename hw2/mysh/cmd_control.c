#include "cmd_control.h"

/* ===== Built in functions ===== */

extern HistoryList* hist_list;

int b_exit() {
    kill(getppid(), SIGTERM);   
}

int b_history() {
    int i;
    for(i = 1; i <= hist_list->size; i++) {
        printf(" %d ", i);    
        print_cmd(histlst_get(hist_list, i));
        printf("\n");
    }
}

int b_repeat_cmd(int n) {
    char** args = histlst_get_recent(hist_list, n);
    char* path = args[0];
    exec_sh(path, args);
}


/* ===== Command execution functions ===== */

int exec_sh(char* path, char** args) {
  
    //Program execution    
    pid_t pid;
    if((pid = fork()) > 0) {
        //Parent
        wait();           
        histlst_add(hist_list, args);
    }
    else if(pid == 0) {                       
        //Child                  
        if(exec_bcmd(path, args) == 0) return 0;    
        if(execvp(path, args) == -1) {
            fprintf(stderr, "Unable to execute file\n");
        }     
        exit(EXIT_SUCCESS);
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
    else if(path[0] == '!') {
        //History shortcuts
                  
        if(strcmp(path, "!!") == 0) {
            b_repeat_cmd(1);
            return 0;
        }
        else if(strncmp(path, "!-", strlen("!-")) == 0) {
            //Match "!-n", nth most recent command
            
            char* num = substring(path, 2, 3);  
            int n;
            if(int_valueof(num, &n) != 0) return -1;
            b_repeat_cmd(n);
            free(num); //Free memory
            return 0;
        }
        else {
            //Match "!n", nth command
            
            char* num = substring(path, 1, 2);
            int n;
            if(int_valueof(num, &n) != 0) return -1;
            b_repeat_cmd(hist_list->size - n + 1);
            free(num);
            return 0;            
        }
        
    }
    
    
  
        
    return -1;
}

