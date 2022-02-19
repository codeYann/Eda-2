#include "./lib/avl.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 10000

bool check_number(int *list, int n, int number) {
  int temp = list[0];
  for (int i = 1; i < n; i++) {
    if (temp == number) {
      return true;
    }
    temp = list[i];
  }
  return false;
}

int *list_fill(int n) {
  int repair = 200001;
  int semente;
  int *list = malloc(sizeof(int) * n);
  srand(time(NULL));
  for (int i = 0; i < n; i++) {
    semente = (rand() % n);
    list[i] = semente;
    if (check_number(list, n, semente) == true) {
      list[i] = repair;
      repair += 1;
    }
  }
  return list;
}

void avl_insert_test(Avl *tree, int *list, int n) {
  for (int i = 0; i < n; i++) {
    Insert(tree, list[i]);
  }
}

int main(int argc, char **argv) {
  Avl *tree;
  int *list;
  for (int i = 0; i < LENGTH; i++) {
    tree = create_avl();
    list = list_fill(LENGTH);
    avl_insert_test(tree, list, LENGTH);

    printf("\nA árvore é avl? => %d\n", is_avl(tree));
    printf("Tamanho da árvore avl => %d\n", size_avl(tree));
    clear_nodes(&tree->root);
    free(tree);
    free(list);
  }

  return 0;
}
