#include "stdbool.h"
#ifndef AVL
#define AVL

typedef struct node
{
  struct node *left;
  struct node *right;
  int key;
  int balancing;
} Node;

typedef struct
{
  Node *root;
  int length;
} Avl;

Node *CreateNode(int key);
Avl *CreateAvl();
void Insert(Avl *tree, int key);
void Delete(Avl *tree, int key);

void PreOrder(Node *root);
void InOrder(Node *root);
void PostOrder(Node *root);

bool IsAVL(Avl *tree);
int SizeAvl(Avl *tree);
void ClearNodes(Node **root);

#endif
