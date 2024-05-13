#include "util.h"


int* malloc_int(const size_t total) {
    int* n = malloc(sizeof(int) * total);
    for (int i = 0; i < total; i++) {
        int* p = n + i;
        *p = i;
    }
    return n;
}


int assert(const int a, const int b) {
    return a == b ? 1 : 0;
}


void print_result(const char* test_name, int result) {
    if (result == 1) {
        printf("[TEST %s PASSED]\n", test_name);
    } else {
        printf("[TEST %s FAIL]\n", test_name);
    }
}