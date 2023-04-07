#ifndef GEO_H
#define GEO_H

typedef void *Lista;
typedef void *ArqGeo;

/*
  Cria o arquivo "fn" para escrita. Substitui o arquivo, caso exista.
  Retorna NULL, caso nao tenha sido possivel criar arquivo.
 */
ArqGeo abreLeituraGeo(char *fn);

/*A função recebe o nome de um arquivo .geo interpreta e acrescenta os elementos as listas*/
void InterpretaGeo(ArqGeo fgeo, Lista Circ, Lista Ret, Lista Tex, Lista Lin);

/* Fecha o arquivo fgeo. */
void fechaGeo(ArqGeo fgeo);

#endif