#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node *left;
  struct node *right;
};

struct node *newnode(int data) {
  struct node *temp = malloc(sizeof(struct node));
  temp->data = data;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

struct node* insert(struct node* node, int data) {
  if(!node) return newnode(data);
  if(data < node->data) node->left = insert(node->left, data);
  else node->right = insert(node->right, data);
  return node;
}

struct node* delete(struct node* root, int data) {
  if (!root) return root;
  if (root->data > data) {
    root->left = delete(root->left, data);
    return root;
  }
  else if (root->data < data) {
    root->right = delete(root->right, data);
    return root;
  }
  if (!root->left) {
    struct node* temp = root->right;
    free(root);
    return temp;
  }
  else if (!root->right) {
    struct node* temp = root->left;
    free(root);
    return temp;
  }
  else {
    struct node* successorparent = root;
    struct node *succ = root->right;
    while (succ->left) {
      successorparent = succ;
      succ = succ->left;
    }
    if (successorparent != root)
      successorparent->left = succ->right;
    else
      successorparent->right = succ->right;
    root->data = succ->data;
    free(succ);
    return root;
  }
}

int treeheight(struct node* root) {
  int left, right;
  if (!root) return -1;
  left = treeheight(root->left);
  right = treeheight(root->right);
  if (left > right) return left+1;
  else return right+1;
}

void height(struct node* root) {
  printf("The height of tree is: %d.\n", treeheight(root));
}

void inorder(struct node *root) {
  if (root) {
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
  }
}

void print(struct node *root) {
  if(!root) printf("The tree is empty.");
  else{
    printf("Tree: ");
    inorder(root);
  }
  printf("\n");
}

int main() {
  struct node *root = NULL;
  print(root);
  root = insert(root, 50);
  print(root);
  height(root);
  insert(root, 30);
  print(root);
  insert(root, 20);
  print(root);
  height(root);
  insert(root, 40);
  print(root);
  insert(root, 70);
  print(root);
  insert(root, 60);
  print(root);
  insert(root, 80);
  print(root);
  insert(root, 80);
  print(root);
  insert(root, 90);
  print(root);
  insert(root, 100);
  print(root);
  delete(root, 200);
  print(root);
  height(root);
  delete(root, 50);
  print(root);
  delete(root, 0);
  print(root);
  insert(root, 10);
  print(root);
  height(root);
  return 0;
}
