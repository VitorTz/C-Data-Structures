#include <stdio.h>
#include "linked_list.h"
#include "util.h"



void test_linked_list_push_back() {
    const int total = 10;
    LinkedList* lk = linked_list_create();
    int* nums = malloc_int(total);
    for (int i = 0; i < total; i++) {
        linked_list_push_back(lk, nums + i);
    }
    for (int i = 0; i < total; i++) {
        int* p = (int*) linked_list_at(lk, i);
        printf("%d\n", *p);
    }
    linked_list_destroy(lk);
}


void test_linked_list_push_front() {
    const int total = 10;
    LinkedList* lk = linked_list_create();
    int* nums = malloc_int(total);
    for (int i = 0; i < total; i++) {
        linked_list_push_front(lk, nums + i);
    }
    for (int i = 0; i < total; i++) {
        int* p = (int*) linked_list_at(lk, i);
        printf("%d\n", *p);
    }
    linked_list_destroy(lk);
}


void test_linked_list_pop() {
    const int total = 10;
    LinkedList* lk = linked_list_create();
    int* nums = malloc_int(total);
    for (int i = 0; i < total; i++) {
        linked_list_push_back(lk, nums + i);
    }

    int* p1 = (int*) linked_list_pop(lk, 1);
    int* p2 = (int*) linked_list_pop(lk, 1);
    int* p3 = (int*) linked_list_pop(lk, 1);
    printf("%d\n", *p1);
    printf("%d\n", *p2);
    printf("%d\n", *p3);

    linked_list_destroy(lk);
}


void test_linked_list_erase() {
    const int total = 10;
    LinkedList* lk = linked_list_create();
    int* nums = malloc_int(total);
    for (int i = 0; i < total; i++) {
        linked_list_push_back(lk, nums + i);
    }

    linked_list_erase(lk, 1);
    linked_list_erase(lk, 1);
    linked_list_erase(lk, 1);
    
    for (int i = 0; i < lk->size; i++) {
        int*p = (int*) linked_list_at(lk, i);
        printf("%d\n", *p);        
    }
    linked_list_destroy(lk);
    free(nums);
}


void test_linked_list_insert() {
    const int total = 10;
    LinkedList* lk = linked_list_create();
    int* nums = malloc_int(total);
    for (int i = 0; i < total; i++) {
        linked_list_push_back(lk, nums + i);
    }

    linked_list_insert(lk, nums + 9, 1);
    linked_list_insert(lk, nums + 8, 1);
    linked_list_insert(lk, nums + 7, 1);
    
    for (int i = 0; i < lk->size; i++) {
        int*p = (int*) linked_list_at(lk, i);
        printf("%d\n", *p);        
    }
    linked_list_destroy(lk);
    free(nums);
}