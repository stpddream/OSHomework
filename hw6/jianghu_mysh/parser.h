/* 
 * Project: mysh
 * File:   parser.h
 * Author: Panda
 *
 * Created on February 17, 2014, 8:42 PM
 */

#ifndef PARSER_H
#define	PARSER_H

#include <stdlib.h>
#include <string.h>

#include <ctype.h>
#include "cmd_history.h"
#include "util.h"

#define MAX_ARG_NUM 30
#define DIR_IN 1
#define DIR_OUT 0

char* strip_space(char*);

int parse_args(char*, char**);
int parse_process(char*, char**);
int parse_space(char*, char**);



#endif	/* PARSER_H */

