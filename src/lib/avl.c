#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

int max(int k, int t) {
  if (t > k)
    return t;
  return k;
}

int Height(Node* node) {
  if (node == NULL) 
    return 0;
  return node->balancing;
}

int Balanced(Node* node) {
  if (node == NULL) 
    return 0;
  return Height(node->right) - Height(node->left);
}

Node *RightRotate(Node *t, int *flag) {
  Node *u, *v;
  u = t->left;
  if (u->balancing == -1) {
    t->left = u->right;
    u->right = t;
    t = u;
    t->right->balancing = 0;
  } else {
    v = u->right;
    u->right = v->left;
    v->left = u;
    t->left = v->right;
    v->right = t;

    if (v->balancing == -1) {
      t->balancing = 1;
      u->balancing = 0;
    } else if (v->balancing == 1) {
      t->balancing = 0;
      u->balancing = -1;
    } else {
      t->balancing = 0;
      u->balancing = 0;
    }
    t = v;
  }
  t->balancing = 0;
  *flag = 0;
  return t;
}

Node* LeftRotate(Node* t, int* flag) {
  Node* u, *v;
  u = t->right;
  if (u->balancing == 1) {
    t->right = u->left;
    u->left = t;
    t = u;
    t->left->balancing = 0;
  } else {
    v = u->left;
    u->left = v->right;
    v->right = u;
    t->right = v->left;
    v->left = t;

    if (v->balancing == 1) {
      t->balancing = -1;
      u->balancing = 0;
    } else if (v->balancing == -1) {
      t->balancing = 0;
      u->balancing = 1;
    } else {
      t->balancing = 0;
      u->balancing = 0;
    }
    t = v;
  }
  t->balancing = 0;
  *flag = 0;
  return t;
}

Node* CreateNode(int key) {
  Node* node = (Node *) malloc(sizeof(Node));
  node->key = key;
  node->left = node->right = NULL;
  node->balancing = 0;
  return node;
}

Avl* CreateAvl() {
  Avl* avl = (Avl*) malloc(sizeof(Avl));
  avl->length = 0;
  avl->root = NULL;
  return avl;
}

Node *insertAvlRec(Node *root, int key, int *flag) {
  if (root == NULL) {
    root = CreateNode(key);
  } else {
    if (key < root->key) {
      root->left = insertAvlRec(root->left, key, flag);
      if (*flag) {
        switch (root->balancing) {
        case 1:
          root->balancing = 0;
          *flag = 0;
          break;
        case 0:
          root->balancing = -1;
          break;
        case -1:
          root = RightRotate(root, flag);
          break;
        }
      }
    } else if (key > root->key) {
      root->right = insertAvlRec(root->right, key, flag);
      if (*flag == 1) {
        switch (root->balancing) {
        case -1:
          root->balancing = 0;
          *flag = 0;
          break;
        case 0:
          root->balancing = 1;
          break;
        case 1:
          root = LeftRotate(root, flag);
          break;
        }
      }
    } else {
      printf("Elemento já existe!\n");
    }
  }
  return root;
}

void Insert(Avl* tree, int key) {
  int flag = 1;
  tree->root = insertAvlRec(tree->root, key, &flag);
}

void PreOrder(Node* root) {
  if (root == NULL)
    return;
  printf(" %d ", root->key);
  PreOrder(root->left);
  PreOrder(root->right);
}

void InOrder(Node* root) {
  if (root == NULL)
    return;
  InOrder(root->left);
  printf(" %d ", root->key);
  InOrder(root->right);
}

void PostOrder(Node* root) {
  if (root == NULL)
    return;
  PostOrder(root->left);
  PostOrder(root->right);
  printf(" %d ", root->key);
}

void isAvlRec(Node* root, bool* flag) {
  if (root == NULL)
    return;
  isAvlRec(root->left, flag);
  isAvlRec(root->right, flag);
  int vertice = Balanced(root);
  if (vertice < -1 && vertice > 1) {
    *flag = false;
    return;
  }
}

bool IsAVL(Avl* tree) {
  bool status = true;
  isAvlRec(tree->root, &status);
  return status;
}

void sizeAvlRec(Node* root, int* size) {
  if (root == NULL)
    return ;
  *size += 1;
  sizeAvlRec(root->left, size);
  sizeAvlRec(root->right, size);
}

int SizeAvl(Avl* tree) {
  int count = 0;
  sizeAvlRec(tree->root, &count);
  return count;
}
