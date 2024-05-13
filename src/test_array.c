#include "test_array.h"



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
        int* p = (int*) array_at(arr, i);
        if (assert(*p, i) == 0) {
            test_passed = 0;
            printf("Erro. Esperado -> %d | Encontrado -> %d\n", i, *p);
        }
        printf("%d\n", *p);
    }

    print_result(test_name, test_passed);    
    
    array_destroy(arr);
    free(nums);
}
