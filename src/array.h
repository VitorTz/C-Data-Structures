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
Array* array_create();


/**
 * Desaloca a memória utilizada pelo array.
 * Não desaloca a memória ocupada pelos itens
*/
void array_destroy(Array* arr);


/**
 * Aumenta o tamanho do array em 2x
 * caso tenha atingido a capacidade máxima.
 * 
*/
void array_grow(Array* arr);


/**
 * Diminui o tamanho máximo do array para
 * acomodar apenas os itens de fato armazenados no array.
*/
void array_shrink(Array* arr);


/**
 * Remove todos os itens. 
 * Não desaloca a memória ocupada pelos itens
*/
void array_clear(Array* arr);


/**
 * Insere um item no final do array.
*/
void array_push_back(Array* arr, void* item);


/**
 * Insere um item no inicio do array.
*/
void array_push_front(Array* arr, void* item);


/**
 * Insere um item na posição index.
 * @return
 * 1 caso consiga inserir o item ou 0 caso index seja inválido.
*/
int array_insert(Array* arr, void* item, const size_t index);


/**
 * @return 
 * O item na posição index ou NULL caso o index seja inválido.
*/
void* array_at(Array* arr, const size_t index);


/**
 * Remove e retorna o item na posição index.
 * @return
 * O item na posição index ou NULL caso o index seja inválido.
*/
void* array_pop(Array* arr, const size_t index);


/**
 * Remove e retorna o ultimo item do index.
 * @return
 * O item na ultima posição ou NULL caso o array estaja vazio.
*/
void* array_pop_back(Array* arr);


/**
 * Remove e retorna o ultimo item do index.
 * @return
 * O item na primeira posição ou NULL caso o array estaja vazio.
*/
void* array_pop_front(Array* arr);



/**
 * @return
 * Retorna o ultimo item do array.
*/
const void* array_back(Array* arr);


/**
 * @return
 * Retorna o primeiro item do array.
*/
const void* array_front(Array* arr);


/**
 * Remove o item na posição index.
 * Não desaloca a memória ocupada pelo item.
 * @return
 * 1 caso tenha removido o item ou 0 caso o index seja inválido.
*/
int array_erase(Array* arr, const size_t index);



#endif