#include "avl_tree.h"
#include "util.h"


void test_avl_in_order(AvlNode* node) {
    if (node != NULL) {
        test_avl_in_order(node->left);
        printf("%d\n", *((int*) node->data));
        test_avl_in_order(node->right);
    }
}


void test_avl_tree_insert() {
    const int total = 10;
    AvlTree* avl = avl_tree_create();
    int* nums = malloc_int(total);
    for (int i = 0; i < total; i++) {
        avl_tree_insert(avl, nums + 1);
    }
    test_avl_in_order(avl->root);
    avl_tree_destroy(avl);
    free(nums);
}