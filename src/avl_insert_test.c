#include "./lib/avl.h"
#include <stdio.h>

int list1[] = {10, 4, 89, 12, 3, 7, 20, 30, 40, 17, 9, 1, 15, 8};
int list2[] = {18, 16, 14, 12, 10, 1, 22, 24, 26, 30, 32};
int list3[] = {24, 89, 1, 11, 0, 169, 2871, 12, 144, 121, 7, 15};

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
  Avl *b = create_avl();
  Avl *c = create_avl();

  test_insert_avl(a, list1, 14);
  test_insert_avl(b, list2, 11);
  test_insert_avl(c, list3, 12);
  return 0;
}
