#include "lista.h"
#include <stdlib.h>

struct StNode{
  struct StNode *prox, *ant;
  Item info;
};

struct StLista{
  struct StNode *prim, *ult;
  int capac;
  int length;
};

typedef struct StLista ListaImpl;
typedef struct StNode Node;


struct StIterator{
  Node *curr;
  bool reverso;
};

typedef struct StIterator IteratorImpl;

Lista createLista(int capacidade){
  ListaImpl *newLista = (ListaImpl *) malloc (sizeof(ListaImpl));
  newLista->prim = NULL;
  newLista->ult = NULL;
  newLista->capac = capacidade;
  newLista->length = 0;
}

int length(Lista L){
  ListaImpl *lst = ( ListaImpl *)L;
  return lst->length;
}


int maxLength(Lista L){
  ListaImpl *lst = ( ListaImpl *)L;
  return lst->capac;
}


bool isEmpty(Lista L){
  ListaImpl *lst = ( ListaImpl *)L;
  return lst->length == 0;
}


bool isFull(Lista L){
  ListaImpl *lst = ( ListaImpl *)L;
  return lst->length == lst->capac;
}

Posic insert(Lista L, Item info){
  ListaImpl *lst = ( ListaImpl *)L;
  Node *newNode = (Node *) malloc (sizeof(Node));
  newNode->info = info;
  newNode->prox = NULL;
  
  if (isEmpty(L)){
    lst->prim = newNode;
  }
  else{
    lst->ult->prox = newNode;
  }
    
  newNode->ant = lst->ult;
  lst->ult = newNode;
    lst->length++;
}

Item pop(Lista L){
  ListaImpl *lst = (ListaImpl *)L;
  Item item = lst->prim->info;
  Node *paux;
  paux = lst->prim;
  lst->prim = paux->prox;

  if(paux->prox == NULL){
    // lista vai ficar vazia
    lst->ult = NULL;
  }
  else{
    paux->prox->ant = NULL;
  }

  lst->length--;
  free(paux);
  return item;
}

void removeLista(Lista L, Posic p){
  ListaImpl *lst = (ListaImpl *)L;
}


Item get(Lista L, Posic p){
  ListaImpl *lst = ( ListaImpl *)L;
}

Posic getNext(Lista L,Posic p){
  ListaImpl *lst = ( ListaImpl *)L;
  
}

Posic getPrevious(Lista L,Posic p){
  ListaImpl *lst = ( ListaImpl *)L;
  
}

/*
 * Iterador
 */

 Item getIteratorNext(Lista L, Iterador it){
   IteratorImpl *itimpl = (IteratorImpl *)it;
   Item valor =itimpl->curr->info
   if (itimpl->reverso){
     itimpl->curr = (Node *)getPrevious(L,itimpl->curr);
   }
   else{
     itimpl->curr = (Node *)getNext(L,itimpl->curr);
   }
   return valor;
 }

 /*
  * High-order functions
  */
 
 Lista map(Lista L,Apply f){
    ListaImpl *lst = ( ListaImpl *)L;
    ListaImpl *nova = (ListaImpl *)createLista(lst->capac);
    Item novoItem;

    for (Node *curr = lst->prim; curr != NULL; curr = curr->prox){
      novoItem = f(curr->info);
      insert(nova,novoItem);
    }

    return nova;
 }

void fold(Lista L, ApplyClosure f, Clausura c){
  ListaImpl *lst = ( ListaImpl *)L;
  Item novoItem;

  for (Node *curr = lst->prim; curr != NULL; curr = curr->prox){
    f(curr->info,c);
  }
  
}