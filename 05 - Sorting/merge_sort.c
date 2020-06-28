#include <stdio.h>
#include <stdlib.h>

// divide and conquer
// O(nlogn)
// Von Neumann
// worst case -> maximum comparison
/*      (Example)
    [4,0,6,2,5,1,7,3]
        /        \
       /          \
 [4,0,6,2] and [5,1,7,3]
    / \            / \
   /   \          /   \
[4,0] [6,2]    [5,1] [7,3]  Every pair of 2 will be compared
  |     |        |     |
  |     |        |     |
[0,4] [2,6]    [1,5] [3,7]  Every pair of set is used in comparison
  \    /         \    /
   \  /           \  /
[0,2,4,6]      [1,3,5,7]    Every pair of set compared
    \             /
     \           /
   [0,1,2,3,4,5,6,7]
*/

// define Node struct
struct Node {
  int data;
  struct Node* next;
};

// split the nodes into two sublists
void front_back_split(struct Node* p, struct Node** front, struct Node** back) {
  *front = p->next;
  *back = p;

  // advance '(*front)' two nodes and '(*back)' one node
  while (*front != NULL) {
    *front = (*front)->next;
    if (*front != NULL) {
      *front = (*front)->next;
      *back = (*back)->next;
    }
  }

  // '(*back)' is before the midpoint in the list
  *front = *back;
  *back = (*back)->next;
  (*front)->next = NULL;
  *front = p;
}

struct Node* sorted_merge(struct Node* a, struct Node* b) {
  struct Node* p = NULL;

  // base case
  // check if a = NULL or b = NULL
  if (a == NULL) return (b);
  else if (b == NULL) return (a);

  // pick either a or b
  if (a->data <= b->data) {
    p = a;
    p->next = sorted_merge(a->next, b);
  }
  else {
    p = b;
    p->next = sorted_merge(a, b->next);
  }
  return (p);
}

// change next pointers (not data)
void merge_sort(struct Node** p) {
  // base case
  // list = NULL or list with one element
  if (*p == NULL || (*p)->next == NULL) {
    return;
  }

  struct Node* head = *p;
  struct Node* a;
  struct Node* b;

  // split head into 'a' and 'b' sublists
  front_back_split(*p, &a, &b);

  // recursively sort the sublists
  merge_sort(&a);
  merge_sort(&b);

  // merge the two sorted lists
  *p = sorted_merge(a, b);
}

void show(struct Node* node) {
  while (node != NULL) {
    printf("%d ", node->data);
    node = node->next;
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

void main() {
  struct Node* p = NULL;

  // create a unsorted linked lists to test the functions (2->3->20->5->10->15)
  push(&p, 4);
  push(&p, 0);
  push(&p, 6);
  push(&p, 2);
  push(&p, 5);
  push(&p, 1);
  push(&p, 7);
  push(&p, 3);

  // sort the linked list
  merge_sort(&p);

  printf("Sorted: ");
  show(p);
}
