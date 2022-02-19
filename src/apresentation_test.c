#include "./lib/avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool checkNumber(int *list, int n, int number) {
  for (int i = 0; i < n; i++) {
    if (list[i] != number)
      continue;
    else
      return true;
  }
  return false;
}

int main(int argc, char **argv) {
  Avl *main = create_avl();

  int list[100];
  int semente, repair = 101;
  srand(time(NULL));

  for (int i = 0; i < 100; i++) {
    semente = rand() % 100;
    list[i] = semente;
    if (checkNumber(list, 100, semente)) {
      list[i] = repair;
      repair += 1;
    }
  }

  for (int i = 0; i < 100; i++) {
    Insert(main, list[i]);
  }

  in_order(main->root);
  printf("\nA árvore é avl? => %d\n", is_avl(main));
  printf("Tamanho da árvore avl => %d\n", size_avl(main));

  return 0;
}
