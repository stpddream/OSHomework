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
Job* job_create(int status, char* path, pid_t pid) {
    Job* new_job = (Job*)malloc(sizeof(Job));
    new_job->id = (tail == NULL? 0 : tail->job->id+1);
    new_job->status = status;
    if(path!=NULL){
        new_job->path = (char*) malloc(sizeof(char)*strlen(path));
        strcpy(new_job->path, path);
    }
    new_job->pid = pid;
    return new_job;
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
    head = (ListNode*)malloc(sizeof(ListNode));
    head->job = job_create(-1, NULL, 0); //Dummy Node
    tail = head;
    size = 0;
    head->next = NULL;
    return 0;
}

/**
 * Add job to list
 * @param job
 * @return 
 */
int jobs_add(Job* job) {
    tail->next = (ListNode*)malloc(sizeof(ListNode));
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
int jobs_remove_by_jid(int jid) {  
    
    if(jobs_is_empty()) return -1;
    ListNode* current = head;
    
    while(current->next != NULL) {
        if(current->next->job->id == jid) {
            current->next = current->next->next;
            size--;
            return 0;
        }
        current = current->next;
    }
    return -1;
}

int jobs_remove_by_pid(pid_t pid) {  
    
    if(jobs_is_empty()) return -1;
    ListNode* current = head;
    ListNode* tmp;

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

    ListNode* current = head->next;
    
    while(current != NULL) {
        if(current->job->id == jid) return current->job;
        current = current->next;
    }
    return NULL;
}

Job* jobs_get_by_pid(pid_t pid){
    ListNode* current = head->next;

    while(current!=NULL){
        if(current->job->pid == pid) return current->job;    
        current = current->next;
    }

    return NULL;
}


void job_print(Job* job) {
    printf("[%d] ", job->id);
    if(job->status == JOB_BACK) printf("Running");
    else if (job->status == JOB_SUSP) printf("Stopped");
     
}

void jobs_print() {
    ListNode* current = head->next;
    
    while(current != NULL) {
        printf("[%d] ", current->job->id);
        if(current->job->status == JOB_BACK) printf("Running");
        else if (current->job->status == JOB_SUSP) printf("Stopped");
        printf("\t%s", current->job->path+1);
        if(current->job->path[0] == '&') printf(" &\n");
        else printf("\n");
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
    ListNode* current = head->next;
    
    while(current != NULL) {
        printf("id %d->", current->job->id);
        current = current->next;
    }
    printf("NULL\n");
}
