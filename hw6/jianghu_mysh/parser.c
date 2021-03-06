#include "parser.h"

int parse_args(char* line, char** commands) {
    char* prv;
    int count = 0;
    int back_flag = 0;

    while (*line != '\0') {

        while (*line == ' ' && *line != '\0') line++; //Skip white spaces        

        if (*line == '&' || *line == ';') {
            printf("-mysh:\tsyntax error\n");
            return 0;
        }

        prv = line; //Start of command        

        //Find the next delimiter
        while (*line != '&' && *line != ';' && *line != '\0') line++;

        if (*line == '&') back_flag = 1;
        else back_flag = 0;

        //Set the end of command flag
        if (*line != '\0') *line++ = '\0';
        commands[count] = malloc((1 + strlen(prv)) * sizeof (char));

        //Set background flag
        if (back_flag) commands[count][0] = '&';
        else commands[count][0] = '%';

        strcpy(commands[count++] + 1, prv);
    }

    return count;
}

int parse_process(char* line, char** processes) {

    int i = 0;
    char* tok;
    tok = strtok(line, "|");
    while (tok != NULL) {
        processes[i++] = strip_space(tok);
        tok = strtok(NULL, "|");
    }

    return i;
}

int parse_redirection(char* line, char** args, char* file, int* redir_mode) {
    int i = 0, j = 0;
    int n_args;
    while (line[i] != '\0') {
        if (line[i] == '>') {
            if (line[i + 1] == '>') {
                n_args = parse_space(strip_space(substring(line, 0, i)), args);
                strcpy(file, strip_space(substring(line, i + 2, strlen(line) + 1)));
                while (file[j] != '\0' && file[j] != ' ') j++;
                if (file[j] == ' ') {
                    n_args += parse_space(strip_space(substring(file, j + 1, strlen(file) + 1)), args + n_args);
                    strcpy(file, strip_space(substring(file, 0, j)));
                }
                (*redir_mode) = WRITE_APND;
                return n_args;
            } else {
                n_args = parse_space(strip_space(substring(line, 0, i)), args);
                strcpy(file, strip_space(substring(line, i + 1, strlen(line) + 1)));
                while (file[j] != '\0' && file[j] != ' ') j++;
                if (file[j] == ' ') {

                    n_args += parse_space(strip_space(substring(file, j + 1, strlen(file) + 1)), args + n_args);
                    strcpy(file, strip_space(substring(file, 0, j)));
                }
                (*redir_mode) = WRITE_OVRWT;
                return n_args;
            }
        } else if (line[i] == '<') {
            n_args = parse_space(strip_space(substring(line, 0, i)), args);
            strcpy(file, strip_space(substring(line, i + 1, strlen(line) + 1)));
            while (file[j] != '\0' && file[j] != ' ') j++;
            if (file[j] == ' ') {
                n_args += parse_space(strip_space(substring(file, j + 1, strlen(file) + 1)), args + n_args);
                strcpy(file, strip_space(substring(file, 0, j)));
            }
            (*redir_mode) = READ_MODE;
            return n_args;
        }
        i++;
    }
    n_args = parse_space(strip_space(substring(line, 0, i)), args);
    strcpy(file, "");

    (*redir_mode) = -1;
    return n_args;
}

int parse_space(char* cmd_str, char** args) {
    int i = 0;
    char* tok;
    tok = strtok(cmd_str, " \t\n");
    while (tok != NULL) {
        args[i++] = tok;
        tok = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
    return i;
}

/**
 * Clean extra space for string
 * @param str
 * @return 
 */
char* strip_space(char *str) {

    int i = -1;
    char ch;


    //Skip white space characters at the beginning
    while ((ch = str[++i]) != '\0' && (isspace(ch) || ch == '\n'));

    //Move nonspace to the start of string
    int j = strlen(str);

    while ((ch = str[--j]) >= i && (isspace(ch) || ch == '\n'));
    char* res_str = substring(str, i, j + 1);
    return res_str;
}

