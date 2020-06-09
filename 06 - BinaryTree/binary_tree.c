#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node *left;
  struct node *right;
}; // estrutura node da arvore binaria

struct node *newnode(int data) {
  struct node *temp = malloc(sizeof(struct node));
  temp->data = data;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
} // criacao de novo node da arvore binaria

struct node* insert(struct node* node, int data) {
  if(!node) return newnode(data);
  if(data < node->data) node->left = insert(node->left, data);
  else node->right = insert(node->right, data);
  return node;
} // funcao para insercao do novo node na arvore binaria
  // verifica se a raiz (primeiro node) é nula, se sim, cria um node e retorna
  // caso contrario, verifica se é maior ou menor do que a raiz
  // chama a si mesma, verifica se é maior ou menor do que o próximo node e
  // faz isso sucessivamente até encontrar a posição nula passível de inserção

struct node* delete(struct node* root, int data) {
  // caso básico
  if (!root) return root;

  // chamada recursiva para descobrir qual é antecessor
  // do node que será deletado
  if (root->data > data) {
    root->left = delete(root->left, data);
    return root;
  }
  else if (root->data < data) {
    root->right = delete(root->right, data);
    return root;
  }

  // o codigo abaixo sera chamado quando o node a ser deletado for encontrado

  // verifica se os nodes abaixo do "antecessor" ("sucessor") estao vazios
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

  // se o os dois nodes abaixo nao forem nulos
  else {
    struct node* successorparent = root;
    struct node *succ = root->right;

    // encontra o "antecessor" (foi definido que seria sempre o menor)
    while (succ->left) {
      successorparent = succ;
      succ = succ->left;
    }

    // deleta o "sucessor"
    // como o "sucessor" sempre é filho esquerdo de seu pai,
    // podemos fazer o filho direito do "sucessor" como esquerdo de seu pai
    // Se não houver "sucessor", faz a atribuicao de succ-> right
    //                                    para succParent-> right
    if (successorparent != root)
      successorparent->left = succ->right;
    else
      successorparent->right = succ->right;

    // copia o conteudo do "sucessor" para a raiz
    root->data = succ->data;

    // deleta o "sucessor"
    free(succ);

    // retorna a raiz
    return root;
  }
}

int treeheight(struct node* root) {
  int left;
  int right;
  if (!root) return -1;
  left = treeheight(root->left);
  right = treeheight(root->right);
  if (left > right) return left+1;
  else return right+1;
} // verifica se a arvore nao é nula
  // define duas variaveis para saber a altura dos nodes esquerdos e direitos
  // chama a si mesma, incrementando as variaveis definidas
  // ate que chege no final dos nodes e defina qual o maior dos valores
  // retornando a altura

void height(struct node* root) {
  printf("The height of tree is: %d.\n", treeheight(root));
} // apenas para formatar a impressao

void inorder(struct node *root) {
  if (root) {
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
  }
} // imprime, em ordem, da esquerda para a direita de cada node,
  // chamando a si mesma até encontrar o último elemento da "pilha", retornando
  // os resultados em ordem

void print(struct node *root) {
  if(!root) printf("The tree is empty.");
  else{
    printf("Tree: ");
    inorder(root);
  }
  printf("\n");
} // apenas para formatar a impressão

int main() {
  struct node *root = NULL;
  print(root);
  height(root);
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
