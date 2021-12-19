#include <stdio.h>
#include "./lib/avl.h"

int height(Node *node)
{
  if (node == NULL) 
    return 0;
  else {
    int left = height(node->left);
    int right = height(node->right);
    if (left > right) {
      return left + 1;
    } else {  
      return right + 1;
    }
  }
}

void TestInsertAvl(Avl *tree, int *list, int n) 
{
  for (int i = 0; i < n; i++) {
    Insert(tree, list[i]);
  }

  printf("Árvore é uma avl? => %d\n", IsAVL(tree));
  printf("Quantidade de nós => %d\n", SizeAvl(tree));
  InOrder(tree->root);
}

int main(int argc, char **argv)
{
  Avl *a = CreateAvl();

  int list[] = {10, 4, 89, 12, 3, 7, 20, 30, 40, 17, 9, 1, 15, 8};
  int list2[] = {18, 16, 14, 12, 10, 1, 22, 24, 26, 30, 32};
  int list3[] = {24, 89, 1, 11, 0, 169, 2871, 12, 144, 121, 7, 15};

  TestInsertAvl(a, list3, 12);
  printf("%d\n", height(a->root));
  return 0;
}
