#include <stdio.h>
#include "./lib/avl.h"

int main(int argc, char** argv) {
  Avl* a = CreateAvl();
  Insert(a, 10);
  Insert(a, 4);
  Insert(a, 89);
  Insert(a, 12);
  Insert(a, 3);
  Insert(a, 7);
  Insert(a, 20);
  Insert(a, 30);
  Insert(a, 40);
  Insert(a, 17);
  Insert(a, 9);
  Insert(a, 1);
  Insert(a, 15);
  Insert(a, 8);

  InOrder(a->root);

  printf("\nOlá, mundo!");
  return 0;
}
