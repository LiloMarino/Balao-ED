#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "leArquivo.h"
#include "listadupla.h"

struct StCirculo
{
    int ID;
    double x, y, raio;
    char *corb, *corp;
};

struct StRetangulo
{
    int ID;
    double x, y, larg, alt;
    char *corb, *corp;
};

struct StLinha
{
    int ID;
    double x1, x2, y1, y2;
    char *cor;
};

struct StTxtStyle
{
    char *fFamily, *fWeight, *fSize;
};

struct StTexto
{
    int ID;
    double x, y;
    char *corb, *corp, *txto;
    char a;
};

typedef struct StCirculo Circulo;
typedef struct StRetangulo Retangulo;
typedef struct StLinha Linha;
typedef struct StTxtStyle EstiloTxt;
typedef struct StTexto Texto;

ArqGeo abreLeituraGeo(char *fn)
{
    ArqGeo fgeo;
    fgeo = fopen(fn, "r");
    return fgeo;
}

void InterpretaGeo(ArqGeo fgeo, Lista Circ, Lista Ret, Lista Tex, Lista Lin)
{
    char comando[3];
    char *linha;
    int *buflen;
    while (leLinha(fgeo, &linha, buflen))
    {
        sscanf(linha, "%s", comando);
        if (strcmp(comando, "c") == 0)
        {
            sscanf(linha, "%s %d %d %d %s %s", comando, &i, &x, &y, corb, corp);
        }
        else if (strcmp(comando, "r") == 0)
        {
            sscanf(linha, "%s %d %d %d %d %s %s", comando, &i, &x, &y, &w, &h, corb, corp);
        }
        else if (strcmp(comando, "l") == 0)
        {
            sscanf(linha, "%s %d %d %d %d %d %s", comando, &i, &x1, &y1, &x2, &y2, corb);
        }
        else if (strcmp(comando, "ts") == 0)
        {
            sscanf(linha, "%s %s %s %d", comando, fFamily, fWeight, &fSize);
        }
        else if (strcmp(comando, "t") == 0)
        {
            sscanf(linha, "%s %d %d %d %s %s %c %[^\n]", comando, &i, &x, &y, corb, corp, &a, txto);
        }
        else
        {
            printf("Comando desconhecido: %s\n", comando);
        }
    }
}

void fechaGeo(ArqGeo fgeo)
{
    fclose(fgeo);
}