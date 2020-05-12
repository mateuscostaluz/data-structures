#include <stdio.h>
#include <stdlib.h>

// tendo em vista as compras relizadas com um cartao de crrdito qualquer
// pude observar que, por conta de nao se ter ideia da quantidade de compras
// que sera realizadas, nao poderia armazenar a estrutura da compra em um vetor
// de compras simples, portanto, torna-se necessario o uso de uma lista encadeada

struct cmp {
    int idCmp;           // armazenara o id de cada compra (para possivel solicitacao de estorno, comecando por 0)
    float vlrCmp;        // armazerara o valor da compra (para calculo de gastos totais e futuras faturas de cobranca)
    int cmpCancelada;    // armazenara 0 para compra nao cancelada e 1 para compra cancelada, preferi guardar o historico
    struct cmp *proxCmp; // para apontar para a praxima compra efetuada com o cartao, ligando as compras em lista encadeada
};

typedef struct cmp compra;

void registrarCompra(float valor, compra **cartao) {
    compra *aux;
    aux = *cartao;
    compra *novaCompra = malloc(sizeof(compra));
    novaCompra->vlrCmp = valor;
    novaCompra->cmpCancelada = 0;
    novaCompra->proxCmp = NULL;
    if(*cartao == NULL) {
        novaCompra->idCmp = 0;
        *cartao = novaCompra;
    }
    else {
        int i;
        int id = aux->idCmp;
        for(i = 0; aux->proxCmp != NULL; i++) {
            aux = aux->proxCmp;
            id = aux->idCmp;
        }
        novaCompra->idCmp = ++id;
        aux->proxCmp = novaCompra;
    }
}

void estornarCompra(int id, compra **cartao) {
    compra *aux;
    aux = *cartao;
    int i;
    for(i = 0; aux->idCmp != id; i++) {
        aux = aux->proxCmp;
    }
    aux->cmpCancelada = 1;
}

float removerCompra(int id, compra **cartao) { // NAO UTILIZAR, FIZ APENAS PARA DEMONSTRAR A REMOCAO DE UM ELEMENTO DA LISTA ENCADEADA
    int valorRemovido;
    compra *aux;
    compra *anterior;
    aux = *cartao;
    int i;
    for(i = 0; aux->idCmp != id; i++) {
        anterior = aux;
        aux = aux->proxCmp;
    }
    anterior->proxCmp = aux->proxCmp;
    valorRemovido = aux->vlrCmp;
    free(aux);
    return valorRemovido;
}

float calcularFatura(compra *cartao) {
    float totalFatura = 0;
    compra *aux;
    aux = cartao;
    int i;
    for(i = 0; aux != NULL; i++) {
        if(aux->cmpCancelada == 0) {
            totalFatura = totalFatura + aux->vlrCmp;
        }
        aux = aux->proxCmp;
    }
    return totalFatura;
}

int main()
{
    compra *cartao = NULL;
    registrarCompra(100.0, &cartao);
    registrarCompra(200.0, &cartao);
    registrarCompra(400.0, &cartao);
    registrarCompra(300.0, &cartao);
    estornarCompra(2, &cartao);
    printf("Valor total da fatura: %.2f", calcularFatura(cartao)); // PARA DEMONSTRAR QUE A FUNCAO NAO ESTA SOMANDO A COMPRA ESTORNADA
    float valorRemovido;
    valorRemovido = removerCompra(2, &cartao);
    printf("\nValor removido: %2.f", valorRemovido);
    registrarCompra(500.0, &cartao);
    printf("\nValor total da fatura: %.2f", calcularFatura(cartao)); // PARA DEMONSTRAR QUE A FUNCAO DE REMOCAO TAMBEM ESTA FUNCIONANDO
    return 0;
}
