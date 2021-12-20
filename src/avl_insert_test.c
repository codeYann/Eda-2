#include <stdio.h>
#include "./lib/avl.h"

int list1[] = {10, 4, 89, 12, 3, 7, 20, 30, 40, 17, 9, 1, 15, 8};
int list2[] = {18, 16, 14, 12, 10, 1, 22, 24, 26, 30, 32};
int list3[] = {24, 89, 1, 11, 0, 169, 2871, 12, 144, 121, 7, 15};


void TestInsertAvl(Avl *tree, int *list, int n) 
{
  for (int i = 0; i < n; i++) {
    Insert(tree, list[i]);
  }
  InOrder(tree->root);
  printf("Árvore é uma avl? => %d\n", IsAVL(tree));
  printf("Quantidade de nós => %d\n\n", SizeAvl(tree));
}

int main(int argc, char **argv)
{
  Avl *a = CreateAvl();
  Avl *b = CreateAvl();
  Avl *c = CreateAvl();

  TestInsertAvl(a, list1, 14);
  TestInsertAvl(b, list2, 11);
  TestInsertAvl(c, list3, 12);
  return 0;
}
