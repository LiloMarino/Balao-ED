#include "fila_estatica.h"
#include <stdlib.h>

struct StFilaEstatica
{
    Item *elementos;
    int capacidade;
    int inicio;
    int fim;
    int tamanho;
};

typedef struct StFilaEstatica FilaEstatica;

Fila criarFila(int capacidade)
{
    Fila fila = malloc(sizeof(FilaEstatica));
    fila->elementos = malloc(capacidade * sizeof(Item));
    fila->capacidade = capacidade;
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
    return fila;
}

bool inserirFila(Fila fila, Item item)
{
    if (fila->tamanho == fila->capacidade)
    {
        return false; // fila cheia
    }
    fila->elementos[fila->fim] = item;
    fila->fim = (fila->fim + 1) % fila->capacidade;
    fila->tamanho++;
    return true;
}

Item removerFila(Fila fila)
{
    if (filaVazia(fila))
    {
        return NULL; // fila vazia
    }
    Item itemRemovido = fila->elementos[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->capacidade;
    fila->tamanho--;
    return itemRemovido;
}

int tamanhoFila(Fila fila)
{
    return fila->tamanho;
}

bool filaVazia(Fila fila)
{
    return fila->tamanho == 0;
}