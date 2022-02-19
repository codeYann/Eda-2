#include "stdbool.h"
#ifndef AVL
#define AVL

typedef struct node {
  struct node *left;
  struct node *right;
  int key;
  int balancing;
} Node;

typedef struct {
  Node *root;
} Avl;

Node *create_node(int key);
Avl *create_avl();
void Insert(Avl *tree, int key);
void Delete(Avl *tree, int key);

void pre_order(Node *root);
void in_order(Node *root);
void post_order(Node *root);

bool is_avl(Avl *tree);
int size_avl(Avl *tree);
void clear_nodes(Node **root);

#endif
