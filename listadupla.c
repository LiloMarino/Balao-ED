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

typedef struct StIterator Iterator;

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

void RemoveElemento(Lista L, Posic P)
{
    ListaDupla *rmv,*rmvprox;
    rmv = (ListaDupla *)P;
    if (rmv->ID == 0)
    {
        ((ListaInfo *)L)->inicio = rmv->prox;
        if (rmv->prox != NULL)
        {
            rmvprox = rmv->prox;
            rmvprox->ant = rmv->ant;
            rmvprox->ID--;
        }
    }
    else
    {
        if (rmv->prox != NULL)
        {
            proc->prox->ant = proc;
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
        while (rmvprox->prox != NULL)
        {
            rmvprox = rmvprox->prox;
            rmvprox->ID--;
        }
    }
}

void PrintLista(Lista L)
{
    ListaDupla *p;
    printf("\n");
    printf("====== Lista ======\n");
    for (p = ((ListaInfo *)L)->inicio; p != NULL; p = p->prox)
        printf("%d ID: %d\n", *(int *)p->info, p->ID);
    if (p != NULL)
    {
        printf("Inicio:Item info %d ID: %d\n", *(int *)((ListaInfo *)L)->inicio->info, ((ListaInfo *)L)->inicio->ID);
        printf("Fim: %d ID: %d\n", *(int *)((ListaInfo *)L)->final->info, ((ListaInfo *)L)->final->ID);
    }
    printf("Tamanho: %d\n", ((ListaInfo *)L)->length);
    printf("\n");
}

Posic AddElemento(Lista L, Item info)
{
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
        return aux;
    }
}

bool InsereElemento(Lista L, Item info, int ID)
{
    ListaDupla *p = ((ListaInfo *)L)->inicio;
    if (((ListaInfo *)L)->inicio == NULL)
    {
        return false;
    }
    else
    {
        ListaDupla *aux = malloc(sizeof(ListaDupla));
        aux->info = info;
        while (p->ID != ID)
        {
            p = p->prox;
            if (p == NULL)
            {
                AddElemento(L, info);
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

bool BuscaID(Lista L, Item info)
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
