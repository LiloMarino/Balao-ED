#include "listadupla.h"
#include <stdio.h>
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

int LengthLista(Lista L)
{
    ListaInfo *lista = (ListaInfo *)L;
    return lista->length;
}

/*void PrintLista(Lista inicio)
{
    ListaDupla *p = (ListaDupla *)ini;
    printf("\n");
    printf("====== Lista ======\n");
    for (p = (ListaDupla *)ini; p != NULL; p = p->prox)
        printf("%d ID: %d\n", p->valor, p->ID);
    printf("\n");
}*/

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

/*void InsereElemento(Lista ini, int valor, int ID)
{
    ListaDupla *p = *(ListaDupla **)ini;
    if (*(ListaDupla **)ini == NULL)
    {
        AddElemento(ini, valor);
        return;
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
                AddElemento(ini, valor);
                return;
            }
        }
        aux->ant = p->ant;
        p->ant = aux;
        aux->prox = p;
        aux->ID = p->ID;

        // Ajeita o ID das próximas
        p->ID++;
        while (p->prox != NULL)
        {
            p = p->prox;
            p->ID++;
        }
        if (ID == 0)
        {

            *(ListaDupla **)ini = aux;
        }
        else
        {
            p = *(ListaDupla **)ini;
            while (p->ID != ID - 1)
            {
                p = p->prox;
            }
            p->prox = (ListaDupla *)aux;
        }
    }
}

void EditaElemento(Lista inicio, int novovalor, int ID)
{
    ListaDupla *p = (ListaDupla *)ini;
    while (p->ID != ID)
    {
        p = p->prox;
    }
    p->valor = novovalor;
}
*/
void RemoveElemento(Lista L, int ID)
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
    if (rmv->ID+1 == ((ListaInfo *)L)->length)
    {
        ((ListaInfo *)L)->final = p;
    }
    ((ListaInfo *)L)->length--;
    free(rmv);

    // Ajeita o ID das próximas
    while (p->prox != NULL)
    {
        p = p->prox;
        p->ID--;
    }
}
/*
int BuscaID(Lista inicio, int valor)
{
    int ID;
    ListaDupla *p;
    p = (ListaDupla *)ini;
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

int BuscaValor(Lista inicio, int ID)
{
    int val;
    ListaDupla *p;
    p = (ListaDupla *)ini;
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

void LimpaLista(Lista inicio)
{
    ListaDupla *rmv, *p;
    rmv = *(ListaDupla **)ini;
    p = *(ListaDupla **)ini;
    while (p->prox != NULL)
    {
        p = p->prox;
        free(rmv);
        rmv = p;
    }
    free(rmv);
    *(ListaDupla **)ini = NULL;
}*/
