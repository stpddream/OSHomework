#include "kernel_mem.h"


User* user_create(char* uname, int priv) {
    User* new_user = (User*)malloc(sizeof(User));
    strcpy(new_user->name, uname);
    new_user->privilege = priv;
    return new_user;
}
