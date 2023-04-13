#ifndef GEO_H
#define GEO_H

/*
 * Conjunto de funções que interpretam arquivos .geo e criam figuras svg a partir dele
 */
#include "listadupla.h"
#include "arqsvg.h"

typedef void *ArqGeo;

/*
  Cria o arquivo "fn" para escrita. Substitui o arquivo, caso exista.
  Retorna NULL, caso nao tenha sido possivel criar arquivo.
 */
ArqGeo abreLeituraGeo(char *fn);

/*A função recebe um arquivo .geo interpreta e acrescenta os elementos as listas*/
void InterpretaGeo(ArqGeo fgeo, Lista Circ, Lista Ret, Lista Tex, Lista Lin);

/* Fecha o arquivo fgeo. */
void fechaGeo(ArqGeo fgeo);

/*Interpreta o item dado pela lista e cria no arquivo svg o retângulo*/
void CriaRetanguloSvg(ArqSvg fsvg, Item info);

/*Interpreta o item dado pela lista e cria no arquivo svg o circulo*/
void CriaCirculoSvg(ArqSvg fsvg, Item info);

/*Interpreta o item dado pela lista e cria no arquivo svg a linha*/
void CriaLinhaSvg(ArqSvg fsvg, Item info);

/*Interpreta o item dado pela lista e cria no arquivo svg o texto*/
void CriaTextoSvg(ArqSvg fsvg, Item info);

#endif