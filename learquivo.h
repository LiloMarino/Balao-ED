#ifndef LE_ARQUIVOS__
#define LE_ARQUIVOS__

#include <stdbool.h>
/* EXERCICIO: escrever a descricao do modulo e das operacoes */

typedef void *ArqCmds;

/*Abre um arquivo com tipo não especificado para leitura,
portanto é necessário acrescentar a extensão do arquivo*/
ArqCmds abreArquivoCmd(char *fn);

/*Le uma linha do arquivo e atribui por referência ao ponteiro buf
OBS: tem que dar free(buf) antes de usar a função novamente*/
bool leLinha (ArqCmds ac,char **buf, int *bufLen);

/*Separa os parâmetros da linha delimtados por espaço em várias palavras 
e retorna o parâmetro de índice i no paramI*/
void getParametroI(char *buf, int i, char **paramI);

/*Retorna em paramI todos os parâmetros depois de i
Ex: Casa Amarela Verde
i = 1
*paramI = Amarela Verde*/
void getParametroDepoisI(char *buf, int i, char **paramI);

/*Fecha o arquivo aberto pela função abreArquivoCmd */
void fechaArquivoCmd(ArqCmds ac);

#endif