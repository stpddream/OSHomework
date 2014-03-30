#include "util.h"

int round_to(int val, int base) {
    return ((val / base) + 1) * base;
}

char* p_status(int status) {
    return (status == MEM_FREE) ? "Free" : "Occupied";
}
