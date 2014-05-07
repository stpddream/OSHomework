#include "cmd_control.h"

/* ===== Built in functions ===== */

void b_exit() {
    exit_clean();
}

int exec_job(Job* new_job) {

    Process *cur_proc = new_job->f_process;
    char* cur_cmd = cur_proc->args[0]+1;

    if (strcmp(cur_cmd, "ls") == 0) {
        cmd_ls(cur_proc->args + 1, cur_proc->n_args - 1);
    } else if (strcmp(cur_cmd, "chmod") == 0) {
        printf("chmod:\t under construction...\n");
    } else if (strcmp(cur_cmd, "mkdir") == 0) {
        cmd_mkdir(cur_proc->args + 1, cur_proc->n_args - 1);
    } else if (strcmp(cur_cmd, "rmdir") == 0) {
        cmd_rmdir(cur_proc->args + 1, cur_proc->n_args - 1);
    } else if (strcmp(cur_cmd, "cd") == 0) {
        if (cur_proc->n_args == 1) {
            printf("please enter directory name\n");
        } else {
            cmd_cd(cur_proc->args[1]);
        }
    } else if (strcmp(cur_cmd, "pwd") == 0) {
        cmd_pwd();
    } else if (strcmp(cur_cmd, "cat") == 0) {
        cmd_cat(cur_proc->args[1]);
    } else if (strcmp(cur_cmd, "more") == 0) {
        printf("more:\t under construction...\n");
    } else if (strcmp(cur_cmd, "rm") == 0) {
        cmd_rm(cur_proc->args + 1, cur_proc->n_args - 1);
    } else if (strcmp(cur_cmd, "mount") == 0) {
        printf("mount:\t under construction...\n");
    } else if (strcmp(cur_cmd, "unmount") == 0) {
        printf("unmount:\t under construction...\n");
    } else if(strcmp(cur_cmd, "exit") == 0){
        b_exit();
    } else {
        printf("invalid command, please try again\n");
    }
    return 0;
}

void sigchld_handler(int sig) {
    pid_t pid;
    int status;
    int proc_status;
    int job_status;
    
    //printf("In sig child handler\n");
    
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
    }
}