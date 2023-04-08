#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "arqsvg.h"
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
    char *corb, *corp, *txto, *fFamily, *fWeight, *fSize;
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
    char *linha = NULL;
    int *buflen = NULL;
    EstiloTxt *style = malloc(sizeof(EstiloTxt));
    style->fFamily = NULL;
    style->fWeight = NULL;
    style->fSize = NULL;
    while (leLinha(fgeo, &linha, buflen))
    {
        sscanf(linha, "%s", comando);
        if (strcmp(comando, "c") == 0)
        {
            Circulo *c = malloc(sizeof(Circulo));
            sscanf(linha, "%s %d %lf %lf %lf %s %s", comando, &c->ID, &c->x, &c->y, &c->raio, c->corb, c->corp);
            insertLst(Circ, c);
        }
        else if (strcmp(comando, "r") == 0)
        {
            Retangulo *r = malloc(sizeof(Retangulo));
            sscanf(linha, "%s %d %lf %lf %lf %lf %s %s", comando, &r->ID, &r->x, &r->y, &r->larg, &r->alt, r->corb, r->corp);
            insertLst(Ret, r);
        }
        else if (strcmp(comando, "l") == 0)
        {
            Linha *l = malloc(sizeof(Linha));
            sscanf(linha, "%s %d %lf %lf %lf %lf %s", comando, &l->ID, &l->x1, &l->y1, &l->x2, &l->y2, l->cor);
            insertLst(Lin, l);
        }
        else if (strcmp(comando, "ts") == 0)
        {
            sscanf(linha, "%s %s %s %s", comando, style->fFamily, style->fWeight, style->fSize);
        }
        else if (strcmp(comando, "t") == 0)
        {
            Texto *t = malloc(sizeof(Texto));
            sscanf(linha, "%s %d %lf %lf %s %s %c %[^\n]", comando, &t->ID, &t->x, &t->y, t->corb, t->corp, &t->a, t->txto);
            t->fFamily = style->fFamily;
            t->fWeight = style->fWeight;
            t->fSize = style->fSize;
            insertLst(Tex, t);
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

void CriaRetanguloSvg(ArqSvg fsvg, Item info)
{
    Retangulo *r = (Retangulo *)info;
    char *deco = NULL;
    preparaDecoracao(deco, 0, r->corb, r->corp, NULL, -1, -1, -1);
    escreveRetanguloSvg(fsvg, r->x, r->y, r->larg, r->alt, deco);
    free(deco);
}

void CriaCirculoSvg(ArqSvg fsvg, Item info)
{
    Circulo *c = (Circulo *)info;
    char *deco = NULL;
    preparaDecoracao(deco, 0, c->corb, c->corp, NULL, -1, -1, -1);
    escreveCirculoSvg(fsvg, c->x, c->y, c->raio, deco);
    free(deco);
}

void CriaLinhaSvg(ArqSvg fsvg, Item info)
{
    Linha *l = (Linha *)info;
    char *deco = NULL;
    preparaDecoracao(deco, 0, NULL, l->cor, NULL, -1, -1, -1);
    escreveLinhaSvg(fsvg, l->x1, l->y1, l->x2, l->y2, deco);
    free(deco);
}

void CriaTextoSvg(ArqSvg fsvg, Item info)
{
    Texto *t = (Texto *)info;
    char *deco = NULL, *fontWeight, *textAnchor;
    if (t->a == 'i')
    {
        textAnchor = strdup("start");
    }
    else if (t->a == 'f')
    {
        textAnchor = strdup("end");
    }
    else
    {
        textAnchor = strdup("middle");
    }

    if (strcmp(t->fWeight, "l") == 0)
    {
        fontWeight = strdup("lighter");
    }
    else if (strcmp(t->fWeight, "b") == 0)
    {
        fontWeight = strdup("bold");
    }
    else if (strcmp(t->fWeight, "b+") == 0)
    {
        fontWeight = strdup("bolder");
    }
    else
    {
        fontWeight = strdup("normal");
    }
    preparaDecoracaoTexto(deco, 0, t->fFamily, NULL, fontWeight, t->fSize, t->corb, t->corp, textAnchor);
    escreveTextoSvg(fsvg, t->x, t->y, t->txto, deco);
    free(fontWeight);
    free(textAnchor);
    free(deco);
}
