#include <stdio.h>
#include "./lib/avl.h"

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

  int list[] = {10, 4, 89, 12, 3, 7, 20, 30, 40, 17, 9, 1, 15, 8};
  int list2[] = {18, 16, 14, 12, 10, 1, 22, 24, 26, 30, 32};
  int list3[] = {24, 89, 1, 11, 0, 169, 2871, 12, 144, 121, 7, 15};

  TestInsertAvl(a, list3, 12);
  
  printf("Removendo 12 e 7\n");
  Delete(a, 12);
  Delete(a, 7);
  // Delete(a, 11); Erro ao deleter um nó com 2 filhos.

  printf("\n");
  InOrder(a->root);
  printf("Árvore é uma avl? => %d\n", IsAVL(a));
  printf("Quantidade de nós => %d\n", SizeAvl(a));

  return 0;
}
