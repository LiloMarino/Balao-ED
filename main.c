#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "listadupla.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int n, val, pos;
    Lista inicio = NULL;
    inicio = CreateLista(-1);
    AddElemento(inicio, 10);
    AddElemento(inicio, 20);
    AddElemento(inicio, 30);
    AddElemento(inicio, 40);
    AddElemento(inicio, 50);
    RemoveElemento(inicio, 2);
    RemoveElemento(inicio, 2);
    RemoveElemento(inicio, 2);
    InsereElemento(inicio, 40, 2);
    InsereElemento(inicio, 30, 2);
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
        if (n != 1)
            PrintLista(inicio);
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            PrintLista(inicio);
            break;
        case 2:
            printf("Digite o valor:");
            scanf("%d", &val);
            AddElemento(inicio, val);
            break;
        case 3:
            printf("Digite o valor:");
            scanf("%d", &val);
            printf("Digite o ID:");
            scanf("%d", &pos);
            InsereElemento(inicio, val, pos);
            break;
        case 4:
            printf("Digite o ID:");
            scanf("%d", &pos);
            RemoveElemento(inicio, pos);
            break;
        case 5:
            printf("Digite o ID:");
            scanf("%d", &pos);
            val = BuscaValor(inicio, pos);
            printf("Valor: %d\n", val);
            break;
        case 6:
            printf("Digite o valor:");
            scanf("%d", &val);
            pos = BuscaID(inicio, val);
            printf("ID: %d\n", pos);
            break;
        case 7:
            printf("Digite o ID:");
            scanf("%d", &pos);
            printf("Digite o novo valor:");
            scanf("%d", &val);
            EditaElemento(inicio, val, pos);
            break;
        case 8:
            LimpaLista(inicio);
            break;
        case 0:
            break;
        default:
            printf("Não Existe a opção!\n");
            break;
        }

    } while (n != 0);
}