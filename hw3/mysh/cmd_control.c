#include "cmd_control.h"

/* ===== Built in functions ===== */

extern HistoryList* hist_list;
/*
int b_history() {
    int i;
    for(i = 1; i <= hist_list->size; i++) {     
        int id = histlst_get_id(hist_list, i);
        printf(" %d ", id);
        print_cmd(histlst_get(hist_list, id));
        printf("\n");
    }
    return 0;
}

int b_repeat_cmd(int n) {
    char** args = histlst_get_recent(hist_list, n);
    if(args == NULL) {
        printf("Error: Event not found\n");       
        exit(1);
    }
    char* path = args[0];
    exec_sh(path, args);
    return 0;
}
*/


void b_jobs() {
    jobs_print();
}

void b_kill(char** cur_args, int n_args) {
    Job* job;
    int id, i, is_jid, kill_flag = FALSE;
    
    // if no job ids were specified, print usage and return
    if(n_args == 1){
        print_usage(KILL);
        return;
    }

    // determine if there is a -9 flag in args
    for(i = 1; i < n_args; i++){
        if(cur_args[i][0] == '-'){
            if(!kill_flag && strcmp(cur_args[i], "-9")==0){
                kill_flag = TRUE;
            }else{
                print_usage(KILL);
                return;
            }
        }
    }

    for(i = 1; i < n_args; i++){
        //skip flags
        if(cur_args[i][0] == '-') continue;
        
        // determine if the given id is a job id or process id
        is_jid = (cur_args[i][0] == '%' ? TRUE : FALSE);

        // check if the entry is a valid integer string
        if(int_valueof(cur_args[i]+(is_jid ? 1 : 0), &id)==-1){
            printf("kill: %s : arguments must be process or job IDs\n", cur_args[i]);
        } else {
            printf("id = %d\n",id);
            // retrieve job either by pid or jid
            job = (is_jid ? jobs_get_by_jid(id) : jobs_get_by_pid(id));
            
            // print job not found error if given id is not in the jobs list
            if(job == NULL){
                printf("kill : %s : no such %s \n", cur_args[i], (is_jid? "job" : "process"));
            } else {
                //send a sigterm signal to terminate the job and remove from list
                kill(job->pid, (kill_flag ? SIGKILL : SIGTERM));
                jobs_remove_by_pid(job->pid);
            }
        }
    }
}

/**
 * Built in function for 'fg': bring job to foreground
 * @param job_id if equal to TAIL_ID will bring the most recent job to foreground
 *         otherwise bring #job_id to foreground
 */
void b_fg(char** args, int n_args){
   Job* job;   
   int job_id;
   if(n_args == 1) job_id = TAIL_ID;
   else int_valueof(args[0], &job_id);
   
   if((job = jobs_get_by_jid(job_id)) == NULL) {
            printf("fg: %d : no such job\n", job_id);
   }
   
   job->status = JOB_FORE;
   kill(job->pid, SIGCONT);
}

/**
 * 
 */
void b_bg(char** args, int n_args) {
    Job* job;
    int i = 0;
    int this_id;
    if(n_args == 0) this_id = TAIL_ID;
    else int_valueof(args[0], &this_id);
        
    do {
        
        int_valueof(args[i], &this_id);        
        if((job = jobs_get_by_jid(this_id)) == NULL) {
            printf("fg: %d : no such job\n", this_id);
        }
        job->status = JOB_BACK;
        kill(job->pid, SIGCONT);
        i++;
    } while(i < n_args);
    
}


/* ===== Command execution functions ===== */

int exec_sh(char** args, int n_args, char* origin) {
    pid_t pid;
    sigset_t mask;
    
    Job* new_job = job_create((origin[0] == '&') ? JOB_BACK: JOB_FORE, origin, -1);

    //if an empty argument, free the new_job node and return

    if(exec_bcmd(args, n_args) == NOT_INTERNAL_CMD) {
        sigemptyset(&mask);
        /* check for fork() error */
        if((pid = fork()) < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }
        /*if child, set its group id to pid*/ 
        else if (pid == 0 && setpgid(0, 0) != -1) {
            /****** In Child ******/
            if(execvp(args[0], args) == -1) {
                printf("%s\n", args[0]);
                perror("Exec failed");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        } else {
            /***** In Parent *****/
            new_job->pid = pid;
            jobs_add(new_job);
                
            if(new_job->status == JOB_FORE) { 
               sigsuspend(&mask);
            } else if(new_job->status == JOB_BACK) {
               printf("[%d]\t%d\n", new_job->id, pid);  /* if background, print job info,  handle SITCHLD signal */
            }
        }
    }    
    return 0;
}


/**
 * Execute built in command (considering use data structure (hashmap) to automate?)
 * @param path
 * @param args
 * @return Success 0; Otherwise -1
 */
int exec_bcmd(char** args, int n_args) {
    
    if(strcmp(args[0], "bg") == 0) {
        b_bg(args, n_args);
    }     
    else if(strcmp(args[0], "jobs") == 0) {
        b_jobs();
    }
   
        /*
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
         */
    
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

/* ===== Signal Handler ===== */

void signal_wrapper(int signum, void* handler){
    struct sigaction action;
    action.sa_handler = handler;
    action.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    if(sigaction(signum, &action, 0) == -1){
        perror("Signal Error");
    }
}

//TODO: Add signal handlers
//Functionality see design doc
void sigchld_handler(int sig){
    pid_t pid;
    int status;
    while((pid = waitpid(-1, &status, WNOHANG | WUNTRACED))>0){
        jobs_remove_by_pid(pid);
    }
}

void sigtstp_handler(int sig){
    Job* job;
    if((job = get_fg_job()) != NULL){
        job->status = JOB_SUSP;
        kill(-job->pid, SIGSTOP);
    }
}