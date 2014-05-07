#include "kernel_mem.h"

Dev* cur_dev;
User* cur_user;

void set_user(User* user) {
    cur_user = user;
}

