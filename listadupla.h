#ifndef LISTADUPLA_H
#define LISTADUPLA_H

#include <stdbool.h>

/**
Uma lista e´ uma colecao ordenada de itens (ou seja, um elemento possui um 
antecessor e um sucessor)  em que seus elementos podem
ser acessados atraves de sua posicao (tipo Posic). 
Uma lista sem nenhum elemento (comprimento 0) e' denominada lista vazia.

Uma instancia do tipo Posic indica a posicao de um item dentro da lista. 
Este tipo possui um valor invalido que indica nao se referir a nenhum item. 
Tal valor invalido e' denotado por NIL.

Este modulo prove diversos iteradores: 1 deles genérico e 3 comuns a linguagens
de programacao funcionais (high-order functions).
*/

typedef void *Lista;
typedef void *Posic;
typedef void *Item;

typedef void *Iterador;
typedef void *Clausura;

#define NIL NULL
#define CAPAC_ILIMITADA -1

/** Retorna uma lista vazia. A lista pode definir um limite maximo de
elementos armazenados (capacidade). Caso capacidade < 0, o tamanho da lista é
ilimitado */
Lista CreateLista(int capacidade);

/* Retorna o numero de elementos da lista. */
int lengthLst(Lista L);

/** Retorna a capacidade da lista. Retorna -1, se a capacidade é ilimitada */
int maxLengthLst(Lista L);

/** Retorna verdadeiro se a lista L estiver vazia */
bool isEmptyLst(Lista L);

/** Retorna verdadeiro se a lista L estiver cheia. Ou seja, se a lista
   tiver sido criada com uma capacidade máxima e lenght(L) == maxLength(L). */
bool isFullLst(Lista L);

/** Remove o elemento da lista L indicado por p.  p deve indicar um elemento existente em L. O comprimento da lista e' diminuido de 1 elemento. */
void RemoveElemento(Lista L, Posic p);

/** Retorna o valor do item da lista indicado por p.
    p deve indicar um elemento existente em L. */
Item getLst(Lista L, Posic p);

/** Insere o item info na posicao imediatamente anterior ao
item indicado por p. O comprimento da lista e' acrescido de 1 elemento.
Retorna um indicador para o elemento acrescentado. p deve indicar um 
elemento existente em L.*/
Posic insertBefore(Lista L,Posic p, Item info);

/** Insere o item info na posicao imediatamente posterior ao
item indicado por p. O comprimento da lista e' acrescido de 1 elemento.
Retorna um indicador para o elemento acrescentado. p deve indicar um 
elemento existente em L.*/
Posic insertAfterLst(Lista L,Posic p, Item info);

/** Retorna o indicador do primeiro elemento de L. Se
length(L)=0, retorna NIL. */
Posic getFirstLst(Lista L);

/** Retorna o indicador do elemento de L seguinte ao elemento
indicado por p. Se p for o ultimo elemento da lista, retorna NIL.
p deve indicar um elemento existente em L.*/
Posic getNextLst(Lista L,Posic p);

/** Retorna o indicador do ultimo elemento de L. Se
length(L)=0, retorna NIL.*/
Posic getLastLst(Lista L);

/** Retorna o indicador do elemento de L anterior ao elemento
indicado por p. Se p for o primeiro elemento da lista, retorna NIL.
p deve indicar um elemento existente em L. */
Posic getPreviousLst(Lista L,Posic p);

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

/*Adiciona o elemento no final da lista e retorna
um indicador para o elemento acrescentado ou NIL,
se a lista estiver cheia.
Exemplo adicionando elemento 10 e o 20:
"Inicio -> NULL"
"Inicio -> 10 -> NULL"
"Inicio -> 10 -> 20 -> NULL"
*/
Posic AddElemento(Lista L, Item info);

/*Insere o elemento na posição definida pelo ID e move
o elemento dessa posição para frente
e retorna falso caso não seja possível adicionar nessa posição
Exemplo inserindo no ID 1 o elemento 15:
"Inicio -> 10 ID:0 -> 20 ID: 1 -> 30 ID: 2 -> NULL"
"Inicio -> 10 ID:0 -> 15 ID: 1 -> 20 ID: 2 -> 30 ID: 3 -> NULL"
*/
bool InsereElemento(Lista L, Item info, int ID);

/*Edita o elemento na posição definida pelo ID
e retorna falso caso não seja possível editar nessa posição
Editando o valor do elemento 20 com ID 1 para 15:
"Inicio -> 10 ID:0 -> 20 ID: 1 -> 30 ID: 2 -> NULL"
"Inicio -> 10 ID:0 -> 15 ID: 1 -> 30 ID: 2 -> NULL"
*/
bool EditaElemento(Lista L, int novovalor, int ID);

/*Retorna o valor da célula com o ID igual ao especificado*/
bool BuscaValor(Lista L, int ID);

/*Retorna o ID da célula com o valor igual ao especificado*/
bool BuscaID(Lista L, Item info);

/*Limpa a lista*/
void LimpaLista(Lista L);

#endif