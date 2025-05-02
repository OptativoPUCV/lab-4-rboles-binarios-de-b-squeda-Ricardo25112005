#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * map = (TreeMap *)malloc(sizeof(TreeMap));
    if (map == NULL) return NULL;
    map->root = NULL;
    map->current = NULL;
    map->lower_than = lower_than;
    return map; 
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if (tree == NULL) return;
    if (searchTreeMap(tree, key) != NULL) return;
    TreeNode * new = createTreeNode(key, value);
    if (new == NULL) return;
    if (tree->root == NULL) {
        tree->root = new;
        tree->current = new;
        return;
    }
    TreeNode * parent = NULL;
    TreeNode * current = tree->root;
    while (current != NULL) {
        parent = current;
        if (tree->lower_than(key, current->pair->key)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    new->parent = parent;
    if (tree->lower_than(key, parent->pair->key)) {
        parent->left = new;
    } else {
        parent->right = new;
    }
    tree->current = new;
}

TreeNode * minimum(TreeNode * x){
    if (x == NULL) return NULL;
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    if (node == NULL) return;
    if (node->left == NULL && node->right == NULL) {
        if (node->parent != NULL) {
            if (node->parent->left == node) {
                node->parent->left = NULL;
            } else {
                node->parent->right = NULL;
            }
        } else {
            tree->root = NULL;
        }
        free(node->pair);
        free(node);
        return;
    }
    if (node->left == NULL || node->right == NULL) {
        TreeNode * child = (node->left != NULL) ? node->left : node->right;
        if (node->parent != NULL) {
            if (node->parent->left == node) {
                node->parent->left = child;
            } else {
                node->parent->right = child;
            }
        } else {
            tree->root = child;
        }
        child->parent = node->parent;
        free(node->pair);
        free(node);
        return;
    }
    TreeNode * minNode = minimum(node->right);
    node->pair->key = minNode->pair->key;
    node->pair->value = minNode->pair->value;
    removeNode(tree, minNode);
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL; 
    TreeNode * actual = tree->root;
    while (actual != NULL) {
        if (is_equal(tree, key, actual->pair->key)) {
            tree->current = actual;
            return actual->pair;
        } else if (tree->lower_than(key, actual->pair->key)) {
            actual = actual->left;
        } else {
            actual = actual->right;
        }
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
