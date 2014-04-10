#include <stdio.h>

int main(int argc, char** argv) {
    
    FILE* fp;
    fp = fopen("datafile-frag", "r");
    
    fseek(fp, 512, SEEK_SET);
    
    int test;
    
    fread((void*)&test, sizeof(int), 1, fp);
    
    printf("Read is %d", test);
    
    
    
    
    return 0;
    
    
}
