#include <stdio.h>
#include <stdlib.h>

struct node {
  int elem;
  struct node *next;
  struct node *prev;
};

struct node *new_list(int elem) {
  struct node *l = malloc(sizeof(struct node));
  l->elem = elem;
  l->next = NULL;
  l->prev = NULL;
  return l;
}

void show(struct node *l) {
  for(; l; l = l->next) {
    printf("%d ", l->elem);
  }
  printf("\n");
}

void append_prev(struct node **l, struct node *prev, int elem) {
  if(*l) {
    append_prev(&(*l)->next, *l, elem);
  } else {
    *l = new_list(elem);
    (*l)->prev = prev;
  }
}

void append(struct node **l, int elem) {
  append_prev(l, NULL, elem);
}

void insertion_sort(struct node **l) {
  if(*l == NULL || (*l)->next == NULL) return;
  struct node *i = *l;
  for(; i->next; i = i->next) {
    int elem = i->elem;
    struct node *prev = i->prev;
    struct node *actual = (prev) ? prev->next : NULL;
    while((prev) && (prev->elem > elem)) {
      actual->elem = prev->elem;
      prev = prev->prev;
    }
    if(actual) actual->elem = elem;
  }
}

int main() {
  struct node *l = NULL;
  show(l); //
  append(&l, 4);
  show(l); // 4
  append(&l, 7);
  show(l); // 4 7
  append(&l, 2);
  show(l); // 4 7 2
  append(&l, 5);
  show(l); // 4 7 2 5
  append(&l, 4);
  show(l); // 4 7 2 5 4
  append(&l, 0);
  show(l); // 4 7 2 5 4 0
  insertion_sort(&l);
  show(l); // 0 2 4 4 5 7
  return 0;
}
