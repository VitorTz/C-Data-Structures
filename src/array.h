#ifndef C_DATA_STRUCTURES_ARRAY_H
#define C_DATA_STRUCTURES_ARRAY_H
#include <stdlib.h>


typedef struct Array_ {
    void** data;    
    size_t capacity;
    size_t size;
} Array;


/**
 * Cria um array de capacidade inicial = 8
*/
Array* array_create() {
    Array* arr = malloc(sizeof(Array));
    arr->capacity = 8;
    arr->size = 0;    
    arr->data = malloc(sizeof(void*) * arr->capacity);
    return arr;
}


/**
 * Desaloca a memória utilizada pelo array.
 * Não desaloca a memória ocupada pelos itens
*/
void array_destroy(Array* arr) {
    if (arr != NULL) {
        free(arr->data);
        arr->data = NULL;
        free(arr);
        arr = NULL;
    }
}


/**
 * Aumenta o tamanho do array em 2x
 * caso tenha atingido a capacidade máxima.
 * 
*/
void array_grow(Array* arr) {
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->data = realloc(arr->data, sizeof(void*) * arr->capacity);
    }
}


/**
 * Diminui o tamanho máximo do array para
 * acomodar apenas os itens de fato armazenados no array.
*/
void array_shrink(Array* arr) {
    arr->capacity = arr->size == 0 ? 8 : arr->size;
    arr->data = realloc(arr->data, sizeof(void*) * arr->capacity);
}


/**
 * Remove todos os itens. 
 * Não desaloca a memória ocupada pelos itens
*/
void array_clear(Array* arr) {
    free(arr->data);
    arr->capacity = 8;
    arr->size = 0;
    arr->data = malloc(sizeof(void*) * arr->capacity);
}


/**
 * Insere um item no final do array.
*/
void array_push_back(Array* arr, void* item) {
    array_grow(arr);
    arr->data[arr->size++] = item;
}


/**
 * Insere um item no inicio do array.
*/
void array_push_front(Array* arr, void* item) {
    array_grow(arr);
    for (int i = arr->size-1; i >= 0; i--) {
        arr->data[i+1] = arr->data[i];
    }
    arr->data[0] = item;
    arr->size++;
}


/**
 * Insere um item na posição index.
 * @return
 * 1 caso consiga inserir o item ou 0 caso index seja inválido.
*/
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


/**
 * @return 
 * O item na posição index ou NULL caso o index seja inválido.
*/
void* array_at(Array* arr, const size_t index) {    
    return arr->data[index];
}


/**
 * Remove e retorna o item na posição index.
 * @return
 * O item na posição index ou NULL caso o index seja inválido.
*/
void* array_pop(Array* arr, const size_t index) {
    if (arr->size == 0 || index >= arr->size) {
        return NULL;
    }
    void* p = arr->data[index];
    for (int i = index; i < arr->size-1; i++) {
        arr->data[i] = arr->data[i+1];
    }
    arr->size--;
    if (arr->size < arr->capacity / 4) {
        array_shrink(arr);
    }
    return p;
}


/**
 * Remove e retorna o ultimo item do index.
 * @return
 * O item na ultima posição ou NULL caso o array estaja vazio.
*/
void* array_pop_back(Array* arr) {
    return array_pop(arr, arr->size-1);
}


/**
 * Remove e retorna o ultimo item do index.
 * @return
 * O item na primeira posição ou NULL caso o array estaja vazio.
*/
void* array_pop_front(Array* arr) {
    return array_pop(arr, 0);
}



/**
 * @return
 * Retorna o ultimo item do array.
*/
const void* array_back(Array* arr) {
    if (arr->size == 0) {
        return NULL;
    }
    return arr->data[arr->size-1];
}


/**
 * @return
 * Retorna o primeiro item do array.
*/
const void* array_front(Array* arr) {
    if (arr->size == 0) {
        return NULL;
    }
    return arr->data;
}


/**
 * Remove o item na posição index.
 * Não desaloca a memória ocupada pelo item.
 * @return
 * 1 caso tenha removido o item ou 0 caso o index seja inválido.
*/
int array_erase(Array* arr, const size_t index) {
    if (index >= arr->size) {
        return 0;
    }
    for (int i = index; i < arr->size-1; i++) {
        arr->data[i] = arr->data[i+1];
    }
    arr->size--;
    if (arr->size < arr->capacity / 4) {
        array_shrink(arr);
    }
    return 1;
}



#endif