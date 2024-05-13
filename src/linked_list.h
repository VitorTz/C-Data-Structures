#ifndef C_DATA_STRUCTURES_LINKED_LIST_H
#define C_DATA_STRUCTURES_LINKED_LIST_H
#include <stdlib.h>


typedef struct LkNode_ {
    void* data;
    struct LkNode_* left;
    struct LkNode_* right;
} LkNode;


typedef struct LinkedList_ {
    LkNode* head;
    LkNode* tail;
    size_t size;
} LinkedList;


LinkedList* linked_list_create() {
    LinkedList* lk = (LinkedList*) malloc(sizeof(LinkedList));
    lk->head = lk->tail = NULL;
    lk->size = 0;
    return lk;
}


LkNode* linked_list_create_node(void* data) {
    LkNode* node = (LkNode*) malloc(sizeof(LkNode));
    node->left = node->right = NULL;
    node->data = data;
    return node;
}


void linked_list_destroy(LinkedList* lk) {
    LkNode* node = lk->head;
    while (node != NULL) {
        LkNode* aux = node;
        node = node->right;
        free(aux);        
    }
    free(lk);
}


void linked_list_destroy_node(LkNode* node) {
    free(node);
}


void linked_list_push_back(LinkedList* lk, void* data) {
    LkNode* node = linked_list_create_node(data);
    switch (lk->size) {
        case 0:
            lk->head = node; 
            break;
        case 1:
            lk->tail = node;
            lk->head->right = lk->tail;
            lk->tail->left = lk->head;
            break;
        default:
            lk->tail->right = node;
            node->left = lk->tail;
            lk->tail = node;
            break;
    }
    lk->size++;
}


void linked_list_push_front(LinkedList* lk, void* data) {
    LkNode* node = linked_list_create_node(data);
    switch (lk->size) {
        case 0:
            lk->head = node; 
            break;
        case 1:
            lk->head->left = node;
            node->right = lk->head;
            lk->tail = lk->head;
            lk->head = node;            
            break;
        default:
            lk->head->left = node;
            node->right = lk->head;
            lk->head = node;            
            break;
    }
    lk->size++;
}


LkNode* linked_list_node_at(LinkedList* lk, const size_t index) {
    if (index >= lk->size) {
        return NULL;
    }
    LkNode* node = NULL;
    if (index < lk->size / 2) {
        node = lk->head;
        for (int i = 0; i < index; i++) {
            node = node->right;
        }
        return node;
    }
    node = lk->tail;
    for (int i = lk->size-1; i > index; i--) {
        node = node->left;
    }
    return node;
} 


void* linked_list_pop(LinkedList* lk, const size_t index) {
    LkNode* node = linked_list_node_at(lk, index);
    if (node == NULL) {
        return NULL;        
    }
    void* data = node->data;
    if (node->left != NULL) {
        node->left->right = node->right;
    }
    if (node->right != NULL) {
        node->right->left = node->left;
    }
    linked_list_destroy_node(node);
    lk->size--;
    return data;
}


void* linked_list_pop_front(LinkedList* lk) {
    return linked_list_pop(lk, 0);
}


void* linked_list_pop_back(LinkedList* lk) {
    return linked_list_pop(lk, lk->size-1);
}


const void* linked_list_back(LinkedList* lk) {
    LkNode* node = linked_list_node_at(lk, lk->size-1);
    if (node == NULL) {
        return NULL;
    }
    return node->data;
}


const void* linked_list_front(LinkedList* lk) {
    LkNode* node = linked_list_node_at(lk, 0);
    if (node == NULL) {
        return NULL;
    }
    return node->data;
}


void* linked_list_at(LinkedList*lk, const size_t index) {
    LkNode* node = linked_list_node_at(lk, index);
    if (node == NULL) {
        return NULL;
    }
    return node->data;
}



void linked_list_insert(LinkedList* lk, void* data, const size_t index) {
    LkNode* newNode = linked_list_create_node(data);
    LkNode* node = linked_list_node_at(lk, index);    
    if (node->left != NULL) {
        node->left->right = newNode;
        newNode->left = node->left;
    }
    node->left = newNode;
    newNode->right = node;
    lk->size++;
}


void linked_list_erase(LinkedList* lk, const size_t index) {
    LkNode* node = linked_list_node_at(lk, index);
    if (node->left != NULL) {
        node->left->right = node->right;
    }
    if (node->right != NULL) {
        node->right->left = node->left;
    }
    linked_list_destroy_node(node);
    node = NULL;
    lk->size--;
}




#endif