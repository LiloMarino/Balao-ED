#include "learquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *ArqCmds;

ArqCmds abreArquivoCmd(char *fn)
{
    ArqCmds ac;
    ac = fopen(fn, "r");
    return ac;
}

bool leLinha(ArqCmds ac, char **buf, int *bufLen)
{
    if (*buf != NULL)
    {
        free(*buf);
        *buf = NULL;
    }
    char linha[300];
    if (!feof(ac))
    {
        fscanf(ac, "%299[^\n]", linha);
        fgetc(ac);
        *buf = malloc((strlen(linha) + 1)*sizeof(char));
        strcpy(*buf, linha);
        char *palavra = strtok(*buf, " ");
        *bufLen = 0;
        while (palavra != NULL)
        {
            *bufLen += 1;
            palavra = strtok(NULL, " ");
        }
        strcpy(*buf, linha);
        return true;
    }
    else
    {
        return false;
    }
}

void getParametroI(char *buf, int i, char **paramI)
{
    if (*paramI != NULL)
    {
        free(*paramI);
        *paramI = NULL;
    }
    char *bufcopia = strdup(buf);
    *paramI = strtok(bufcopia, " ");
    for (int j = 0; j < i; j++)
    {
        *paramI = strtok(NULL, " ");
    }
}

void getParametroDepoisI(char *buf, int i, char **paramI)
{
    if (*paramI != NULL)
    {
        free(*paramI);
        *paramI = NULL;
    }
    char *bufcopia = strdup(buf);
    for (int j = 0; j < i-1; j++)
    {
        if (j == 0)
        {
           *paramI = strtok(bufcopia, " ");
        }
        *paramI = strtok(NULL, " ");
    }
    *paramI = strtok(NULL, "");
}

void fechaArquivoCmd(ArqCmds ac)
{
    fclose(ac);
}