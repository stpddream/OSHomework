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

#define MAX_ARG_NUM 30

void parse_args(char*, char**);
char* strip_space(char*);




#endif	/* PARSER_H */

