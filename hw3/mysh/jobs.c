#include "jobs.h"

int id_edge = 0;

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
    new_job->id = id_edge++;
    new_job->status = status;
    new_job->path = path;
    new_job->pid = pid;
    return new_job;
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
    size++;
    return 0;    
}

/**
 * Remove #id job from list
 * @param id job id of the job to be removed
 * @return 0 if success; -1 if failure
 */
int jobs_remove(int id) { 
    
    if(jobs_is_empty()) return -1;
    ListNode* current = head;
    
    while(current->next != NULL) {
        printf("remove id: %d\n", current->next->job->id);
        if(current->next->job->id == id) {
            current->next = current->next->next;
            size--;
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
Job* jobs_get(int id) {
    ListNode* current = head->next;
    
    while(current != NULL) {
        if(current->job->id == id) return current->job;
        current = current->next;
    }
    return NULL;
}


void jobs_print() {
    ListNode* current = head->next;
    
    while(current != NULL) {
        printf("[%d] ", current->job->id);
        if(current->job->status == JOB_BACK) printf("Running");
        printf("\t%s\n", current->job->path);
        current = current->next;
    }
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