#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

int Height(Node *node) {
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

int Balanced(Node *node) {
  if (node == NULL)
    return 0;
  return Height(node->right) - Height(node->left);
}

Node *right_rotate(Node *t, int *flag) {
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

Node *left_rotate(Node *t, int *flag) {
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

void is_avl_rec(Node *root, bool *flag) {
  if (root == NULL)
    return;
  is_avl_rec(root->left, flag);
  is_avl_rec(root->right, flag);
  int vertice = Balanced(root);
  if (vertice < -1 && vertice > 1) {
    *flag = false;
    return;
  }
}

bool is_avl(Avl *tree) {
  bool status = true;
  is_avl_rec(tree->root, &status);
  return status;
}

void size_avl_rec(Node *root, int *size) {
  if (root == NULL)
    return;
  *size += 1;
  size_avl_rec(root->left, size);
  size_avl_rec(root->right, size);
}

int size_avl(Avl *tree) {
  int count = 0;
  size_avl_rec(tree->root, &count);
  return count;
}

void pre_order(Node *root) {
  if (root == NULL)
    return;
  printf("Key => %d, Bal => %d\n", root->key, root->balancing);
  pre_order(root->left);
  pre_order(root->right);
}

void in_order(Node *root) {
  if (root == NULL)
    return;
  in_order(root->left);
  printf("Key => %d, Bal => %d\n", root->key, root->balancing);
  in_order(root->right);
}

void post_order(Node *root) {
  if (root == NULL)
    return;
  post_order(root->left);
  post_order(root->right);
  printf("Key => %d, Bal => %d\n", root->key, root->balancing);
}

void clear_nodes_rec(Node *root) {
  if (root == NULL)
    return;
  clear_nodes_rec(root->left);
  clear_nodes_rec(root->right);
  free(root);
}

void clear_nodes(Node **root) {
  clear_nodes_rec(*root);
  *root = NULL;
}

Node *create_node(int key) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->key = key;
  node->left = node->right = NULL;
  node->balancing = 0;
  return node;
}

Avl *create_avl() {
  Avl *avl = (Avl *)malloc(sizeof(Avl));
  avl->root = NULL;
  return avl;
}

Node *insert_avl_rec(Node *root, int key, int *flag) {
  if (root == NULL) {
    root = create_node(key);
    *flag = 1;
  } else {
    if (key < root->key) {
      root->left = insert_avl_rec(root->left, key, flag);
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
          root = right_rotate(root, flag);
          break;
        }
      }
    } else if (key > root->key) {
      root->right = insert_avl_rec(root->right, key, flag);
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
          root = left_rotate(root, flag);
          break;
        }
      }
    } else {
      printf("Elemento já existe!\n");
    }
  }
  return root;
}

void Insert(Avl *tree, int key) {
  int flag = 1;
  tree->root = insert_avl_rec(tree->root, key, &flag);
}

Node *right_rotate_delete(Node *t, int *flag) {
  Node *u, *v;
  u = t->left;
  if (u->balancing <= 0) {
    t->left = u->right;
    u->right = t;
    t = u;
    if (u->balancing == -1) {
      u->balancing = t->right->balancing = 0;
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
    case 0:
      u->balancing = 0;
      t->right->balancing = 0;
      break;
    case -1:
      u->balancing = 0;
      t->right->balancing = 1;
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

Node *left_rotate_delete(Node *t, int *flag) {
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
    case 0:
      u->balancing = 0;
      t->left->balancing = 0;
      break;
    case -1:
      u->balancing = 0;
      t->left->balancing = -1;
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

Node *left_balancing(Node *t, int *flag) {
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
      t = left_rotate_delete(t, flag);
      break;
    }
  }
  return t;
}

Node *right_balancing(Node *t, int *flag) {
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
      t = right_rotate_delete(t, flag);
      break;
    }
  }
  return t;
}

void swap(Node *p, Node *q) {
  Node *temp;
  temp->balancing = p->balancing;
  temp->key = p->key;
  temp->right = p->right;
  temp->left = p->right;
  p->balancing = q->balancing;
  p->key = q->key;
  p->right = q->right;
  p->left = q->left;
  q->balancing = temp->balancing;
  q->key = temp->key;
  q->right = temp->right;
  q->left = temp->left;
}

Node *delete_avl_rec(Node *root, int key, int *flag) {
  if (root == NULL) {
    printf("Elemento não encontrado!\n");
    *flag = 0;
  } else {
    if (key < root->key) {
      root->left = delete_avl_rec(root->left, key, flag);
      root = left_balancing(root, flag);
    } else {
      if (key > root->key) {
        root->right = delete_avl_rec(root->right, key, flag);
        root = right_balancing(root, flag);
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
              root = delete_avl_rec(root->right, key, flag);
            }
            root = right_balancing(root, flag);
          }
        }
      }
    }
  }
  return root;
}

void Delete(Avl *tree, int key) {
  int flag = 1;
  tree->root = delete_avl_rec(tree->root, key, &flag);
}
