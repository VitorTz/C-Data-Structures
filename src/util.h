#ifndef C_DATA_STRUCTURES_UTIL_H
#define C_DATA_STRUCTURES_UTIL_H
#include <stdio.h>
#include <stdlib.h>


int* malloc_int(const size_t total);

int assert(const int a, const int b);


void print_result(const char* test_name, const int result);

#endif