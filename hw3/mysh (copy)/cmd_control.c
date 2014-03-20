#include "cmd_control.h"

/* ===== Built in functions ===== */

void b_exit() {
    exit_clean();
}

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
            // retrieve job either by pid or jid
            
            if(is_jid) {                
                job = jobs_get_by_jid(id);
                if(job == NULL){
                    printf("kill : %s : no such %s \n", cur_args[i], (is_jid? "job" : "process"));
                } else {
                    //send a sigterm signal to terminate the job and remove from list                
                    Process* process = job->f_process;
                    while(process != NULL) {
                        kill(process->pid, (kill_flag ? SIGKILL : SIGTERM));      
                        process = process->next;
                    }
                }                                                
                
            }
            else {
                printf("kill by id %d\n", id);
                if(kill(id, (kill_flag ? SIGKILL : SIGTERM)) == -1) { 
                    fprintf(stderr, "Kill failed. No such process\n");
                }
            }
            
            // print job not found error if given id is not in the jobs list
            
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
   else int_valueof(args[1], &job_id);
   
   if((job = jobs_get_by_jid(job_id)) == NULL) {
       printf("fg: %d : no such job\n", job_id);
       return ;
   }
   
   job->status = JOB_FORE;
   
   Process* process = job->f_process;
   while(process != NULL) {
       kill(process->pid, SIGCONT);
       process->status = PROC_RUN;       
       process = process->next;
   }
   
   put_in_foreground(job);

}


/**
 * 
 */
void b_bg(char** args, int n_args) {
    Job* job;
    int i = 0;
    int this_id;
    if(n_args == 1) this_id = TAIL_ID;
    else int_valueof(args[1], &this_id);
        
    do {        
        int_valueof(args[i], &this_id);        
        if((job = jobs_get_by_jid(this_id)) == NULL) {
            printf("fg: %d : no such job\n", this_id);
        }
        job->status = JOB_BACK;
        
         
       Process* process = job->f_process;
           while(process != NULL) {
           kill(process->pid, SIGCONT);
           process->status = PROC_RUN;       
           process = process->next;
       }
       
        job_print(job);        
        i++;
    } while(i < n_args);
    
}


/* ===== Command execution functions ===== */

int exec_job(Job* new_job) {
    
    int built_in = 0;
    
    pid_t pid;
        
    int pipe_file[2];
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    int errfile = STDERR_FILENO;    
    Process *cur_proc = new_job->f_process;
    
    while(cur_proc != NULL) {
        
        //If there are more than one processes in the list and not
        // the last elemen: need piping
        
        if(cur_proc->next != NULL) {
            
            if(pipe(pipe_file) < 0) {
                perror("pipe");
                exit(1);
            }        
            outfile = pipe_file[1];
            
        }
        else outfile = STDOUT_FILENO;
        
        /** Start forking process **/
      
        //if an empty argument, free the new_job node and return
        if((built_in = exec_bcmd(cur_proc->args, cur_proc->n_args)) == NOT_INTERNAL_CMD) {    
        /* check for fork() error */
            if((pid = fork()) < 0) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }
            /*if child, set its group id to pid*/ 
            else if (pid == 0) {
                /****** In Child ******/
                pid_t cid = getpid();
                if(new_job->pgid == -1) new_job->pgid = cid;
                setpgid(pid, new_job->pgid);
                                               
                if(infile != STDIN_FILENO) {
                    dup2(infile, STDIN_FILENO);                                  
                    close(infile);
                }
    
                if(outfile != STDOUT_FILENO) {
                    dup2(outfile, STDOUT_FILENO);
                    close(outfile);
                }
    
                
                if(errfile != STDERR_FILENO) {
                    dup2(errfile, STDERR_FILENO);
                    close(errfile);
                }
                                
                if(execvp(cur_proc->args[0], cur_proc->args) == -1) {      
                    perror("Exec failed");
                    exit(EXIT_FAILURE);
                }
                
                exit(EXIT_SUCCESS);
            } else {
                /***** In Parent *****/
                cur_proc->pid = pid;           
                cur_proc->status = PROC_RUN; //sync problem?
                if(new_job->pgid == -1) {
                    new_job->pgid = pid;                    
                }
                setpgid(pid, new_job->pgid);
            }
        }    
        
        
         /** Clean up pipes **/
        
        if(infile != STDIN_FILENO) {
            close(infile);
        }
    
        if(outfile != STDOUT_FILENO) {
            close(outfile);
        }
        infile = pipe_file[0];                    
        cur_proc = cur_proc->next;        
    }
    
    
    if(built_in == NOT_INTERNAL_CMD) {                   
        jobs_lock();
        jobs_add(new_job);
        jobs_unlock();    
        
        printf("Job %d added\n",new_job->pgid);
        printf("jobs size %d\n", size);
    }
    
    jobs_print();
  
               
    if(new_job->status == JOB_FORE) {                
        if(built_in == NOT_INTERNAL_CMD) put_in_foreground(new_job); 
    } else if(new_job->status == JOB_BACK) {
        printf("[%d]\t%d\n", new_job->id, new_job->pgid);  /* if background, print job info,  handle SITCHLD signal */
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
    } else if(strcmp(args[0], "fg") == 0) {
        b_fg(args, n_args);
    } else if(strcmp(args[0], "jobs") == 0) {
        printf("Exe jobs\n");
        b_jobs();
    } else if(strcmp(args[0], "kill") == 0) {
        printf("num arguments %d\n", n_args);
        b_kill(args, n_args);
    } else if(strcmp(args[0], "exit") == 0) {
        exit_clean();
    }
    else return NOT_INTERNAL_CMD;
    return 0;

}


/*** Helper Functions ***/

void put_in_foreground(Job* job){
    int status;
    int proc_status;
    int job_status;  
    pid_t pid;
    
    tcsetpgrp(mysh_terminal, job->pgid);
       
    do {
        printf("Wait again\n");
        pid = waitpid(-1, &status, WUNTRACED);
        printf("In put foreground: pid %d returned\n", pid);
        
        if(WIFSTOPPED(status)) proc_status = PROC_STOP;
        else proc_status = PROC_COMP;
        

        process_update_status(pid, proc_status);
        
        job_status = jobs_check_status(job);          
        printf("Job status: %d\n", job_status);      
        
    } while(job_status != JOB_COMP && job_status != JOB_STOP);

    
    job->status = job_status;
    job_print(job);
    if(job_status == JOB_COMP) {
        jobs_lock();
        jobs_remove_by_jid(job->id);
        jobs_unlock();                        
    }
    
    // jobs_unlock();
    tcsetpgrp(mysh_terminal, mysh_pgid);  
    tcsetattr(mysh_terminal, TCSADRAIN, &mysh_tmodes);  
      
}



/* ===== Signal Handler ===== */

void signal_wrapper(int signum, void* handler) {
    struct sigaction action;
    action.sa_handler = handler;
    action.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    if(sigaction(signum, &action, 0) == -1) {
        perror("Signal Error");
    }
}

//TODO: Add signal handlers
//Functionality see design doc

void sigchld_handler(int sig) {
    pid_t pid;
    int status;
    int proc_status;
    int job_status;
    
    printf("In sig child handler\n");
    
    while((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0) {                 
        
        if(WIFSTOPPED(status)) proc_status = PROC_STOP;
        else proc_status = PROC_COMP;
        
        if(process_update_status(pid, proc_status) == -1) continue ; //Can optimize here redundant loop
        Job* job = jobs_get_by_pid(pid);
        
        if(job->status == JOB_FORE) continue; //Don't handle foreground process
        
        job_status = jobs_check_status(job);
        if(job_status == JOB_RUN) continue; //Do nothing if job still running
                    
        job->status = job_status;
        job_print(job);
        if(job_status == JOB_COMP) {
            jobs_lock();
            jobs_remove_by_jid(job->id);
            jobs_unlock();                        
        }
    }
}

void jobs_lock() {
    sigprocmask(SIG_BLOCK, &chld_mask, NULL);
}

void jobs_unlock() {
    sigprocmask(SIG_UNBLOCK, &chld_mask, NULL);
}