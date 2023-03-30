#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listadupla.h"

int main()
{
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
    PrintLista(inicio);
}