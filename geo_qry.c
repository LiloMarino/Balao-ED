#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "qry.h"
#include "arqsvg.h"
#include "learquivo.h"
#include "listadupla.h"
#include "fila_estatica.h"

/*========================================================================================================== *
 * Funções GEO                                                                                               *
 *========================================================================================================== */

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
    char *a;
    char *rotacao;
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
    char comando[2];
    char *linha = NULL;
    EstiloTxt *style = malloc(sizeof(EstiloTxt));
    style->fFamily = strdup("arial");
    style->fWeight = NULL;
    style->fSize = NULL;
    while (leLinha(fgeo, &linha))
    {
        sscanf(linha, "%s", comando);
        if (strcmp(comando, "c") == 0)
        {
            Circulo *c = malloc(sizeof(Circulo));
            sscanf(linha, "%s %d %lf %lf %lf", comando, &c->ID, &c->x, &c->y, &c->raio);
            c->corb = getParametroI(linha, 5);
            c->corp = getParametroI(linha, 6);
            insertLst(Circ, c);
        }
        else if (strcmp(comando, "r") == 0)
        {
            Retangulo *r = malloc(sizeof(Retangulo));
            sscanf(linha, "%s %d %lf %lf %lf %lf", comando, &r->ID, &r->x, &r->y, &r->larg, &r->alt);
            r->corb = getParametroI(linha, 6);
            r->corp = getParametroI(linha, 7);
            insertLst(Ret, r);
        }
        else if (strcmp(comando, "l") == 0)
        {
            Linha *l = malloc(sizeof(Linha));
            sscanf(linha, "%s %d %lf %lf %lf %lf", comando, &l->ID, &l->x1, &l->y1, &l->x2, &l->y2);
            l->cor = getParametroI(linha, 6);
            insertLst(Lin, l);
        }
        else if (strcmp(comando, "ts") == 0)
        {
            if (style->fFamily != NULL)
            {
                free(style->fFamily);
            }
            if (style->fWeight != NULL)
            {
                free(style->fWeight);
            }
            if (style->fSize != NULL)
            {
                free(style->fSize);
            }
            style->fFamily = getParametroI(linha, 1);
            style->fWeight = getParametroI(linha, 2);
            style->fSize = getParametroI(linha, 3);
        }
        else if (strcmp(comando, "t") == 0)
        {
            Texto *t = malloc(sizeof(Texto));
            sscanf(linha, "%s %d %lf %lf", comando, &t->ID, &t->x, &t->y);
            t->corb = getParametroI(linha, 4);
            t->corp = getParametroI(linha, 5);
            t->a = getParametroI(linha, 6);
            t->txto = getParametroDepoisI(linha, 7);
            t->rotacao = NULL;
            if (style->fFamily != NULL)
            {
                t->fFamily = strdup(style->fFamily);
            }
            else
            {
                t->fFamily = NULL;
            }
            if (style->fWeight != NULL)
            {
                t->fWeight = strdup(style->fWeight);
            }
            else
            {
                t->fWeight = NULL;
            }
            if (style->fSize != NULL)
            {
                t->fSize = strdup(style->fSize);
            }
            else
            {
                t->fSize = NULL;
            }
            insertLst(Tex, t);
        }
        else
        {
            printf("Comando desconhecido: %s\n", comando);
        }
    }
    if (style->fFamily != NULL)
    {
        free(style->fFamily);
    }
    if (style->fWeight != NULL)
    {
        free(style->fWeight);
    }
    if (style->fSize != NULL)
    {
        free(style->fSize);
    }
    free(style);
}

void fechaGeo(ArqGeo fgeo)
{
    fclose(fgeo);
}

void CriaRetanguloSvg(ArqSvg fsvg, Item info)
{
    Retangulo *r = (Retangulo *)info;
    char *deco = NULL;
    preparaDecoracao(&deco, 0, r->corb, r->corp, NULL, -1, -1, -1);
    escreveRetanguloSvg(fsvg, r->x, r->y, r->larg, r->alt, deco);
}

void CriaCirculoSvg(ArqSvg fsvg, Item info)
{
    Circulo *c = (Circulo *)info;
    char *deco = NULL;
    preparaDecoracao(&deco, 0, c->corb, c->corp, NULL, -1, -1, -1);
    escreveCirculoSvg(fsvg, c->x, c->y, c->raio, deco);
}

void CriaLinhaSvg(ArqSvg fsvg, Item info)
{
    Linha *l = (Linha *)info;
    char *deco = NULL;
    preparaDecoracao(&deco, 0, l->cor, NULL, NULL, -1, -1, -1);
    escreveLinhaSvg(fsvg, l->x1, l->y1, l->x2, l->y2, deco);
}

void CriaTextoSvg(ArqSvg fsvg, Item info)
{
    Texto *t = (Texto *)info;
    char *deco = NULL, *fontWeight = NULL, *textAnchor = NULL;
    if (*(t->a) == 'i')
    {
        textAnchor = strdup("start");
    }
    else if (*(t->a) == 'f')
    {
        textAnchor = strdup("end");
    }
    else
    {
        textAnchor = strdup("middle");
    }
    if (t->fWeight != NULL)
    {
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
    }
    preparaDecoracaoTexto(&deco, 0, t->fFamily, NULL, fontWeight, t->fSize, t->corb, t->corp, textAnchor, t->rotacao);
    escreveTextoSvg(fsvg, t->x, t->y, t->txto, deco);
    free(fontWeight);
    free(textAnchor);
}

/*========================================================================================================== *
 * Funções QRY                                                                                               *
 *========================================================================================================== */

struct StBalao
{
    int ID;
    float raio, prof, alt;
    Fila camera[10]; // Balao tem 10 cameras com capacidade de 15 fotos cada
};

typedef struct StBalao Balao;

ArqQry abreLeituraQry(char *fn)
{
    ArqQry fqry;
    fqry = fopen(fn, "r");
    return fqry;
}

void InterpretaQry(ArqQry fqry, Lista Circ, Lista Ret, Lista Tex, Lista Lin)
{
    char comando[2], forma[1];
    int ID;
    char *linha = NULL;
    FILE *log;
    Lista Baloes = createLst(-1);

    while (leLinha(fqry, &linha))
    {
        sscanf(linha, "%s", comando);
        if ((strcmp(comando, "b?") != 0) && (strcmp(comando, "c?") != 0))
        {
            sscanf(linha, "%s %d", comando, &ID);
            Posic p = ProcuraID(ID, Circ, Ret, Tex, Lin, forma);
            if (p != NULL)
            {
                if (strcmp(comando, "mv") == 0)
                {
                    float dx, dy;
                    char prefix[] = "move";
                    log = CriaLog(prefix);
                    sscanf(linha, "%s %d %f %f", comando, &ID, &dx, &dy);
                    Move(p, dx, dy, forma, log);
                    fclose(log);
                }
                else if (strcmp(comando, "g") == 0)
                {
                    float grs;
                    char prefix[] = "rotaciona";
                    log = CriaLog(prefix);
                    sscanf(linha, "%s %d %f", comando, &ID, &grs);
                    Rotaciona(p, grs, log);
                    fclose(log);
                }
                else if (strcmp(comando, "ff") == 0)
                {
                    float prof, raio, alt;
                    FocoDaFoto(Baloes, p, ID, raio, prof, alt);
                }
                else if (strcmp(comando, "tf") == 0)
                {
                }
                else if (strcmp(comando, "df") == 0)
                {
                }
                else if (strcmp(comando, "d") == 0)
                {
                }
                else
                {
                    printf("Comando desconhecido: %s\n", comando);
                }
            }
            else
            {
                printf("ID não encontrado: %d\n", ID);
            }
        }
        else
        {
            if (strcmp(comando, "b?") == 0)
            {
            }
            else if (strcmp(comando, "c?") == 0)
            {
            }
            else
            {
                printf("Comando desconhecido: %s\n", comando);
            }
        }
    }
}

void fechaQry(ArqQry fqry)
{
    fclose(fqry);
}

void Move(Posic P, float dx, float dy, char forma[], FILE *log)
{
    fprintf(log, "Moveu:\n");
    if (forma[0] == 'T')
    {
        Texto *t = (Texto *)P;
        fprintf(log, "Texto\n");
        fprintf(log, "ID: %d\n", t->ID);
        fprintf(log, "De\n");
        fprintf(log, "x:%f y:%f\n", t->x, t->y);
        t->x += dx;
        t->y += dy;
        fprintf(log, "Para\n");
        fprintf(log, "x:%f y:%f\n", t->x, t->y);
    }
    else if (forma[0] == 'C')
    {
        Circulo *c = (Circulo *)P;
        fprintf(log, "Circulo\n");
        fprintf(log, "ID: %d\n", c->ID);
        fprintf(log, "De\n");
        fprintf(log, "x:%f y:%f\n", c->x, c->y);
        c->x += dx;
        c->y += dy;
        fprintf(log, "Para\n");
        fprintf(log, "x:%f y:%f\n", c->x, c->y);
    }
    else if (forma[0] == 'R')
    {
        Retangulo *r = (Retangulo *)P;
        fprintf(log, "Retangulo\n");
        fprintf(log, "ID: %d\n", r->ID);
        fprintf(log, "De\n");
        fprintf(log, "x:%f y:%f\n", r->x, r->y);
        r->x += dx;
        r->y += dy;
        fprintf(log, "Para\n");
        fprintf(log, "x:%f y:%f\n", r->x, r->y);
    }
    else if (forma[0] == 'L')
    {
        Linha *l = (Linha *)P;
        fprintf(log, "Linha\n");
        fprintf(log, "ID:%d\n", l->ID);
        fprintf(log, "De\n");
        fprintf(log, "x1:%f y1:%f x2:%f y2:%f\n", l->x1, l->y1, l->x2, l->y2);
        l->x1 += dx;
        l->y1 += dy;
        l->x2 += dx;
        l->y2 += dy;
        fprintf(log, "Para\n");
        fprintf(log, "x1:%f y1:%f x2:%f y2:%f\n", l->x1, l->y1, l->x2, l->y2);
    }
    else
    {
        return;
    }
}

void Rotaciona(Posic P, float grs, FILE *log)
{
    char rotacao[30];
    float rot;
    Texto *t = (Texto *)P;
    fprintf(log, "Rotacionou:\n");
    fprintf(log, "ID: %d\n", t->ID);
    fprintf(log, "De:\n");
    if (t->rotacao != NULL)
    {
        char *token = strtok(t->rotacao, " ");
        rot = atof(token);
    }
    else
    {
        rot = 0;
    }
    fprintf(log, "Graus: %f°\n", rot);
    rot += grs;
    fprintf(log, "Para:\n");
    fprintf(log, "Graus: %f°\n", rot);
    sprintf(rotacao, "%f %f %f", rot, t->x, t->y);
    t->rotacao = strdup(rotacao);
}

void FocoDaFoto(Lista Bal, int ID, float raio, float prof, float alt)
{
    // Procura o balão na lista Bal
    Iterador B = createIterador(Bal, false);
    while (!isIteratorEmpty(Bal, B))
    {
        Balao *b = (Balao *)getIteratorNext(Bal, B);
        if (b->ID == ID)
        {
            b->alt = alt;
            b->prof = prof;
            b->raio = raio;
            return;
        }
    }

    // O balão ainda não foi criado na lista
    Balao *b = (Balao *)malloc(sizeof(Balao));
    b->ID = ID;
    b->alt = alt;
    b->prof = prof;
    b->raio = raio;
    for (int i; i < 10, i++)
    {
        b->fotos[i] = criarFila(15);
    }
    insertLst(Bal, b);
}

void TiraFoto(Lista Bal, int ID)
{
    // Procura o balão na lista Bal
    Iterador B = createIterador(Bal, false);
    while (!isIteratorEmpty(Bal, B))
    {
        Balao *b = (Balao *)getIteratorNext(Bal, B);
        if (b->ID == ID)
        {
            for (int i = 0; i < 10; i++)
            {
                if (inserirFila(b->fotos[i],ProcessaFoto()))
                { 
                    // Foto criada com sucesso
                    return;
                }
            }
            // Limite de fotos atingido
            return;
        }
    }
    // Não existe o balão na lista então não tem foto
    return;
}

Posic ProcuraID(int ID, Lista Circ, Lista Ret, Lista Tex, Lista Lin, char forma[])
{
    Iterador T = createIterador(Tex, false);
    Iterador C = createIterador(Circ, false);
    Iterador R = createIterador(Ret, false);
    Iterador L = createIterador(Lin, false);
    while (!isIteratorEmpty(Tex, T))
    {
        Texto *t = (Texto *)getIteratorNext(Tex, T);
        if (t->ID == ID)
        {
            killIterator(T);
            killIterator(C);
            killIterator(R);
            killIterator(L);
            forma[0] = 'T';
            return t;
        }
    }
    while (!isIteratorEmpty(Circ, C))
    {
        Circulo *c = (Circulo *)getIteratorNext(Circ, C);
        if (c->ID == ID)
        {
            killIterator(T);
            killIterator(C);
            killIterator(R);
            killIterator(L);
            forma[0] = 'C';
            return c;
        }
    }
    while (!isIteratorEmpty(Ret, R))
    {
        Retangulo *r = (Retangulo *)getIteratorNext(Ret, R);
        if (r->ID == ID)
        {
            killIterator(T);
            killIterator(C);
            killIterator(R);
            killIterator(L);
            forma[0] = 'R';
            return r;
        }
    }
    while (!isIteratorEmpty(Lin, L))
    {
        Linha *l = (Linha *)getIteratorNext(Lin, L);
        if (l->ID == ID)
        {
            killIterator(T);
            killIterator(C);
            killIterator(R);
            killIterator(L);
            forma[0] = 'L';
            return l;
        }
    }
    return NULL;
}

FILE *CriaLog(char prefix[])
{
    char nomearq[50];
    int n = 1;
    sprintf(nomearq, "logs/%s-log%d.txt", prefix, n);

    // Verifica se o arquivo já existe
    while (fopen(nomearq, "r") != NULL)
    {
        n++;
        sprintf(nomearq, "logs/%s-log%d.txt", prefix, n);
    }

    // Cria o arquivo com o nome gerado
    FILE *arq = fopen(nomearq, "w");
    if (arq == NULL)
    {
        printf("Erro ao criar arquivo de log!\n");
        exit(1);
    }

    return arq;
}
