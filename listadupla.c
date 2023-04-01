#include "listadupla.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct StListaDupla
{
    Item info;
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

struct StIterator
{
    struct StListaDupla *curr;
    bool reverso;
};

typedef struct StListaDupla ListaDupla;
typedef struct StInfoLista ListaInfo;
typedef struct StIterator IteratorInfo;

Lista CreateLista(int capacidade)
{
    ListaInfo *lista = malloc(sizeof(ListaInfo));
    lista->inicio = NULL;
    lista->final = NULL;
    lista->capac = capacidade;
    lista->length = 0;
    if (capacidade < 0)
    {
        lista->capac = CAPAC_ILIMITADA;
    }
    return lista;
}

int lengthLst(Lista L)
{
    ListaInfo *lista = (ListaInfo *)L;
    return lista->length;
}

int maxLengthLst(Lista L)
{
    if (((ListaInfo *)L)->capac == CAPAC_ILIMITADA)
    {
        return -1;
    }
    else
    {
        return ((ListaInfo *)L)->capac;
    }
}

bool isEmptyLst(Lista L)
{
    return ((ListaInfo *)L)->length == 0;
}

bool isFullLst(Lista L)
{
    if (((ListaInfo *)L)->capac == CAPAC_ILIMITADA)
    {
        return false;
    }
    else
    {
        return ((ListaInfo *)L)->length == ((ListaInfo *)L)->capac;
    }
}

Posic AddElemento(Lista L, Item info)
{
    // Verifica se a lista está cheia
    if (((ListaInfo *)L)->length >= ((ListaInfo *)L)->capac)
    {
        return NIL;
    }
    else
    {
        ListaDupla *aux;
        aux = malloc(sizeof(ListaDupla));
        aux->info = info;
        aux->prox = NULL;
        aux->ant = NULL;
        aux->ID = 0;

        // Verifica se a lista está vazia
        if (((ListaInfo *)L)->inicio == NULL)
        {
            ((ListaInfo *)L)->inicio = aux;
        }
        else
        {
            ListaDupla *p;
            p = ((ListaInfo *)L)->final;
            aux->ant = p;
            p->prox = aux;
            aux->ID = p->ID++;
        }
        ((ListaInfo *)L)->length++;
        ((ListaInfo *)L)->final = aux;
        return aux;
    }
}

void RemoveElemento(Lista L, Posic p)
{
    ListaDupla *rmv, *aux;
    rmv = (ListaDupla *)p;

    // Verifica se é o primeiro elemento da lista
    if (rmv->ID == 0)
    {
        if (rmv->prox != NULL)
        {
            ((ListaInfo *)L)->inicio = rmv->prox;
            rmv->prox->ant = rmv->ant;
            aux = rmv->prox;
            aux->ID--;
        }
        else
        {
            ((ListaInfo *)L)->inicio = NULL;
        }
    }
    else if (rmv->prox != NULL)
    {
        rmv->prox->ant = rmv->ant;
        rmv->ant->prox = rmv->prox;
        aux = rmv->prox;
        aux->ID--;
    }

    // Se for o último elemento da lista
    if (rmv->ID + 1 == ((ListaInfo *)L)->length)
    {
        ((ListaInfo *)L)->final = rmv->ant;
    }
    ((ListaInfo *)L)->length--;
    free(rmv);

    // Ajeita o ID das próximas
    if (((ListaInfo *)L)->length != 0)
    {
        while (aux->prox != NULL)
        {
            aux = aux->prox;
            aux->ID--;
        }
    }
}

Item getLst(Posic p)
{
    ListaDupla *aux = (ListaDupla *)p;
    return aux->info;
}

Posic insertBefore(Lista L, Posic p, Item info)
{
    // Verifica se a lista está cheia
    if (((ListaInfo *)L)->length >= ((ListaInfo *)L)->capac)
    {
        return NIL;
    }
    else
    {
        // Insere um item na lista antes do item indicado por p
        ListaDupla *aux = (ListaDupla *)p;
        ListaDupla *new = malloc(sizeof(ListaDupla));
        new->info = info;
        new->prox = aux;
        aux->ant = new;
        new->ant = aux->ant;
        new->ID = aux->ID;
        if (new->ant != NULL)
        {
            new->ant->prox = new;
        }
        else
        {
            ((ListaInfo *)L)->inicio = new;
        }
        ((ListaInfo *)L)->length++;

        // Ajeita o ID das próximas
        aux->ID++;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
            aux->ID++;
        }
        return new;
    }
}

Posic insertAfterLst(Lista L, Posic p, Item info)
{
    // Verifica se a lista está cheia
    if (((ListaInfo *)L)->length >= ((ListaInfo *)L)->capac)
    {
        return NIL;
    }
    else
    {
        // Insere um item na lista depois do item indicado por p
        ListaDupla *aux = (ListaDupla *)p;
        ListaDupla *new = malloc(sizeof(ListaDupla));
        new->info = info;
        new->ant = aux;
        aux->prox = new;
        new->prox = aux->prox;
        new->ID = aux->ID;
        if (new->prox != NULL)
        {
            new->prox->ant = new;
        }
        else
        {
            ((ListaInfo *)L)->final = new;
        }
        ((ListaInfo *)L)->length++;

        // Ajeita o ID das próximas
        aux->ID++;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
            aux->ID++;
        }
        return new;
    }
}

Posic getFirstLst(Lista L)
{
    if (((ListaInfo *)L)->length == 0)
    {
        return NIL;
    }
    else
    {
        return ((ListaInfo *)L)->inicio;
    }
}

Posic getNextLst(Lista L, Posic p)
{
    if (((ListaInfo *)L)->final == p)
    {
        return NIL;
    }
    else
    {
        return ((ListaDupla *)p)->prox;
    }
}

Posic getLastLst(Lista L)
{
    if (((ListaInfo *)L)->length == 0)
    {
        return NIL;
    }
    else
    {
        return ((ListaInfo *)L)->final;
    }
}

Posic getPreviousLst(Lista L, Posic p)
{
    if (((ListaInfo *)L)->inicio == p)
    {
        return NIL;
    }
    else
    {
        return ((ListaDupla *)p)->ant;
    }
}

void PrintLista(Lista L)
{
    ListaDupla *p;
    printf("\n");
    printf("====== Lista ======\n");
    for (p = ((ListaInfo *)L)->inicio; p != NULL; p = p->prox)
        printf("%p ID: %d\n", p->info, p->ID);
    if (p != NULL)
    {
        printf("Inicio: %p ID: %d\n", ((ListaInfo *)L)->inicio->info, ((ListaInfo *)L)->inicio->ID);
        printf("Fim: %p ID: %d\n", ((ListaInfo *)L)->final->info, ((ListaInfo *)L)->final->ID);
    }
    printf("Tamanho: %d\n", ((ListaInfo *)L)->length);
    printf("\n");
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

Iterador createIterador(Lista L, bool reverso)
{
    IteratorInfo *it = malloc(sizeof(IteratorInfo));
    if (reverso)    
    {
        it->curr = ((ListaInfo *)L)->final;
    }
    else
    {
        it->curr = ((ListaInfo *)L)->inicio;
    }
    return it;
}
