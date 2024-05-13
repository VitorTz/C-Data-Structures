#include "array.h"



Array* array_create() {
    Array* arr = malloc(sizeof(Array));
    arr->capacity = 8;
    arr->size = 0;
    arr->data = malloc(sizeof(void*) * arr->capacity);
    return arr;
}


void array_destroy(Array* arr) {
    if (arr != NULL) {
        free(arr->data);
        arr->data = NULL;
        free(arr);
        arr = NULL;
    }
}


void array_grow(Array* arr) {
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->data = realloc(arr->data, sizeof(void*) * arr->capacity);
    }
}


void array_shrink(Array* arr) {
    arr->capacity = arr->size;
    arr->data = realloc(arr->data, sizeof(void*) * arr->capacity);
}


void array_clear(Array* arr) {
    free(arr->data);
    arr->capacity = 8;
    arr->size = 0;
    arr->data = malloc(sizeof(void*) * arr->capacity);
}


void array_push_back(Array* arr, void* item) {
    array_grow(arr);
    arr->data[arr->size++] = item;
}


void array_push_front(Array* arr, void* item) {
    array_grow(arr);
    for (int i = arr->size; i > 0; i++) {
        arr->data[i+1] = arr->data[i];
    }
    arr->size++;
}


int array_insert(Array* arr, void* item, const size_t index) {
    if (index > arr->size) {
        return 0;
    }
    for (int i = arr->size; i > index; i--) {
        arr->data[i+1] = arr->data[i];
    }
    arr->data[index] = item;
    arr->size++;
}


void*  array_at(Array* arr, const size_t index) {        
    if (arr->size == 0 || index >= arr->size) {
        return NULL;
    }
    return arr->data[index];
}


void* array_pop(Array* arr, const size_t index) {
    if (arr->size == 0 || index >= arr->size) {
        return NULL;
    }
    void* p = arr->data[index];
    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i+1];
    }
    arr->size--;
    return p;
}


void* array_pop_back(Array* arr) {
    return array_pop(arr, arr->size-1);
}


void* array_pop_front(Array* arr) {
    return array_pop(arr, 0);
}


const void* array_back(Array* arr) {
    if (arr->size == 0) {
        return NULL;
    }
    return arr->data[arr->size-1];
}


const void* array_front(Array* arr) {
    if (arr->size == 0) {
        return NULL;
    }
    return arr->data;
}


int array_erase(Array* arr, const size_t index) {
    if (index >= arr->size) {
        return 0;
    }
    for (int i = index; i < arr->size; i++) {
        arr->data[i] = arr->data[i+1];
    }
    arr->size--;
    return 1;
}