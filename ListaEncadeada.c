#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct cel
{
    int valor;
    int ID;
    struct cel *prox;
};

typedef struct cel celula;

void PrintLista (celula *ini);
void AddElemento (celula **ini, int valor);
void InsereElemento (celula **ini, int valor, int ID);
void EditaElemento (celula *ini, int novovalor, int ID);  //O tipo do novo valor tem que ser o mesmo da vari�vel
void RemoveElemento (celula ** ini, int ID);
int BuscaValor (celula *ini, int ID); //O tipo da função tem que ser o mesmo que o da vari�vel da lista
int BuscaID (celula *ini, int valor);
void LimpaLista (celula **ini);

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int n, val, pos;
    celula *inicio;
    inicio = NULL; // Cria uma lista e aterra
    AddElemento(&inicio,10);
    AddElemento(&inicio,20);
    AddElemento(&inicio,30);
    AddElemento(&inicio,40);
    AddElemento(&inicio,50);
    printf("Digite 1 para ver a lista\n"
           "Digite 2 para adicionar um elemento ao final da lista\n"
           "Digite 3 para inserir um elemento\n"
           "Digite 4 para remover um elemento\n"
           "Digite 5 para buscar um valor na lista\n"
           "Digite 6 para buscar um ID na lista\n"
           "Digite 7 para editar um elemento da lista\n"
           "Digite 8 para limpar a lista\n"
           "Digite 0 para sair\n\n");
    do
    {
        if(n != 1)
            PrintLista(inicio);
        scanf("%d", &n);
        switch(n)
        {
        case 1:
            PrintLista(inicio);
            break;
        case 2:
            printf("Digite o valor:");
            scanf("%d", &val);
            AddElemento(&inicio, val);
            break;
        case 3:
            printf("Digite o valor:");
            scanf("%d", &val);
            printf("Digite o ID:");
            scanf("%d", &pos);
            InsereElemento(&inicio,val,pos);
            break;
        case 4:
            printf("Digite o ID:");
            scanf("%d", &pos);
            RemoveElemento(&inicio,pos);
            break;
        case 5:
            printf("Digite o ID:");
            scanf("%d", &pos);
            val = BuscaValor (inicio,pos);
            printf("Valor: %d\n", val);
            break;
        case 6:
            printf("Digite o valor:");
            scanf("%d", &val);
            pos = BuscaID (inicio,val);
            printf("ID: %d\n", pos);
            break;
        case 7:
            printf("Digite o ID:");
            scanf("%d", &pos);
            printf("Digite o novo valor:");
            scanf("%d", &val);
            EditaElemento(inicio,val,pos);
            break;
        case 8:
            LimpaLista(&inicio);
            break;
        case 0:
            break;
        default:
            printf("N�o Existe a op��o!\n");
            break;
        }

    }
    while(n != 0);

}

void PrintLista(celula *ini)
{
    celula *p;
    printf("\n");
    printf("====== Lista ======\n");
    for (p = ini; p!= NULL; p = p->prox)
        printf("%d ID: %d\n",p->valor,p->ID);
    printf("\n");
}

void AddElemento(celula **ini, int valor)
{

    celula *aux;
    aux = malloc(sizeof(celula));
    aux->valor = valor;
    aux->prox = NULL;
    aux->ID = 0;
    if (*ini == NULL)
    {
        *ini = aux;
    }
    else
    {
        celula *p;
        p = *ini;
        //aux->ID = p->ID++; (Inverte a ordem do ID)
        aux->ID++;
        while(p->prox != NULL)
        {
            p = p->prox;
            //aux->ID = p->ID++; (Inverte a ordem do ID)
            aux->ID++;
        }
        p->prox = aux;
    }

}

void InsereElemento(celula **ini, int valor, int ID)
{
    celula *p;
    p = *ini;
    if(*ini == NULL)
    {
        AddElemento(ini,valor);
    }
    else
    {
        celula *aux;
        aux = malloc(sizeof(celula));
        aux->valor = valor;
        while(p->ID != ID)
        {
            p = p->prox;
        }
        aux->prox = p;
        aux->ID = p->ID;

        //Ajeita o ID das pr�ximas
        p->ID++;
        while(p->prox != NULL)
        {
            p = p->prox;
            p->ID++;
        }

        if(ID == 0)
        {
            *ini = aux;
        }
        else
        {
            p = *ini;
            while(p->ID != ID-1)
            {
                p = p->prox;
            }
            p->prox = aux;
        }
    }
}

void EditaElemento (celula *ini, int novovalor, int ID)
{
    celula *p;
    p = ini;
    while (p->ID != ID)
    {
        p = p->prox;
    }
    p->valor = novovalor;
}

void RemoveElemento (celula ** ini, int ID)
{
    celula *rmv, *p;
    p = *ini;
    rmv = *ini;
    while (rmv->ID != ID)
    {
        rmv = rmv->prox;
    }
    if (ID == 0)
    {
        *ini = rmv->prox;
    }
    else
    {
        while(p->ID != ID-1)
        {
            p = p->prox;
        }
        p->prox = rmv->prox;
    }
    free(rmv);

    //Ajeita o ID das pr�ximas
    while(p->prox != NULL)
    {
        p = p->prox;
        p->ID--;
    }
}

int BuscaID (celula *ini, int valor)
{
    int ID;
    celula *p;
    p = ini;
    while(p->prox != NULL)
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

int BuscaValor (celula *ini, int ID)
{
    int val;
    celula *p;
    p = ini;
    while(p->ID != ID)
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

void LimpaLista (celula **ini)
{
    celula *rmv, *p;
    rmv = *ini;
    p = *ini;
    while(p->prox != NULL)
    {
        p = p->prox;
        free(rmv);
        rmv = p;
    }
    free(rmv);
    *ini = NULL;
}
