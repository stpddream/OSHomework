#include "jobs.h"

Job* job_createc(int id) {
    //Simple job create func for test
    Job* new_job = (Job*)malloc(sizeof(Job));
    new_job->id = id;
    new_job->status = 0;
    return new_job;
}

/**
 * Constructor for Job 
 */
Job* job_create(char* path, Process* process_head, int status) {
    Job* new_job = (Job*)malloc(sizeof(Job));
    new_job->id = id_edge++;
    new_job->status = status;
    if(path != NULL){
        new_job->path = (char*)malloc(sizeof(char)*strlen(path));
        strcpy(new_job->path, path);
    }   
    new_job->f_process = process_head;
    new_job->pgid = -1;
    return new_job;
}

void job_setpgid(Job* job, pid_t pid) {
    job->pgid = pid;
}





void job_print(Job* job) {
    printf("[%d] ", job->id);  
    if(job->status == JOB_BACK) printf("Running");
    else if (job->status == JOB_STOP) printf("Stopped");
    else if (job->status == JOB_COMP) printf("Done");
    printf("\t%s", job->path + 1);     
    if(job->path[0] == '&') printf(" &");
    printf("\n");
}


void job_free(Job* j){
    if(j->path != NULL) free(j->path);
    free(j);
}


/**
 * Init the job list
 * @return 
 */
int jobs_init() {
    //Init Dummy Node
    head = (JobNode*)malloc(sizeof(JobNode));
    head->job = job_create(NULL, NULL, -1); //Dummy Node
    tail = head;
    size = 0;
    id_edge = 0;
    head->next = NULL;
    return 0;
}

/**
 * Add job to list
 * @param job
 * @return 
 */
int jobs_add(Job* job) {
    tail->next = (JobNode*)malloc(sizeof(JobNode));
    tail = tail->next;
    tail->job = job;     
    tail->next = NULL;
    size++;
    return 0;    
}

/**
 * Remove #id job from list
 * @param id job id of the job to be removed
 * @return 0 if success; -1 if failure
 */
int jobs_remove_by_jid(int job_id) {  
    
    if(jobs_is_empty()) return -1;
    JobNode* current = head;
    
    while(current->next != NULL) {
        if(current->next->job->id == job_id) {
            current->next = current->next->next;
            if(current->next == NULL) tail = current;                        
            size--;
            return 0;
        }
        current = current->next;
    }
    return -1;
}

/****Dont use !! bug!! */
int jobs_remove_by_pid(pid_t pid) {  
    
    if(jobs_is_empty()) return -1;
    JobNode* current = head;
    JobNode* tmp;

    while(current->next != NULL) {
        if(current->next->job->pid == pid) {
            tmp = current->next;
            current->next = current->next->next;
            if(tmp == tail){ 
                tail = current;
                tail->next = NULL;
            }
            size--;
            /** free allocated memory **/
            job_free(tmp->job);
            free(tmp);  
            return 0;
        }
        current = current->next;
    }
    return -1;
}





/**
 * Check is job is empty
 * @return 
 */
int jobs_is_empty() {
    return size == 0;
}

/**
 * Get job by id
 * @param id
 * @return 
 */
Job* jobs_get_by_jid(int jid) {

    if(jid == TAIL_ID) return tail->job;

    JobNode* current = head->next;
    
    while(current != NULL) {
        if(current->job->id == jid) return current->job;
        current = current->next;
    }
    return NULL;
}

Job* jobs_get_by_pid(pid_t pid){
    
    JobNode* current = head->next;
    while(current != NULL) {
        Process* process = current->job->f_process;
        while(process != NULL) {
            if(process->pid == pid) {
                return current->job;               
            }            
            process = process->next;
        }       
        current = current->next;
    }
    fprintf(stderr, "ERROR: Process not found\n");
    return NULL;
}

/**
 * Update the status for process pid
 * @param pid
 * @param status
 */
int process_update_status(pid_t pid, int status) {
    
    JobNode* current = head->next;
    while(current != NULL) {
        Process* process = current->job->f_process;
        while(process != NULL) {
            if(process->pid == pid) {
                process->status = status;     
                return 0;
            }            
            process = process->next;
        }
        current = current->next;
    }
    fprintf(stderr, "ERROR: Process not found\n");
    return -1;    
}

int jobs_check_status(Job* job) {
    Process* process = job->f_process;
    int sum = 0;
    int count = 0;
    
    
    while(process != NULL) {
        if(process->status == PROC_RUN) return JOB_RUN;
        sum += process->status;
        process = process->next;
        count++;
    }   
    
    if((sum / count) == PROC_STOP) return JOB_STOP;
    else if((sum / count) == PROC_COMP) return JOB_COMP;
    else return JOB_RUN;
}




void jobs_print() {
    printf("Printing: \n");
    JobNode* current = head->next;    
    while(current != NULL) {        
        job_print(current->job);
        current = current->next;
    }
}
    
Job* get_fg_job(){
    if(tail->job!=NULL && tail->job->status == JOB_FORE){
        return tail->job;
    }
    return NULL;
}


//Test func to print the whole list
void print_jobs() {
    JobNode* current = head->next;
    
    while(current != NULL) {
        printf("id %d->", current->job->id);
        current = current->next;
    }
    printf("NULL\n");
}
