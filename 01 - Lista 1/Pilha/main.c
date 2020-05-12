// Suponha que exista um lote de 10 lugares e que a cada nova compra o lote seja armazenado
// sempre atras do lote anterior e, a cada venda, o ultimo lote do estoque sera removido

#include <stdio.h>
#include <stdlib.h>

void compra(int *f, int *t, int n, int lote) {
    if(*t == n) {
        return -999;
    }
    f[*t] = lote;
    *t+=1;
    return 1;
}

int venda(int *f, int *t, int n) {
    int loteRemovido = -999;
    if(*t != 0) {
        loteRemovido = f[*t-1];
        *t-=1;
    }
    return loteRemovido;
}

int main()
{
    int tamanhoEstoque;
    tamanhoEstoque = 10;
    int estoque[10];
    int ultimaPosicao = 0;
    compra(estoque, &ultimaPosicao, 10, 1);
    compra(estoque, &ultimaPosicao, 10, 2);
    compra(estoque, &ultimaPosicao, 10, 3);
    int loteVendido;
    loteVendido = venda(estoque, &ultimaPosicao, tamanhoEstoque);
    printf("Lote removido: %d", loteVendido);
    loteVendido = venda(&estoque, &ultimaPosicao, tamanhoEstoque);
    printf("\nLote removido: %d", loteVendido);
    loteVendido = venda(&estoque, &ultimaPosicao, tamanhoEstoque);
    printf("\nLote removido: %d", loteVendido);
    loteVendido = venda(&estoque, &ultimaPosicao, tamanhoEstoque);
    printf("\nLote removido: %d", loteVendido);
    return 0;
}
