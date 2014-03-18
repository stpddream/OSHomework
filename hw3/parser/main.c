#include "main.h"

int main(){
    char* input;
    char** cmdlines = malloc(MAX_CMD*sizeof(char*));
    char** args = malloc(MAX_CMD*sizeof(char*));
    int i,j, n_cmd, n_args;
    while(1){
        if((input = readline(""))!=NULL){
            jobs_init();
            n_cmd = parse_cmds(input, cmdlines);
            for(i = 0; i < n_cmd; i++){
                
                Job* new_job = job_create((cmdlines[i][0] == '&'? JOB_BACK:JOB_FORE),cmdlines[i]+1,0);  
                jobs_add(new_job);
                /*
                n_args = parse_space(cmdlines[i]+1, args);
                for(j = 0; j < n_args; j++){
                    printf("%s\n",args[j]);
                }*/

            }
            
	    //print_jobs();
              jobs_print(); 
        }
        // Free input.
        free(input);
    }
   return 0; 
}


