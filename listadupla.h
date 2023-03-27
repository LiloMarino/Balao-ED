#ifndef _LISTADUPLA_H
#define _LISTADUPLA_H

typedef struct StListaDupla ListaDupla;
typedef struct StInfoLista ListaInfo;

typedef void *Lista;
typedef void *Posic;
typedef void *Item;
typedef void *Iterador;
typedef void *Clausura;

#define NIL NULL;
#define CAPAC_ILIMITADA -1

/* Retorna uma lista vazia. A lista pode definir um limite maximo de
elementos armazenados (capacidade). Caso capacidade < 0, o tamanho da lista é
ilimitado */
Lista CreateLista(int capacidade);

/* Retorna o numero de elementos da lista. */
int LengthLista(Lista L);

/*Imprime a lista no terminal mostrando seus valores e IDs
Exemplo:
====== Lista ======
10 ID: 0
20 ID: 1
30 ID: 2
40 ID: 3
50 ID: 4
*/
void PrintLista(Lista L);

/*Adiciona o elemento no final da lista
Exemplo adicionando elemento 10 e o 20:
"Inicio -> NULL"
"Inicio -> 10 -> NULL"
"Inicio -> 10 -> 20 -> NULL"
*/
void AddElemento(Lista L, int valor);

/*Insere o elemento na posição definida pelo ID e move
o elemento dessa posição para frente
Exemplo inserindo no ID 1 o elemento 15:
"Inicio -> 10 ID:0 -> 20 ID: 1 -> 30 ID: 2 -> NULL"
"Inicio -> 10 ID:0 -> 15 ID: 1 -> 20 ID: 2 -> 30 ID: 3 -> NULL"
*/
void InsereElemento(Lista L, int valor, int ID);

/*Edita o elemento na posição definida pelo ID
Editando o valor do elemento 20 com ID 1 para 15:
"Inicio -> 10 ID:0 -> 20 ID: 1 -> 30 ID: 2 -> NULL"
"Inicio -> 10 ID:0 -> 15 ID: 1 -> 30 ID: 2 -> NULL"
*/
void EditaElemento(Lista L, int novovalor, int ID);

/*Remove o elemento na posição definida pelo ID
Removendo elemento com ID = 1:
"Inicio -> 10 ID:0 -> 20 ID: 1 -> 30 ID: 2 -> NULL"
"Inicio -> 10 ID:0 -> 30 ID: 1 -> NULL"
*/
void RemoveElemento(Lista L, int ID);

/*Retorna o valor da célula com o ID igual ao especificado*/
int BuscaValor(Lista L, int ID);

/*Retorna o ID da célula com o valor igual ao especificado*/
int BuscaID(Lista L, int valor);

/*Limpa a lista*/
void LimpaLista(Lista L);

#endif