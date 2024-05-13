#ifndef C_DATA_STRUCTURES_TEST_ARRAY_H
#define C_DATA_STRUCTURES_TEST_ARRAY_H
#include "array.h"
#include "util.h"
#include <stdio.h>


void test_array_push_back() {
    const char test_name[] = "ARRAY PUSH BACK";
    printf("[TEST %s]\n", test_name);

    Array* arr = array_create();
    const int size = 100000;
    int* nums = malloc_int(size);

    for (int i = 0; i < size; i++) {
        array_push_back(arr, nums + i);
    }

    int test_passed = 1;
    for (int i = 0; i < size; i++) {
        int p = *((int*) array_at(arr, i));
        if (p != i) {
            test_passed = 0;
            printf("Erro. Esperado -> %d | Encontrado -> %d\n", i, p);
        }
        printf("%d\n", p);
    }

    print_result(test_name, test_passed);    
    
    array_destroy(arr);
    free(nums);
}

void test_array_push_front() {
    const char test_name[] = "ARRAY PUSH FRONT";
    printf("[TEST %s]\n", test_name);
    Array* arr = array_create();

    const int total = 100000;
    int* nums = malloc_int(total);
    
    for (int i = 0; i < total; i++) {
        array_push_front(arr, nums + i);
    }

    int result = 1;
    for (int i = 0; i < total; i++) {   
        int r1 = total - 1 - i;
        int r2 = *((int*) array_at(arr, i));
        if (r1 != r2) {
            result = 0;
            printf("ERRO. Index: %d | Esperado %d | Encontrado %d\n", i, r1, r2);            
        }
    }

    print_result(test_name, result);
    array_destroy(arr);
    free(nums);
}

void test_array_pop() {
    const char test_name[] = "ARRAY POP";
    printf("[TEST %s]\n", test_name);

    Array* arr = array_create();
    const int total = 100000;
    int* nums = malloc_int(total);
    
    for (int* n = nums; n != nums + total; n++) {
        array_push_back(arr, n);
    }

    int* n2 = array_pop(arr, 14);
    int* n1 = array_pop(arr, 10);
    printf("%d\n", *n2);
    printf("%d\n", *n1);
    printf("%ld\n", arr->size);
    array_destroy(arr);
    free(nums);
}


void test_array_pop_back() {
    const char test_name[] = "ARRAY POP BACK";
    printf("[TEST %s]\n", test_name);   
    Array* arr = array_create();
    const int total = 100000;
    int* nums = malloc_int(total);
    
    for (int* n = nums; n != nums + total; n++) {
        array_push_back(arr, n);
    } 
    int result = 1;
    for (int i = total -1; i >= 0; i--) {
        int r = *((int*) array_pop_back(arr)); 
        printf("%d\n", r);
        if (r != i) {
            result = 0;
            printf("ERRO. Index: %d | Esperado %d | Encontrado %d\n", i, i, r);
        }
    }
    
    printf("Array size: %ld\n", arr->size);
    printf("Array capacity: %ld\n", arr->capacity);
    print_result(test_name, result);
    array_destroy(arr);
    free(nums);
}


void test_array_pop_front() {
    const char test_name[] = "ARRAY POP FRONT";
    printf("[TEST %s]\n", test_name);   
    Array* arr = array_create();
    const int total = 100000;
    int* nums = malloc_int(total);
    
    for (int* n = nums; n != nums + total; n++) {
        array_push_back(arr, n);
    } 
    int result = 1;
    for (int i = 0; i < total; i++) {
        int r = *((int*) array_pop_front(arr)); 
        printf("%d\n", r);
        if (r != i) {
            result = 0;
            printf("ERRO. Index: %d | Esperado %d | Encontrado %d\n", i, i, r);
        }
    }
    
    printf("Array size: %ld\n", arr->size);
    printf("Array capacity: %ld\n", arr->capacity);
    print_result(test_name, result);
    array_destroy(arr);
    free(nums);
}


#endif 