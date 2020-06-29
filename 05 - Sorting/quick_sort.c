#include <stdio.h>
#include <stdlib.h>

// define Node struct
struct Node {
  int data;
  struct Node* next;
};

// print list
void show(struct Node* p) {
  for(; p; p = p->next) {
    printf("%d ", p->data);
  }
}

// insert a node at the beginging of the linked list
void push(struct Node** p, int data) {
  // allocate node
  struct Node* new = (struct Node*)malloc(sizeof(struct Node));

  // put 'data' in the data
  new->data = data;

  // link list in the new node
  new->next = (*p);

  // move the head to point to the new node
  (*p) = new;
}

// returns the last node of the list
struct Node *tail(struct Node *p) {
  for(; (p && p->next); p = p->next);
  return p;
}

// partitions the list taking the last element as the pivot
struct Node *partition(struct Node *head,
                       struct Node *end,
                       struct Node **newHead,
                       struct Node **newEnd) {

  struct Node *cur = head;
  struct Node *pivot = end;
  struct Node *tail = pivot;
  struct Node *prev = NULL;

  // during partition, both the head and end of the list might change
  // which is updated in the newHead and newEnd variables
  while(cur != pivot) {
    if (cur->data < pivot->data) {
      // if the first node that has a value less than the pivot
      // first node becomes the new head
      if ((*newHead) == NULL) (*newHead) = cur;

      prev = cur;
      cur = cur->next;
    } else { // if cur node is greater than pivot

      // move cur node to next of tail, and change tail
      if (prev) prev->next = cur->next;
      struct Node *tmp = cur->next;
      cur->next = NULL;
      tail->next = cur;
      tail = cur;
      cur = tmp;
    }
  }

  // if the pivot data is the smallest element in the current list
  // pivot becomes the head
  if ((*newHead) == NULL) (*newHead) = pivot;

  // update newEnd to the current last node
  (*newEnd) = tail;

  // return the pivot node
  return pivot;
}

// here the sorting happens exclusive of the end node
struct Node *quickSortRecur(struct Node *head, struct Node *end) {
  // base condition
  if (!head || head == end) return head;

  struct Node *newHead = NULL;
  struct Node *newEnd = NULL;

  // partition the list, newHead and newEnd will be updated
  // by the partition function
  struct Node *pivot = partition(head, end, &newHead, &newEnd);

  // if pivot is the smallest element
  // no need to recursion for the left part
  if (newHead != pivot) {
    // set the node before the pivot node as NULL
    struct Node *tmp = newHead;
    while(tmp->next != pivot) tmp = tmp->next;
    tmp->next = NULL;

    // recursion for the list before pivot
    newHead = quickSortRecur(newHead, tmp);

    // change next of last node of the left half to pivot
    tmp = tail(newHead);
    tmp->next = pivot;
  }

  // recursion for the list after the pivot element
  pivot->next = quickSortRecur(pivot->next, newEnd);

  return newHead;
}

// main function for quick sort
void quickSort(struct Node **headRef) {
  (*headRef) = quickSortRecur(*headRef, tail(*headRef));
  return;
}

void main() {
  struct Node *p = NULL;
  push(&p, 4);
  push(&p, 7);
  push(&p, 2);
  push(&p, 6);
  push(&p, 4);
  push(&p, 1);
  push(&p, 8);
  push(&p, 3);

  printf("Before sorting: ");
  show(p);

  // sort list
  quickSort(&p);
  printf("\n");

  printf(" After sorting: ");
  show(p);
}
