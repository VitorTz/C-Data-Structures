#ifndef C_DATA_STRUCTURES_UTIL_H
#define C_DATA_STRUCTURES_UTIL_H
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int* malloc_int(const size_t total) {
    int* n = malloc(sizeof(int) * total);
    for (int i = 0; i < total; i++) {
        int* p = n + i;
        *p = i;
    }
    return n;
}

int randint(const int start, const int end) {
    return rand() % (end - start + 1) + start;    
}

void print_result(const char* test_name, const int result) {
    if (result == 1) {
        printf("[TEST %s PASSED]\n", test_name);
    } else {
        printf("[TEST %s FAIL]\n", test_name);
    }
}

#endif