#include "util.h"

int round_to(int val, int base) {
    return ((val / base) + 1) * base;
}
