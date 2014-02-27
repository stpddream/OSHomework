#include "cmd_control.h"

/* ===== Built in functions ===== */

extern HistoryList* hist_list;

int b_history() {
    int i;
    for(i = 1; i <= hist_list->size; i++) {     
        int id = histlst_get_id(hist_list, i);
        printf(" %d ", id);
        print_cmd(histlst_get(hist_list, id));
        printf("\n");
    }
}

int b_repeat_cmd(int n) {
    char** args = histlst_get_recent(hist_list, n);
    if(args == NULL) {
        printf("Error: Event not found\n");       
        exit(1);
    }
    char* path = args[0];
    exec_sh(path, args);
}


/* ===== Command execution functions ===== */

int exec_sh(char* path, char** args) {
  
    //Higher priority commands
    if(strcmp(path, "exit") == 0) exit_clean();
    
    //! shortcut not saved in history
    if(path[0] != '!') histlst_add(hist_list, args);   
    
    
    //Program execution    
    pid_t pid;
    if((pid = fork()) > 0) {
        //Parent
        wait();  
        
        //TODO:
        /*        
         Add background support
         if(background) continue to accept commands
         else if(foreground) wait
                  
         Update Job List
         mutex_lock()
         sigpromask(SIGCHLD)
         job_add(job)
         mutex_unlock()
         
         */
        
        
        
        
    }
    else if(pid == 0) {                       
        //Child                  
        if(exec_bcmd(path, args) != -2) exit(0);    //-2 means "not found"
        if(execvp(path, args) == -1) {
            fprintf(stderr, "Unable to execute file\n");
        }     
        exit(0);
    }
    
}

/**
 * Execute built in command (considering use data structure (hashmap) to automate?)
 * @param path
 * @param args
 * @return Success 0; Otherwise -1
 */
int exec_bcmd(char* path, char** args) {
        
    if(strcmp(path, "history") == 0) {
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
            printf("offset %d", hist_list->offset);
            b_repeat_cmd(hist_list->size - n + hist_list->offset + 1);
            free(num);
            return 0;            
        }
        
    }
    
    //TODO:
    /*
     
     Add support for bg, fg, jobs, kill command
     if(bg) send SIG_CONT to job
     if(fg) ifsuspend, SIG_CONT and wait for job
     if(jobs) //iterate through joblist and print jobs
     if(kill) //remove job from list
         mutex_lock()
         sigprocmask(SIGCHLD);
         job_remove()
         mutex_unlock()
     
     */
    
    
    
    
    return -2;
}

//TODO: Add signal handlers
//Functionality see design doc
void* signal_handler(void*);