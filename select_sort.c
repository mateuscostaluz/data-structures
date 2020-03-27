#include <stdio.h>

// Define a primeira posição (i) do vetor como a menor e compara com as demais
// Depois define a próxima posição (i + 1) como a menor e também compara com as demais
// Segue, sucessivamente, até o final do vetor
// No fim da iteração ocorre a troca do elemento definido com o menor do vetor, caso necessário
// Os elementos antes do índice atual (i) já encontram-se organizados

void select_sort(int* v, int n) {
  int min = 0;
  int temp = 0;
  for(int i = 0; i < n; i++) {
    min = i;
    for(int j = i + 1; j < n; j++) {
      if(v[j] < v[min]) {
        min = j;
      }
    }
    temp = v[i];
    v[i] = v[min];
    v[min] = temp;
  }
}

void show(int* v, int n) {
  for(int i = 0; i < n; i++) {
    printf("%d ", v[i]);
  }
}

int main() {
  int v[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  int n = sizeof(v) / sizeof(int);
  select_sort(v, n);
  show(v, n);
  return 0;
}
