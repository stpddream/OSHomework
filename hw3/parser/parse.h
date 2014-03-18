#ifndef __parse__
#define __parse__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <sys/types.h>
#include "jobs.h"

#define MAX_CMD 100

int parse_cmds(char* cmdline, char** cmdlines);
int parse_space(char* cmd_str, char** args);

#endif
