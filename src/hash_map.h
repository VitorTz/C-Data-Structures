#ifndef C_DATA_STRUCTURE_HASH_MAP_H
#define C_DATA_STRUCTURE_HASH_MAP_H
#include <stdlib.h>


typedef struct HashMapNode_ {
    int key;
    void* data;
    int height;
    struct HashMapNode_* left;
    struct HashMapNode_* right;
} HashMapNode;


typedef struct AvlTree_ {
    HashMapNode* root;
} AvlTree;


typedef struct HashMap_ {
    AvlTree* buckets;
    size_t size;
    size_t num_buckets;
} HashMap;


//////////////////////////////////////////////////////////////
///////////////////// HASH MAP NODE //////////////////////////
//////////////////////////////////////////////////////////////


HashMapNode* hash_map_node_create(const int key, void* data) {
    HashMapNode* node = malloc(sizeof(HashMapNode));
    node->key = key;
    node->data = data;
    node->left = node->right = NULL;
    node->height = 0;
    return node;
}


void hash_map_node_destroy(HashMapNode* root) {
    free(root);
    root = NULL; 
}


void hash_map_node_destroy_recursive(HashMapNode* root) {
    if (root != NULL) {
        hash_map_node_destroy_recursive(root->left);
        hash_map_node_destroy_recursive(root->right);
        free(root);
        root = NULL;
    }
}


HashMapNode* hash_map_node_clear(HashMapNode* root) {
    hash_map_node_destroy_recursive(root);
    return NULL;
}


HashMapNode* hash_map_node_rotate_left(HashMapNode* root) {
    HashMapNode *rightNode = root->right;
    HashMapNode *leftNode = rightNode->left;
    
    rightNode->left = root;
    root->right = leftNode;
    
    root->height = 1 + hash_map_node_max(
        hash_map_node_height(root->left), 
        hash_map_node_height(root->right)
    );
    rightNode->height = 1 + hash_map_node_max(
        hash_map_node_height(rightNode->left), 
        hash_map_node_height(rightNode->right)
    );
    
    return rightNode;
}


HashMapNode* hash_map_node_rotate_right(HashMapNode* root) {
    HashMapNode* leftNode = root->left;
    HashMapNode* rightNode = root->right;
    
    leftNode->right = root;
    root->left = rightNode;

    root->height = 1 + hash_map_node_max(
        hash_map_node_height(root->left),
        hash_map_node_height(root->right)
    );

    leftNode->height = 1 + hash_map_node_max(
        hash_map_node_height(leftNode->left), 
        hash_map_node_height(leftNode->right)
    );

    return leftNode;
}


int hash_map_node_height(HashMapNode* root) {
    if (root == NULL) {
        return 0;
    }
    return root->height;
}


/**
 * @return Retorna o fator de balanço do HashMapNode
*/
int hash_map_node_get_balance(HashMapNode* root) {
    if (root == NULL) {
        return 0;
    }
    return hash_map_node_height(root->left) - hash_map_node_height(root->right);
}


int hash_map_node_max(const int a, const int b) {
    return a > b ? a : b;
}


HashMapNode* hash_map_node_min(HashMapNode* root) {
    if (root == NULL) {
        return root;
    }    
    while (root->left != NULL) {
        root = root->left;
    }  
    return root;
}


HashMapNode* hash_map_node_insert(HashMapNode* root, const int key, void* data, size_t* avl_size) {
    if (root == NULL) {
        *avl_size += 1;
        return hash_map_node_create(key, data);
    }

    if (key < root->key) {
        root->left = hash_map_node_insert(root->left, key, data, avl_size);
    } else if (key > root->key)
        root->right = hash_map_node_insert(root->left, key, data, avl_size);
    else  {
        return root;
    }
    
    root->height = 1 + hash_map_node_max(
        hash_map_node_height(root->left), 
        hash_map_node_height(root->right)
    );
    
    int balance = hash_map_node_get_balance(root);
    

    // Left Left Case
    if (balance > 1 && key < root->left->key) {
        return hash_map_node_rotate_right(root);
    }

    // Right Right Case
    if (balance < -1 && key > root->right->key) {
        return hash_map_node_rotate_left(root);
    }

    // Left Right Case
    if (balance > 1 && key > root->left->key) {
        root->left = hash_map_node_rotate_left(root->left);
        return hash_map_node_rotate_right(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->key) {
        root->right = hash_map_node_rotate_right(root->right);
        return hash_map_node_rotate_left(root);
    }
    
    return root; 
}


HashMapNode* hash_map_node_erase(HashMapNode* root, const int key, size_t* avl_tree_size) {
    if (root == NULL) {
        return root;
    }
    
    if (key < root->key) {
        root->left = hash_map_node_erase(root->left, key, avl_tree_size);
    } else if (key > root->key) {
        root->right = hash_map_node_erase(root->right, key, avl_tree_size);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            HashMapNode* temp = root->left ? root->left : root->right;  
            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp; // Copy the contents of the non-empty child
            }
            *avl_tree_size -= 1;
            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            HashMapNode* temp = hash_map_node_min(root->right);
  
            // Copy the inorder successor's data to this root
            root->data = temp->data;
  
            // Delete the inorder successor
            root->right = hash_map_node_erase(root->right, temp->key, avl_tree_size);
        }
    }
  
    // If the tree had only one root then return
    if (root == NULL) {
        return root;
    }
  
    // Update height of the current root
    root->height = 1 + hash_map_node_max(
        hash_map_node_height(root->left), 
        hash_map_node_height(root->right)
    );
  
    // Get the balance factor of this root to check whether this root became unbalanced
    int balance = hash_map_node_get_balance(root);
  
    // If this root becomes unbalanced, there are four cases
  
    // Left Left Case
    if (balance > 1 && hash_map_node_get_balance(root->left) >= 0)
        return hash_map_node_rotate_right(root);
  
    // Left Right Case
    if (balance > 1 && hash_map_node_get_balance(root->left) < 0) {
        root->left = hash_map_node_rotate_left(root->left);
        return hash_map_node_rotate_right(root);
    }
  
    // Right Right Case
    if (balance < -1 && hash_map_node_get_balance(root->right) <= 0)
        return hash_map_node_rotate_left(root);
  
    // Right Left Case
    if (balance < -1 && hash_map_node_get_balance(root->right) > 0) {
        root->right = hash_map_node_rotate_right(root->right);
        return hash_map_node_rotate_left(root);
    }
  
    return root;
}


void* hash_map_node_at(HashMapNode* root, const int key) {
    while (root != NULL) {
        if (root->key == key) {
            return root->data;
        }
        if (root->key < key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return NULL;
}


int hash_map_node_contains(HashMapNode* root, const int key) {
    while (root != NULL) {
        if (root->key == key) {
            return 1;
        }
        if (root->key < key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return 0;
}


//////////////////////////////////////////////////////////////
////////////////////////// HASH MAP //////////////////////////
//////////////////////////////////////////////////////////////


HashMap* hash_map_create(const size_t num_buckets) {
    HashMap* map = malloc(sizeof(HashMap));
    map->size = 0;
    map->num_buckets = num_buckets;
    map->buckets = malloc(sizeof(AvlTree) * num_buckets);
    for (int i = 0; i < num_buckets; i++) {
        AvlTree* bucket = map->buckets + i;
        bucket->root = NULL; 
    }
    return map;
}


void hash_map_destroy(HashMap* m) {
    for (int i = 0; i < m->num_buckets; i++) {
        AvlTree* bucket = m->buckets + i;
        hash_map_node_destroy_recursive(bucket->root);
        bucket->root = NULL;
    }
    free(m->buckets);
    m->buckets = NULL;
    free(m);
    m = NULL;
}


void hash_map_clear(HashMap* m) {
    for (int i = 0; i < m->num_buckets; i++) {
        AvlTree* bucket = m->buckets + i;
        hash_map_node_destroy_recursive(bucket->root);
        bucket->root = NULL;        
    }
}


void hash_map_insert(HashMap* m, const int key, void* value) {
    const int hash = hash_map_hash(m, key);
    AvlTree* bucket = m->buckets + hash;
    bucket->root = hash_map_node_insert(bucket->root, key, value, &m->size);
}


void hash_map_erase(HashMap* m, const int key) {
    const int hash = hash_map_hash(m, key);
    AvlTree* bucket = m->buckets + hash;
    bucket->root = hash_map_node_erase(bucket->root, key, &m->size);
}


int hash_map_hash(HashMap* m, const int key) {
    return key % m->num_buckets;
}


int hash_map_hash_char(HashMap* m, const char* key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return hash_map_hash(m, sum);
}


int hash_map_contains(HashMap* m, const int key) {
    const int hash = hash_map_hash(m, key);
    AvlTree* bucket = m->buckets + hash;
    return hash_map_node_contains(bucket->root, key);
}


void* hash_map_at(HashMap* m, const int key) {
    const int hash = hash_map_hash(m, key);
    AvlTree* bucket = m->buckets + hash;
    return hash_map_node_at(bucket->root, key);
}


#endif