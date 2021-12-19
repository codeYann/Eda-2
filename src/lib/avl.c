#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

int max(int k, int t)
{
  if (t > k)
    return t;
  return k;
}

int Height(Node *node)
{
  if (node == NULL) 
    return 0;
  else {
    int left = Height(node->left);
    int right = Height(node->right);
    if (left > right) {
      return left + 1;
    } else {  
      return right + 1;
    }
  }
}

int Balanced(Node *node)
{
  if (node == NULL)
    return 0;
  return Height(node->right) - Height(node->left);
}

Node *RightRotate(Node *t, int *flag)
{
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

    if (v->balancing == 1) {
      t->balancing = 1;
      u->balancing = 0;
    } else if (v->balancing == -1) {
      t->balancing = 1;
      u->balancing = 0;
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

Node *LeftRotate(Node *t, int *flag)
{
  Node *u, *v;
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

void isAvlRec(Node *root, bool *flag) 
{
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

bool IsAVL(Avl *tree)
{
  bool status = true;
  isAvlRec(tree->root, &status);
  return status;
}

void sizeAvlRec(Node *root, int *size)
{
  if (root == NULL)
    return;
  *size += 1;
  sizeAvlRec(root->left, size);
  sizeAvlRec(root->right, size);
}

int SizeAvl(Avl *tree)
{
  int count = 0;
  sizeAvlRec(tree->root, &count);
  return count;
}

void PreOrder(Node *root)
{
  if (root == NULL)
    return;
  printf(" %d ", root->key);
  PreOrder(root->left);
  PreOrder(root->right);
}

void InOrder(Node *root)
{
  if (root == NULL)
    return;
  InOrder(root->left);
  printf("Key => %d, Bal => %d\n", root->key, root->balancing);
  InOrder(root->right);
}

void PostOrder(Node *root)
{
  if (root == NULL)
    return;
  PostOrder(root->left);
  PostOrder(root->right);
  printf(" %d ", root->key);
}

void clearNodesRec(Node* root) 
{
  if (root == NULL) 
    return;
  clearNodesRec(root->left);
  clearNodesRec(root->right);
  free(root);
}

void ClearNodes(Node **root) 
{
  clearNodesRec(*root);
  *root = NULL;
}

Node *CreateNode(int key)
{
  Node *node = (Node *)malloc(sizeof(Node));
  node->key = key;
  node->left = node->right = NULL;
  node->balancing = 0;
  return node;
}

Avl *CreateAvl()
{
  Avl *avl = (Avl *)malloc(sizeof(Avl));
  avl->length = 0;
  avl->root = NULL;
  return avl;
}

Node *insertAvlRec(Node *root, int key, int *flag)
{
  if (root == NULL) {
    root = CreateNode(key);
    *flag = 1;
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
      if (*flag == 1){
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

void Insert(Avl *tree, int key)
{
  int flag = 1;
  tree->root = insertAvlRec(tree->root, key, &flag);
}

Node *RightRotateDelete(Node *t, int *flag)
{
  Node *u, *v;
  u = t->left;
  if (u->balancing <= 0) {
    t->left = u->right;
    u->right = t;
    t = u;
    if (u->balancing == -1) {
      u->balancing = 0;
      t->balancing = 0;
      *flag = 1;
    } else {
      u->balancing = 1;
      t->right->balancing = -1;
      *flag = 0;
    }
  } else {
    v = u->right;
    u->right = v->left;
    v->left = u;
    t->left = v->right;
    v->right = t;
    t = v;

    switch (v->balancing) {
    case -1:
      u->balancing = 0;
      t->right->balancing = 1;
      break;
    case 0:
      u->balancing = 0;
      t->right->balancing = 0;
      break;
    case 1:
      u->balancing = -1;
      t->right->balancing = 0;
      break;
    }
    t->balancing = 0;
    *flag = 1;
  }
  return t;
}

Node *LeftRotateDelete(Node *t, int *flag)
{
  Node *u, *v;
  u = t->right;
  if (u->balancing >= 0) {
    t->right = u->left;
    u->left = t;
    t = u;
    if (u->balancing == 1) {
      u->balancing = 0;
      t->balancing = 0;
      *flag = 1;
    } else {
      u->balancing = -1;
      t->left->balancing = 1;
      *flag = 0;
    }
  } else {
    v = u->left;
    u->left = v->right;
    v->right = u;
    t->right = v->left;
    v->left = t;
    t = v;

    switch (v->balancing) {
    case -1:
      u->balancing = 0;
      t->left->balancing = -1;
      break;
    case 0:
      u->balancing = 0;
      t->left->balancing = 0;
      break;
    case 1:
      u->balancing = 1;
      t->left->balancing = 0;
      break;
    }
    t->balancing = 0;
    *flag = 1;
  }
  return t;
}

Node *LeftBalancing(Node *t, int *flag)
{
  if (*flag == 1) {
    switch (t->balancing) {
    case -1:
      t->balancing = 0;
      break;
    case 0:
      t->balancing = 1;
      *flag = 0;
      break;
    case 1:
      t = LeftRotateDelete(t, flag);
      break;
    }
  }
  return t;
}

Node *RightBalancing(Node *t, int *flag)
{
  if (*flag == 1) {
    switch (t->balancing) {
    case 1:
      t->balancing = 0;
      break;
    case 0:
      t->balancing = -1;
      *flag = 0;
      break;
    case -1:
      t = RightRotateDelete(t, flag);
      break;
    }
  }
  return t;
}

void swap(Node *p, Node *q);

Node *deleteAvlRec(Node *root, int key, int *flag)
{
  if (root == NULL) {
    printf("Elemento não encontrado!\n");
    *flag = 0;
  } else {
    if (key < root->key) {
      root->left = deleteAvlRec(root->left, key, flag);
      root = LeftBalancing(root, flag);
    } else {
      if (key > root->key) {
        root->right = deleteAvlRec(root->right, key, flag);
        root = RightBalancing(root, flag);
      } else {
        Node *aux = root;
        if (root->left == NULL) {
          root = root->right;
          *flag = 1;
        } else {
          if (root->right == NULL) {
            root = root->left;
            *flag = 1;
          } else {
            Node *s = root->right;
            if (s->left != NULL) {
              s->left = root->left;
              s->balancing = root->balancing;
              root = s;
              *flag = 1;
            } else {
              Node *pai;
              while (s->left != NULL) {
                pai = s;
                s = s->left;
              }
              swap(root, pai->left);
              root = deleteAvlRec(root->right, key, flag);
            }
            root = RightBalancing(root->right, flag);
          }
        }
      }
    }
  }
  return root;
}

void Delete(Avl *tree, int key)
{
  int flag = 1;
  tree->root = deleteAvlRec(tree->root, key, &flag);
}
