#ifndef C_DATA_STRUCTURES_AVL_TREE_H
#define C_DATA_STRUCTURES_AVL_TREE_H
#include <stdlib.h>


typedef struct AvlNode_ {
    void* data;
    int height;
    struct AvlNode_* left;
    struct AvlNode_* right;
} AvlNode;


typedef struct AvlTree_ {
    AvlNode* root;
    size_t size;
} AvlTree;


/**
 * Inicia os valores da AvlTree.
*/
void avl_tree_init(AvlTree* avl) {
    avl->root = NULL;
    avl->size = 0;
}


/**
 * Aloca espaço em memória para uma nova AvlTree.
 * @return Uma AvlTree vazia.
*/
AvlTree* avl_tree_create() {
    AvlTree* avl = (AvlTree*) malloc(sizeof(AvlTree));
    avl_tree_init(avl);
    return avl;
}


/**
 * Aloca espaço em memória para um novo AvlNode.
 * @return
 * Uma AvlNode vazio
*/
AvlNode* avl_tree_create_node(void* data) {
    AvlNode* node = (AvlNode*) malloc(sizeof(AvlNode));
    node->data = data;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}


/**
 * Desaloca a memória utilizada pelo AvlNode
 * porem não desaloca a memória do item dentro
 * do nodo.
*/
void avl_tree_destroy_node(AvlNode* node) {
    if (node != NULL) {
        avl_tree_destroy_node(node->left);
        avl_tree_destroy_node(node->right);
        free(node);
        node = NULL;
    }
}


/**
 * Limpa os itens da AvlTree porem não desaloca 
 * a memória HEAP que os itens possam estar utilizando.
*/
void avl_tree_clear(AvlTree* avl) {
    avl_tree_destroy_node(avl->root);
    avl->root = NULL;
    avl->size = 0;   
}


/** 
 * Desaloca a memória utilizada pela AvlTree pordem não pelos 
 * itens armazenados nela.
*/
void avl_tree_destroy(AvlTree* avl) {
    avl_tree_destroy_node(avl->root);
    free(avl);
    avl = NULL;
}


/**
 * @return Retorna a altura de um AvlNode.
*/
int avl_tree_height(AvlNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}


/**
 * @return
 * Retorna o valor máximo entre dois inteiro a e b.
*/
int avl_tree_max(int a, int b) {
    return a > b ? a : b;
}


/**
 * Executa uma rotação simples para a direita.
*/
AvlNode* avl_tree_right_rotate(AvlNode* node) {
    AvlNode* leftNode = node->left;
    AvlNode* rightNode = leftNode->right;
    
    leftNode->right = node;
    node->left = rightNode;
    
    node->height = avl_tree_max(avl_tree_height(node->left), avl_tree_height(node->right)) + 1;
    leftNode->height = avl_tree_max(avl_tree_height(leftNode->left), avl_tree_height(leftNode->right)) + 1;
    
    return leftNode;
}

/**
 * Executa uma rotação simples para a esquerda.
*/
AvlNode* avl_tree_left_rotate(AvlNode* node) {
    AvlNode *rightNode = node->right;
    AvlNode *leftNode = rightNode->left;
    
    rightNode->left = node;
    node->right = leftNode;
    
    node->height = avl_tree_max(avl_tree_height(node->left), avl_tree_height(node->right)) + 1;
    rightNode->height = avl_tree_max(avl_tree_height(rightNode->left), avl_tree_height(rightNode->right)) + 1;
    
    return rightNode;
}


/**
 * Retorna o fator de balanceamento de um AvlNode
*/
int avl_tree_get_balance(AvlNode* node) {
    if (node == NULL) {
        return 0;
    }
    return avl_tree_height(node->left) - avl_tree_height(node->right);
}


/**
 * Insere um nodo na AvlTree
*/
AvlNode* avl_tree_insert_aux(AvlNode* node, void* data, size_t* avl_tree_size) {
    if (node == NULL) {
        *avl_tree_size += 1;
        return avl_tree_create_node(data);        
    }

    if (data < node->data) {
        node->left = avl_tree_insert_aux(node->left, data, avl_tree_size);
    } else if (data > node->data)
        node->right = avl_tree_insert_aux(node->right, data, avl_tree_size);
    else  {
        return node;
    }
    
    node->height = 1 + avl_tree_max(avl_tree_height(node->left), avl_tree_height(node->right));
    
    int balance = avl_tree_get_balance(node);
    
    // Left Left Case
    if (balance > 1 && data < node->left->data) {
        return avl_tree_right_rotate(node);
    }

    // Right Right Case
    if (balance < -1 && data > node->right->data) {
        return avl_tree_left_rotate(node);
    }

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = avl_tree_left_rotate(node->left);
        return avl_tree_right_rotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = avl_tree_right_rotate(node->right);
        return avl_tree_left_rotate(node);
    }
    
    return node;
}


/**
 * Insere um nodo na AvlTree e atualiza o nodo raiz da arvore.
*/
void avl_tree_insert(AvlTree* avl, void* data) {
    avl->root = avl_tree_insert_aux(avl->root, data, &avl->size);    
}


/**
 * @return Retorna o nodo mais a esquerda do nodo passado
 * como argumento da função.
*/
AvlNode* avl_tree_min(AvlNode* node) {
    if (node == NULL) {
        return node;
    }    
    while (node->left != NULL) {
        node = node->left;
    }  
    return node;
}


/**
 * Remove um nodo da AvlTree.
*/
AvlNode* avl_tree_remove_aux(AvlNode* node, void* data, size_t* avl_tree_size) {
    if (node == NULL) {
        return node;
    }
    
    if (data < node->data) {
        node->left = avl_tree_remove_aux(node->left, data, avl_tree_size);
    } else if (data > node->data) {
        node->right = avl_tree_remove_aux(node->right, data, avl_tree_size);
    } else {
        if ((node->left == NULL) || (node->right == NULL)) {
            AvlNode* temp = node->left ? node->left : node->right;  
            // No child case
            if (temp == NULL) {
                temp = node;
                node = NULL;
            } else {
                *node = *temp; // Copy the contents of the non-empty child
            }
            *avl_tree_size -= 1;
            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            AvlNode* temp = avl_tree_min(node->right);
  
            // Copy the inorder successor's data to this node
            node->data = temp->data;
  
            // Delete the inorder successor
            node->right = avl_tree_remove_aux(node->right, temp->data, avl_tree_size);
        }
    }
  
    // If the tree had only one node then return
    if (node == NULL) {
        return node;
    }
  
    // Update height of the current node
    node->height = 1 + avl_tree_max(avl_tree_height(node->left), avl_tree_height(node->right));
  
    // Get the balance factor of this node to check whether this node became unbalanced
    int balance = avl_tree_get_balance(node);
  
    // If this node becomes unbalanced, there are four cases
  
    // Left Left Case
    if (balance > 1 && avl_tree_get_balance(node->left) >= 0)
        return avl_tree_right_rotate(node);
  
    // Left Right Case
    if (balance > 1 && avl_tree_get_balance(node->left) < 0) {
        node->left = avl_tree_left_rotate(node->left);
        return avl_tree_right_rotate(node);
    }
  
    // Right Right Case
    if (balance < -1 && avl_tree_get_balance(node->right) <= 0)
        return avl_tree_left_rotate(node);
  
    // Right Left Case
    if (balance < -1 && avl_tree_get_balance(node->right) > 0) {
        node->right = avl_tree_right_rotate(node->right);
        return avl_tree_left_rotate(node);
    }
  
    return node;
}

/**
 * Remove um nodo da AvlTree e atualiza o nodo raiz da arvore.
*/
void avl_tree_remove(AvlTree* avl, void* data) {
    avl->root = avl_tree_remove_aux(avl->root, data, &avl->size);
}

/**
 * @return 1 caso contenha o dado passado no argumento da função ou 0
 * caso contrário.
*/
int avl_tree_contains(AvlTree* avl, void* data) {
    AvlNode* node = avl->root;
    while (node != NULL) {
        if (data == node->data) {
            return 1;
        }
        node = (data < node->data) ? node->left : node->right;
    }
    return 0;
}


#endif