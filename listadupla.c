#include "listadupla.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void PrintLista(Lista L)
{
    ListaDupla *p;
    printf("\n");
    printf("====== Lista ======\n");
    for (p = ((ListaInfo *)L)->inicio; p != NULL; p = p->prox)
        printf("%d ID: %d\n", p->valor, p->ID);
    if (p != NULL)
    {
        printf("Inicio: %d ID: %d\n", ((ListaInfo *)L)->inicio->valor, ((ListaInfo *)L)->inicio->ID);
        printf("Fim: %d ID: %d\n", ((ListaInfo *)L)->final->valor, ((ListaInfo *)L)->final->ID);
    }
    printf("Tamanho: %d\n", ((ListaInfo *)L)->length);
    printf("\n");
}

void AddElemento(Lista L, int valor)
{
    ListaDupla *aux;
    aux = malloc(sizeof(ListaDupla));
    aux->valor = valor;
    aux->prox = NULL;
    aux->ant = NULL;
    aux->ID = 0;
    if (((ListaInfo *)L)->inicio == NULL)
    {
        ((ListaInfo *)L)->inicio = aux;
        ((ListaInfo *)L)->final = aux;
        ((ListaInfo *)L)->length++;
    }
    else
    {
        ListaDupla *p;
        p = ((ListaInfo *)L)->inicio;
        aux->ID++;
        while (p->prox != NULL)
        {
            p = p->prox;
            aux->ID++;
        }
        aux->ant = p;
        p->prox = aux;
        ((ListaInfo *)L)->length++;
        ((ListaInfo *)L)->final = aux;
    }
}

bool InsereElemento(Lista L, int valor, int ID)
{
    ListaDupla *p = ((ListaInfo *)L)->inicio;
    if (((ListaInfo *)L)->inicio == NULL)
    {
        return false;
    }
    else
    {
        ListaDupla *aux = malloc(sizeof(ListaDupla));
        aux->valor = valor;
        while (p->ID != ID)
        {
            p = p->prox;
            if (p == NULL)
            {
                AddElemento(L, valor);
                return;
            }
        }
        aux->ant = p->ant;
        p->ant = aux;
        aux->prox = p;
        aux->ID = p->ID;
        ((ListaInfo *)L)->length++;
        // Ajeita o ID das próximas
        p->ID++;
        while (p->prox != NULL)
        {
            p = p->prox;
            p->ID++;
        }
        if (ID == 0)
        {

            ((ListaInfo *)L)->inicio = aux;
        }
        else
        {
            p = ((ListaInfo *)L)->inicio;
            while (p->ID != ID - 1)
            {
                p = p->prox;
            }
            p->prox = (ListaDupla *)aux;
        }
    }
    return true;
}

bool EditaElemento(Lista L, int novovalor, int ID)
{
    ListaDupla *p = ((ListaInfo *)L)->inicio;
    while (p->ID != ID)
    {
        p = p->prox;
    }
    p->valor = novovalor;
}

bool RemoveElemento(Lista L, int ID)
{
    ListaDupla *rmv, *p;
    p = ((ListaInfo *)L)->inicio;
    rmv = ((ListaInfo *)L)->inicio;
    while (rmv->ID != ID)
    {
        rmv = rmv->prox;
    }
    if (ID == 0)
    {
        ((ListaInfo *)L)->inicio = rmv->prox;
        if (rmv->prox != NULL)
        {
            p = p->prox;
            p->ant = NULL;
            p->ID--;
        }
    }
    else
    {
        while (p->ID != ID - 1)
        {
            p = p->prox;
        }
        p->prox = rmv->prox;
        if (rmv->prox != NULL)
        {
            p->prox->ant = p;
        }
    }
    if (rmv->ID + 1 == ((ListaInfo *)L)->length)
    {
        ((ListaInfo *)L)->final = rmv->ant;
    }
    ((ListaInfo *)L)->length--;
    free(rmv);

    // Ajeita o ID das próximas
    if (((ListaInfo *)L)->length != 0)
    {
        while (p->prox != NULL)
        {
            p = p->prox;
            p->ID--;
        }
    }
}

bool BuscaID(Lista L, int valor)
{
    int ID;
    ListaDupla *p;
    p = ((ListaInfo *)L)->inicio;
    while (p->prox != NULL)
    {
        if (p->valor == valor)
        {
            break;
        }
        p = p->prox;
    }
    ID = p->ID;
    return ID;
}

bool BuscaValor(Lista L, int ID)
{
    int val;
    ListaDupla *p;
    p = ((ListaInfo *)L)->inicio;
    while (p->ID != ID)
    {
        if (p->prox == NULL)
        {
            break;
        }
        p = p->prox;
    }
    val = p->valor;
    return val;
}

void LimpaLista(Lista L)
{
    ListaDupla *rmv, *p;
    rmv = ((ListaInfo *)L)->inicio;
    p = ((ListaInfo *)L)->inicio;
    while (p->prox != NULL)
    {
        p = p->prox;
        free(rmv);
        rmv = p;
    }
    if (rmv != NULL)
    {
        free(rmv);
    }
    ((ListaInfo *)L)->inicio = NULL;
    ((ListaInfo *)L)->final = NULL;
    ((ListaInfo *)L)->length = 0;
}
