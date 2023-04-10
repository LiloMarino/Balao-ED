#ifndef QRY_H
#define QRY_H

/*
 * Conjunto de funções que interpretam arquivos .qry e realizam operações nas figuras lidas pelos arquivos .geo
 */
#include "arqsvg.h"
#include "listadupla.h"

typedef void *ArqQry;

/*
  Cria o arquivo "fn" para escrita. Substitui o arquivo, caso exista.
  Retorna NULL, caso nao tenha sido possivel criar arquivo.
 */
ArqQry abreLeituraQry(char *fn);

/*A função recebe um arquivo .qry interpreta e opera os elementos das listas*/
void InterpretaQry(ArqQry fqry, Lista Circ, Lista Ret, Lista Tex, Lista Lin);

/* Fecha o arquivo fqry. */
void fechaQry(ArqQry fqry);

/*Move figura/texto de identificador i de dx (no eixo x) e dy (no eixo y)*/
void Move(int ID, float dx, float dy);

/*Rotaciona figura texto de identificador i em grs graus*/
void Rotaciona(int ID, float grs);

/*Define os parâmetros de foco da foto (raio, produndidade, altura) do balão ID*/
void FocoDaFoto(int ID, float raio, float prof, float alt);

/*Balão ID tira foto e coloca no final da lista l (0..9)*/
void TiraFoto(int ID, Lista L);

/*Envia fotos da lista L do balão dado pelo ID para a base.
Base categoriza cada foto*/
void PontuaFoto(int ID, Lista L, ArqSvg sfx);

/*Caça de identificador ID dispara bomba de capacidade capac (A, B ou C) a uma distância
dist. Caso o disparo atinja um balão, clona os elementos contidos nas fotos que não foram
enviadas para base. Os identficadores dos clone começam em j e estão transladados dx
no eixo x. Os clones (quando aplicável) tem suas cores de borda e preenchimento
intercambiadas em relação aos originais.*/
void DisparaCaca(int ID, char tipo, float dist, int j, float dx);

/*Reporta os dados de todos os balões existentes, incluindo seus atributos e o número
de fotos por fila e a rotação corrente do balão*/
void ReportBalao();

/*Reporta os dados de todos as caças existentes: seus atributos,
a rotação corrente,quantos disparos já efetuou e os
identificadores dos elementos que acertou até o momento.*/
void ReportCaca();

#endif