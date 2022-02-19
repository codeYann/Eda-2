#include "./lib/avl.h"
#include <stdio.h>

void test_insert_avl(Avl *tree, int *list, int n) {
  for (int i = 0; i < n; i++) {
    Insert(tree, list[i]);
  }

  in_order(tree->root);
  printf("Árvore é uma avl? => %d\n", is_avl(tree));
  printf("Quantidade de nós => %d\n\n", size_avl(tree));
}

int main(int argc, char **argv) {
  Avl *a = create_avl();

  int list[] = {10, 4, 89, 12, 3, 7, 20, 30, 40, 17, 9, 1, 15, 8};
  int list2[] = {18, 16, 14, 12, 10, 1, 22, 24, 26, 30, 32};
  int list3[] = {24, 89, 1, 11, 0, 169, 2871, 12, 144, 121, 7, 15};

  test_insert_avl(a, list3, 12);

  printf("Removendo 12 e 7\n");
  Delete(a, 12);
  Delete(a, 7);
  // Delete(a, 11); Erro ao deleter um nó com 2 filhos.

  printf("\n");
  in_order(a->root);
  printf("Árvore é uma avl? => %d\n", is_avl(a));
  printf("Quantidade de nós => %d\n", size_avl(a));

  return 0;
}
