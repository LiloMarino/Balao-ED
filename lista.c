#include "lista.h"
#include <stdlib.h>

struct StListaDupla
{
    int valor;
    int ID;
    struct StListaDupla *prox;
    struct StListaDupla *ant;
};

struct StInfoLista
{
    struct StListaDupla *inicio;
    struct StListaDupla *final;
    int capac;
    int length;
};

typedef struct StListaDupla ListaDupla;
typedef struct StInfoLista ListaInfo;

Lista CreateLista(int capacidade)
{
    ListaInfo *lista = malloc(sizeof(ListaInfo));
    lista->inicio = NULL;
    lista->final = NULL;
    lista->capac = capacidade;
    lista->length = 0;
    return lista;
}

int lengthLst(Lista L)
{
    ListaInfo *lista = (ListaInfo *)L;
    return lista->length;
}

