#include <stdio.h>
#include <stdlib.h>
#include "./lib/avl.h"
#include <stdbool.h>
#include <time.h>

#define LENGTH 10000

bool checkNumber(int* list, int n, int number) {
  int temp = list[0];
  for (int i = 1; i < n; i++) {
    if (temp == number) {
      return true;
    }
    temp = list[i];
  }
  return false;
}

int *listFill(int n)
{
  int repair = 200000;
  int semente;
  srand(time(NULL));
  int *list = malloc(sizeof(int) * n);
  for (int i = 0; i < n; i++) {
    semente = (rand() % n);
    list[i] = semente;
    if (checkNumber(list, n, semente) == true) {
      list[i] = repair;
      repair += 1;
    }
  }
  return list;
}

void AvlInsert(Avl *tree, int *list, int n) 
{
  for (int i = 0; i < n; i++) {
    Insert(tree, list[i]);
  }
}

int main(int argc, char **argv)
{
  Avl *tree = CreateAvl();
  int *list = listFill(LENGTH);
  AvlInsert(tree, list, LENGTH);

  printf("\nA árvore é avl? => %d\n", IsAVL(tree));
  printf("Tamanho da árvore avl => %d\n", SizeAvl(tree));
  ClearNodes(&tree->root);
  printf("\nA árvore é avl? => %d\n", IsAVL(tree));
  printf("Tamanho da árvore avl => %d\n", SizeAvl(tree));
  return 0;
}
