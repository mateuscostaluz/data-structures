#include <stdio.h>
#include <stdlib.h>

// list === node * : DEFINIÇÃO LISTA CABEÇA

// Definicao tipo lista "node"
typedef struct node *list;

// Definicao estrutura "node"
struct node {
  int elem;
  struct node *next;
};

// Criacao lista vazia
list new_list(int elem) {
  list l = malloc(sizeof(struct node));
  l->elem = elem;
  l->next = NULL;
  return l;
}

// Exibicao elementos lista
void show(list l) {
  for(; l; l = l->next) {
    printf("%d ", l->elem);
  }
  printf("\n");
}

// Insere início lista
void push(list *l, int elem) {
  list aux = new_list(elem);
  aux->next = *l;
  *l = aux;
}

// Remove primeiro elemento
// "->" tem maior precedencia que "*", por isso usa-se (*l)
int pop(list *l) {
  if(*l) {
    int elem = (*l)->elem;
    *l = (*l)->next;
    return elem;
  }
  return -999;
}

// Insere final lista
void append(list *l, int elem) {
  if (*l) {
    // Nao esta no ultimo elemento
    //    l        : list*
    //   *l        : list
    //  (*l)->next : list
    // &(*l)->next : list*
    append(&(*l)->next, elem);
  } else {
    // Esta no ultimo elemento
    *l = new_list(elem);
  }
}

int main() {
  list l = NULL;
  show(l); //
  push(&l, 3);
  show(l); // 3
  push(&l, 2);
  show(l); // 2 3
  push(&l, 1);
  show(l); // 1 2 3
  printf("%d\n", pop(&l)); // 1
  printf("%d\n", pop(&l)); // 2
  printf("%d\n", pop(&l)); // 3
  printf("%d\n", pop(&l)); // -999 (lista vazia)
  append(&l, 1);
  show(l); // 1
  append(&l, 2);
  show(l); // 1 2
  append(&l, 3);
  show(l); // 1 2 3
  return 0;
}
