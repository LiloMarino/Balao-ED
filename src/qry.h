#ifndef QRY_H
#define QRY_H

/*
 * Conjunto de funções que interpretam arquivos .qry e realizam operações nas figuras lidas pelos arquivos .geo
 */
#include "arqsvg.h"
#include "listadupla.h"
#include "fila.h"

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
void Move(Posic P, float dx, float dy, char forma[], FILE *log);

/*Rotaciona figura texto de identificador i em grs graus*/
void Rotaciona(Posic P, float grs, FILE *log);

/*Define os parâmetros de foco da foto (raio, produndidade, altura) do balão ID*/
void FocoDaFoto(Lista L, int ID, float raio, float prof, float alt);

/*Balão ID tira foto e coloca no final da lista l (0..9)*/
void TiraFoto(Lista Circ, Lista Ret, Lista Tex, Lista Lin, Lista Bal, int ID, FILE *log);

/*Envia fotos da lista L do balão dado pelo ID para a base.
Base categoriza cada foto*/
void PontuaFoto(Lista Bal, int ID, int i, char sfx[]);

/*Recebe a foto e a imprime no SVG*/
void ImprimeFoto(Lista Foto, char sfx[]);

/*Verifica se o tipo da figura do item é igual ao da figura indicada por p*/
bool VerificaTipo(Item item, Posic p);

/*Caça de identificador ID dispara bomba de capacidade capac (A, B ou C) a uma distância
dist. Caso o disparo atinja um balão, clona os elementos contidos nas fotos que não foram
enviadas para base. Os identficadores dos clone começam em j e estão transladados dx
no eixo x. Os clones (quando aplicável) tem suas cores de borda e preenchimento
intercambiadas em relação aos originais.*/
void DisparaCaca(Posic P, char tipo, float dist, int j, float dx);

/*Reporta os dados de todos os balões existentes, incluindo seus atributos e o número
de fotos por fila e a rotação corrente do balão*/
void ReportBalao();

/*Reporta os dados de todos as caças existentes: seus atributos,
a rotação corrente,quantos disparos já efetuou e os
identificadores dos elementos que acertou até o momento.*/
void ReportCaca();

/*Procura o objeto de identificação ID nas 4 listas e retorna a sua posição na lista e seu tipo*/
Posic ProcuraID(int ID, Lista Circ, Lista Ret, Lista Tex, Lista Lin, char forma[]);

/*Elabora os logs dos arquivos em uma pasta log baseado em um prefixo*/
FILE *CriaLog(char prefix[]);

/* Verifica todos os itens dentro da área da foto e cria uma lista contendo eles*/
Lista ProcessaFoto(Lista Circ, Lista Ret, Lista Tex, Lista Lin, int ID, Posic Camera, FILE *log);

/*Verifica se um retangulo está dentro da foto que está sendo tirada pelo balão*/
bool VerificaRetangulo(Item info, Posic R);

/*Verifica se um circulo está dentro da foto que está sendo tirada pelo balão*/
bool VerificaCirculo(Item info, Posic R);

/*Verifica se um texto está dentro da foto que está sendo tirada pelo balão*/
bool VerificaTexto(Item info, Posic R);

/*Verifica se uma linha está dentro da foto que está sendo tirada pelo balão*/
bool VerificaLinha(Item info, Posic R);

/*Verifica se P está dentro do intervalo*/
bool VerificaIntervalo(float Inicio, float P, float Fim);

/*Verifica se o ponto está dentro da área*/
bool VerificaPonto(float Axsup, float Px, float Axinf, float Aysup, float Py, float Ayinf);

/* Concatena a lista de formas 1 com a lista formas 2 */
Lista ConcatLst(Lista L1, Lista L2, char forma[], Posic r);

/*=============================================PARA TESTES======================================================*/
void OperaSVG(char nome[], Lista Circ, Lista Ret, Lista Tex, Lista Lin);

#endif