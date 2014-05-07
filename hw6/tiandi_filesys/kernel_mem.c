#include "kernel_mem.h"

Dev* cur_dev;
User* cur_user;
iNode* cur_dir;
int cur_dir_idx;
char* cur_path;

void set_user(User* user) {
    cur_user = user;
}

void set_cur_idx(int idx) {
    cur_dir_idx = idx;
}
