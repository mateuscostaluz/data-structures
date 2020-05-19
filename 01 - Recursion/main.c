#include <stdio.h>
#include <stdlib.h>

// tendo em vista o mesmo programa entregue na atividade de "Lista Encadeada", resolvi implementar uma
// funcao recursiva para calcular o valor total da fatura e outra funcao recursiva para encontrar o maior
// valor da lista encadeada em si, justamente para demonstrar que a recursao serve como um laco alternativo

struct cmp {
    int idCmp;           // armazenara o id de cada compra (para possivel solicitacao de estorno, comecando por 0)
    float vlrCmp;        // armazerara o valor da compra (para calculo de gastos totais e futuras faturas de cobranca)
    int cmpCancelada;    // armazenara 0 para compra nao cancelada e 1 para compra cancelada, preferi guardar o historico
    struct cmp *proxCmp; // para apontar para a proxima compra efetuada com o cartao, ligando as compras em lista encadeada
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

float calcularFaturaRecursivo(compra *aux, float totalFatura) {
    if(aux->proxCmp == NULL) {
        if(aux->cmpCancelada == 0) {
            totalFatura = totalFatura + aux->vlrCmp;
        }
        return totalFatura;
    }
    else {
        if(aux->cmpCancelada == 0) {
            totalFatura = totalFatura + aux->vlrCmp;;
        }
        return calcularFaturaRecursivo(aux->proxCmp, totalFatura);
    }
}

float maiorCompraRecursivo(compra *aux) {
    if(aux->proxCmp == NULL) {
        if(aux->cmpCancelada == 0) {
            return aux->vlrCmp;
        }
        else {
            return 0;
        }
    }
    else {
        float f = maiorCompraRecursivo(aux->proxCmp);
        if(f > aux->vlrCmp) {
            return f;
        }
        else {
            return aux->vlrCmp;
        }
    }
}

int main()
{
    compra *cartao = NULL;
    registrarCompra(100.0, &cartao);
    registrarCompra(200.0, &cartao);
    registrarCompra(400.0, &cartao);
    registrarCompra(300.0, &cartao);
    estornarCompra(2, &cartao);
    compra *aux = cartao;
    float totalFatura = 0;
    totalFatura = calcularFaturaRecursivo(aux, totalFatura);
    printf("Valor total da fatura (recursivo): %.2f", totalFatura); // PARA DEMONSTRAR QUE A FUNCAO NAO ESTA SOMANDO A COMPRA ESTORNADA
    float valorRemovido;
    valorRemovido = removerCompra(2, &cartao);
    printf("\nValor removido: %2.f", valorRemovido);
    registrarCompra(500.0, &cartao);
    totalFatura = 0;
    totalFatura = calcularFaturaRecursivo(aux, totalFatura);
    printf("\nValor total da fatura (recursivo): %.2f", totalFatura); // PARA DEMONSTRAR QUE A FUNCAO DE REMOCAO TAMBEM ESTA FUNCIONANDO
    float maiorCompra = 0;
    maiorCompra = maiorCompraRecursivo(aux);
    printf("\nValor da maior compra (recursivo): %.2f", maiorCompra);
    return 0;
}
