#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int  main(){
  pid_t pid;
  char *pathvar;
  char newpath[1000];
  int in, out;

  pathvar = getenv("PATH");
  strcpy(newpath, pathvar);
  strcat(newpath, ":u/userid/bin");
  setenv("PATH", newpath, 0);

  if ((pid = fork()) == -1){
    perror("fork error");
  }else if (pid == 0) {
    in = open("input", O_RDONLY);
    dup2(in, STDIN_FILENO);
    close(in);
    //out = open("output", O_WRONLY|O_CREAT, 0666);
    //dup2(out, STDOUT_FILENO);
    //close(out);
    char*args[5] = {"sort"};
    execvp(args[0], args);
    //printf("Return not expected. Must be an execlp error\n");
  }
  return 0;
}
