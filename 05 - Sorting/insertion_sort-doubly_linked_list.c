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
  if(!l) {
    printf("Nothing to show.\n");
    return;
  }
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
  if((!*l) || (!(*l)->next)) {
    printf("Nothing to sort.\n");
    return;
  }
  struct node *i = *l;
  struct node *j = i->next;
  for(; j; j = j->next) {
    int x = j->elem;
    for(i = j->prev; i && i->elem > x; i = i->prev) {
      i->next->elem = i->elem;
    }
    if(!i) {
      i = *l;
      i->elem = x;
    } else {
      i->next->elem = x;
    }
  }
}

int main() {
  struct node *l = NULL;
  insertion_sort(&l);
  show(l); //
  append(&l, 4);
  show(l); // 4
  insertion_sort(&l);
  append(&l, 7);
  show(l); // 4 7
  insertion_sort(&l);
  append(&l, 2);
  show(l); // 4 7 2
  insertion_sort(&l);
  show(l); // 2 4 7
  append(&l, 5);
  show(l); // 2 4 7 5
  append(&l, 4);
  show(l); // 2 4 7 5 4
  append(&l, 0);
  show(l); // 2 4 7 5 4 0
  insertion_sort(&l);
  show(l); // 0 2 4 4 5 7
  return 0;
}
