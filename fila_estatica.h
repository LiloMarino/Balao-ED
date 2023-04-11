#ifndef FILA_ESTATICA_H
#define FILA_ESTATICA_H

#include <stdbool.h>

/**
Uma fila estatica é uma estrutura de dados em que os elementos são inseridos
em uma extremidade e removidos na outra extremidade, seguindo uma política de
FIFO (first in, first out). A implementação é estática, ou seja, o tamanho da
fila é fixo e determinado em tempo de compilação.

Cada fila possui uma capacidade máxima de elementos que pode ser definida no
momento de sua criação. Caso a fila esteja cheia e seja requisitada uma
inserção, a operação falha e retorna false.

Uma fila é composta por um ponteiro para um vetor que armazena seus elementos,
dois índices que apontam para a posição do elemento mais antigo e mais recente
da fila e um contador que guarda o número de elementos atuais na fila.
*/

typedef void *Fila;
typedef void *Item;

#define CAPACIDADE_MAXIMA 15

/** Cria uma nova fila estática com a capacidade máxima especificada. */
Fila criarFila(int capacidade);

/** Insere um novo item no final da fila. Retorna true em caso de sucesso e
false em caso de falha (fila cheia). */
bool inserirFila(Fila fila, Item item);

/** Remove o item mais antigo da fila e o retorna. Se a fila estiver vazia,
retorna NULL. */
Item removerFila(Fila fila);

/** Retorna o número de elementos na fila. */
int tamanhoFila(Fila fila);

/** Retorna true se a fila estiver vazia. */
bool filaVazia(Fila fila);

#endif