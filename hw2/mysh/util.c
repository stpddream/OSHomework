#include "util.h"

/**
 * Mod function that computes the "positive" remainder for negative n1
 * @param n1
 * @param n2 has to be positive
 * @return 
 */
int mod(int n1, int n2) {              
    int res = n1 % n2;
    return (res < 0) ? res + n2 : res;        
}


/**
 * Print out a command
 * @param args
 */
void print_cmd(char** args) {
    int i = 0;   
    while(args[i] != NULL) {
        printf("%s ", args[i++]);
    }   
}


/**
 * Compare two command
 * @param a
 * @param b
 * @return 0 if equal, -1 otherwise
 */
int cmd_compare(char** a, char** b) {
    int i = 0;  

    while(a[i] != NULL && b[i] != NULL) {  
        if(strcmp(a[i], b[i]) != 0) return -1;      
        i++;
    }
    
    if(a[i] != NULL) return -1;
    if(b[i] != NULL) return -1;
    
    return 0;

}


/**
 * Non standard substring function
 * @param str
 * @param start: index (starting from 0) inclusive
 * @param end: index exclusive
 * @return substring
 */
char* substring(char* str, int start, int end) {    
      char* num = (char*)malloc(sizeof(char)*(end - start + 1));
      strncpy(num, str + start, end - start);      
      return num;
}


/**
 * Non standard atoi function with error check
 * @param str
 * @param res: result integer
 * @return 
 */
int int_valueof(char* str, int* res) {
    
    char* end;
    int n = strtol(str, &end, 10);
    
    //Check invalid input
    if(end == str || *end != '\0') {
        return -1;
    }
    
    *res = n;
    return 0;
}



extern void clean_up();

/**
 * Exit program and do clean up
 */
void exit_clean() {
    clean_up();
    exit(0);
}