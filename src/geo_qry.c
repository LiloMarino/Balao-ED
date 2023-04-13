#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "geo.h"
#include "qry.h"
#include "arqsvg.h"
#include "learquivo.h"
#include "listadupla.h"
#include "fila.h"

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
    double x, y, larg, alt, pont;
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
            r->pont = -1;
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
    preparaDecoracao(&deco, 0, r->corb, r->corp, NULL, -1, -1, -1, r->pont);
    escreveRetanguloSvg(fsvg, r->x, r->y, r->larg, r->alt, deco);
}

void CriaCirculoSvg(ArqSvg fsvg, Item info)
{
    Circulo *c = (Circulo *)info;
    char *deco = NULL;
    preparaDecoracao(&deco, 0, c->corb, c->corp, NULL, -1, -1, -1, -1);
    escreveCirculoSvg(fsvg, c->x, c->y, c->raio, deco);
}

void CriaLinhaSvg(ArqSvg fsvg, Item info)
{
    Linha *l = (Linha *)info;
    char *deco = NULL;
    preparaDecoracao(&deco, 0, l->cor, NULL, NULL, -1, -1, -1, -1);
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
    Fila cameras[10]; // Balao tem 10 cameras com capacidade de 15 fotos cada
};

struct StFigura
{
    int ID;
    Item figura;
    float dx, dy;
    char tipo;
};

typedef struct StBalao Balao;
typedef struct StFigura Figura;

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
                    sscanf(linha, "%s %d %f %f %f", comando, &ID, &raio, &prof, &alt);
                    FocoDaFoto(Baloes, ID, raio, prof, alt);
                }
                else if (strcmp(comando, "tf") == 0)
                {
                    char prefix[] = "foto";
                    log = CriaLog(prefix);
                    TiraFoto(Circ, Ret, Tex, Lin, Baloes, ID, log);
                    fclose(log);
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
    for (int i = 0; i < 10; i++)
    {
        b->cameras[i] = createQueue();
    }
    insertLst(Bal, b);
}

void TiraFoto(Lista Circ, Lista Ret, Lista Tex, Lista Lin, Lista Bal, int ID, FILE *log)
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
                if (!isQueueFull(b->cameras[i]))
                {
                    // Foto criada com sucesso
                    insertQueue(b->cameras[i], ProcessaFoto(Circ, Ret, Tex, Lin, ID, b, log));
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

Lista ProcessaFoto(Lista Circ, Lista Ret, Lista Tex, Lista Lin, int ID, Posic Camera, FILE *log)
{
    char forma[] = "T";
    Texto *Bal = (Texto *)ProcuraID(ID, Circ, Ret, Tex, Lin, forma);
    Balao *Cam = (Balao *)Camera;
    fprintf(log, "Foto Tirada\n");
    fprintf(log, "Por Balao ID: %d\n", ID);
    fprintf(log, "Parâmetros da foto\n");
    fprintf(log, "Altitude: %f\n", Cam->alt);
    fprintf(log, "Profundidade: %f\n", Cam->prof);
    fprintf(log, "Raio: %f\n", Cam->raio);
    // Verifica a área da foto e cria um retângulo dela
    Retangulo *r = malloc(sizeof(Retangulo));
    r->ID = 9999;
    r->corb = strdup("#FF0000");
    r->corp = strdup("none");
    r->pont = 5;
    r->x = Bal->x - (Cam->raio);
    r->y = Bal->y + (Cam->prof);
    r->larg = 2 * (Cam->raio);
    r->alt = (Cam->alt);
    Posic Area = insertLst(Ret, r);

    // Verifica quais elementos estão presentes na foto
    Lista C = filter(Circ, VerificaCirculo, Area);
    Lista R = filter(Ret, VerificaRetangulo, Area);
    Lista T = filter(Tex, VerificaTexto, Area);
    Lista L = filter(Lin, VerificaLinha, Area);

    // Produz os dados de registro
    fprintf(log, "Elementos presentes na foto\n");

    Iterador AUX = createIterador(C, false);
    while (!isIteratorEmpty(L, AUX))
    {
        Item item = getIteratorNext(L, AUX);
        fprintf(log, "Circulo ID: %d\n", ((Circulo *)item)->ID);
        fprintf(log, "dx:%f dy:%f\n", fabs(r->x - ((Circulo *)item)->x), fabs(r->y - ((Circulo *)item)->y));
    }
    killIterator(AUX);

    AUX = createIterador(R, false);
    while (!isIteratorEmpty(L, AUX))
    {
        Item item = getIteratorNext(L, AUX);
        fprintf(log, "Retângulo ID: %d\n", ((Retangulo *)item)->ID);
        fprintf(log, "dx:%f dy:%f\n", fabs(r->x - ((Retangulo *)item)->x), fabs(r->y - ((Retangulo *)item)->y));
    }
    killIterator(AUX);

    AUX = createIterador(T, false);
    while (!isIteratorEmpty(L, AUX))
    {
        Item item = getIteratorNext(L, AUX);
        fprintf(log, "Texto ID: %d\n", ((Texto *)item)->ID);
        fprintf(log, "dx:%f dy:%f\n", fabs(r->x - ((Texto *)item)->x), fabs(r->y - ((Texto *)item)->y));
    }
    killIterator(AUX);

    AUX = createIterador(L, false);
    while (!isIteratorEmpty(L, AUX))
    {
        Item item = getIteratorNext(L, AUX);
        fprintf(log, "Linha ID: %d\n", ((Linha *)item)->ID);
        fprintf(log, "dx:%f dy:%f\n", fabs(r->x - ((Linha *)item)->x1), fabs(r->y - ((Linha *)item)->y1));
    }
    killIterator(AUX);

    // Prepara a foto para o armazenamento
    Lista Parte1 = ConcatLst(C, R, "CR", R);
    Lista Parte2 = ConcatLst(Parte1, T, "0T", R);
    Lista Foto = ConcatLst(Parte2, L, "0L", R);
    killLst(C);
    killLst(R);
    killLst(T);
    killLst(L);
    killLst(Parte1);
    killLst(Parte2);
    return Foto;
}

bool VerificaRetangulo(Item info, Posic R)
{
    Retangulo *r = (Retangulo *)info;
    Retangulo *foto = (Retangulo *)getLst(R);
    // Template VerificaPonto(foto->x,,foto->x+foto->larg,foto->y,,foto->y+foto->alt)
    if (VerificaPonto(foto->x, r->x, foto->x + foto->larg, foto->y, r->y, foto->y + foto->alt) || VerificaPonto(foto->x, r->larg, foto->x + foto->larg, foto->y, r->alt, foto->y + foto->alt))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool VerificaCirculo(Item info, Posic R)
{
    Circulo *c = (Circulo *)info;
    Retangulo *foto = (Retangulo *)getLst(R);
    float PYSUP = (c->y) + (c->raio);
    float PYINF = (c->y) - (c->raio);
    float PXDIR = (c->x) + (c->raio);
    float PXESQ = (c->x) - (c->raio);
    if (VerificaPonto(foto->x, c->x, foto->x + foto->larg, foto->y, PYSUP, foto->y + foto->alt) || VerificaPonto(foto->x, c->x, foto->x + foto->larg, foto->y, PYINF, foto->y + foto->alt) || VerificaPonto(foto->x, PXDIR, foto->x + foto->larg, foto->y, c->y, foto->y + foto->alt) || VerificaPonto(foto->x, PXESQ, foto->x + foto->larg, foto->y, c->y, foto->y + foto->alt))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool VerificaTexto(Item info, Posic R)
{
    Texto *t = (Texto *)info;
    Retangulo *foto = (Retangulo *)getLst(R);
    if (VerificaPonto(foto->x, t->x, foto->x + foto->larg, foto->y, t->y, foto->y + foto->alt))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool VerificaLinha(Item info, Posic R)
{
    Linha *l = (Linha *)info;
    Retangulo *foto = (Retangulo *)getLst(R);
    if (VerificaPonto(foto->x, l->x1, foto->x + foto->larg, foto->y, l->y1, foto->y + foto->alt) || VerificaPonto(foto->x, l->x2, foto->x + foto->larg, foto->y, l->y2, foto->y + foto->alt))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool VerificaIntervalo(float Inicio, float P, float Fim)
{
    if ((Inicio <= P) && (P <= Fim))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool VerificaPonto(float Axsup, float Px, float Axinf, float Aysup, float Py, float Ayinf)
{
    if ((VerificaIntervalo(Axsup, Px, Axinf) && VerificaIntervalo(Aysup, Py, Ayinf)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

Lista ConcatLst(Lista L1, Lista L2, char forma[], Posic r)
{
    Lista L3 = createLst(-1);
    // Para a lista L1
    if (!isEmptyLst(L1))
    {
        if (forma[0] != '0')
        {
            if (forma[0] == 'C')
            {
                Figura *F = malloc(sizeof(Figura));
                F->figura = getFirstLst(L1);
                F->dx = fabs(((Retangulo *)r)->x - ((Circulo *)F->figura)->x);
                F->dy = fabs(((Retangulo *)r)->y - ((Circulo *)F->figura)->y);
                F->tipo = 'C';
                F->ID = ((Circulo *)F->figura)->ID;
                insertLst(L3, F);
                while (!isEmptyLst(L1))
                {
                    Figura *F = malloc(sizeof(Figura));
                    F->figura = popLst(L1);
                    F->dx = fabs(((Retangulo *)r)->x - ((Circulo *)F->figura)->x);
                    F->dy = fabs(((Retangulo *)r)->y - ((Circulo *)F->figura)->y);
                    F->tipo = 'C';
                    F->ID = ((Circulo *)F->figura)->ID;
                    insertLst(L3, F);
                    insertLst(L3, F);
                }
            }
            else if (forma[0] == 'R')
            {
                Figura *F = malloc(sizeof(Figura));
                F->figura = getFirstLst(L1);
                F->dx = fabs(((Retangulo *)r)->x - ((Retangulo *)F->figura)->x);
                F->dy = fabs(((Retangulo *)r)->y - ((Retangulo *)F->figura)->y);
                F->tipo = 'R';
                F->ID = ((Retangulo *)F->figura)->ID;
                insertLst(L3, F);
                while (!isEmptyLst(L1))
                {
                    Figura *F = malloc(sizeof(Figura));
                    F->figura = popLst(L1);
                    F->dx = fabs(((Retangulo *)r)->x - ((Retangulo *)F->figura)->x);
                    F->dy = fabs(((Retangulo *)r)->y - ((Retangulo *)F->figura)->y);
                    F->tipo = 'R';
                    F->ID = ((Retangulo *)F->figura)->ID;
                    insertLst(L3, F);
                }
            }
            else if (forma[0] == 'T')
            {
                Figura *F = malloc(sizeof(Figura));
                F->figura = getFirstLst(L1);
                F->dx = fabs(((Retangulo *)r)->x - ((Texto *)F->figura)->x);
                F->dy = fabs(((Retangulo *)r)->y - ((Texto *)F->figura)->y);
                F->tipo = 'T';
                F->ID = ((Texto *)F->figura)->ID;
                insertLst(L3, F);
                while (!isEmptyLst(L1))
                {
                    Figura *F = malloc(sizeof(Figura));
                    F->figura = popLst(L1);
                    F->dx = fabs(((Retangulo *)r)->x - ((Texto *)F->figura)->x);
                    F->dy = fabs(((Retangulo *)r)->y - ((Texto *)F->figura)->y);
                    F->tipo = 'T';
                    F->ID = ((Texto *)F->figura)->ID;
                    insertLst(L3, F);
                }
            }
            else if (forma[0] == 'L')
            {
                Figura *F = malloc(sizeof(Figura));
                F->figura = getFirstLst(L1);
                F->dx = fabs(((Retangulo *)r)->x - ((Linha *)F->figura)->x1);
                F->dy = fabs(((Retangulo *)r)->y - ((Linha *)F->figura)->y1);
                F->tipo = 'L';
                F->ID = ((Linha *)F->figura)->ID;
                insertLst(L3, F);
                while (!isEmptyLst(L1))
                {
                    Figura *F = malloc(sizeof(Figura));
                    F->figura = popLst(L1);
                    F->dx = fabs(((Retangulo *)r)->x - ((Linha *)F->figura)->x1);
                    F->dy = fabs(((Retangulo *)r)->y - ((Linha *)F->figura)->y1);
                    F->tipo = 'L';
                    F->ID = ((Linha *)F->figura)->ID;
                    insertLst(L3, F);
                }
            }
        }
        else
        {
            insertLst(L3, getFirstLst(L1));
            while (!isEmptyLst(L1))
            {
                insertLst(L3, popLst(L1));
            }
        }
    }

    // Para a lista L2
    if (!isEmptyLst(L2))
    {
        if (forma[1] != '0')
        {
            if (forma[1] == 'C')
            {
                Figura *F = malloc(sizeof(Figura));
                F->figura = getFirstLst(L2);
                F->dx = fabs(((Retangulo *)r)->x - ((Circulo *)F->figura)->x);
                F->dy = fabs(((Retangulo *)r)->y - ((Circulo *)F->figura)->y);
                F->tipo = 'C';
                F->ID = ((Circulo *)F->figura)->ID;
                insertLst(L3, F);
                while (!isEmptyLst(L2))
                {
                    Figura *F = malloc(sizeof(Figura));
                    F->figura = popLst(L2);
                    F->dx = fabs(((Retangulo *)r)->x - ((Circulo *)F->figura)->x);
                    F->dy = fabs(((Retangulo *)r)->y - ((Circulo *)F->figura)->y);
                    F->tipo = 'C';
                    F->ID = ((Circulo *)F->figura)->ID;
                    insertLst(L3, F);
                    insertLst(L3, F);
                }
            }
            else if (forma[1] == 'R')
            {
                Figura *F = malloc(sizeof(Figura));
                F->figura = getFirstLst(L2);
                F->dx = fabs(((Retangulo *)r)->x - ((Retangulo *)F->figura)->x);
                F->dy = fabs(((Retangulo *)r)->y - ((Retangulo *)F->figura)->y);
                F->tipo = 'R';
                F->ID = ((Retangulo *)F->figura)->ID;
                insertLst(L3, F);
                while (!isEmptyLst(L2))
                {
                    Figura *F = malloc(sizeof(Figura));
                    F->figura = popLst(L2);
                    F->dx = fabs(((Retangulo *)r)->x - ((Retangulo *)F->figura)->x);
                    F->dy = fabs(((Retangulo *)r)->y - ((Retangulo *)F->figura)->y);
                    F->tipo = 'R';
                    F->ID = ((Retangulo *)F->figura)->ID;
                    insertLst(L3, F);
                }
            }
            else if (forma[1] == 'T')
            {
                Figura *F = malloc(sizeof(Figura));
                F->figura = getFirstLst(L2);
                F->dx = fabs(((Retangulo *)r)->x - ((Texto *)F->figura)->x);
                F->dy = fabs(((Retangulo *)r)->y - ((Texto *)F->figura)->y);
                F->tipo = 'T';
                F->ID = ((Texto *)F->figura)->ID;
                insertLst(L3, F);
                while (!isEmptyLst(L2))
                {
                    Figura *F = malloc(sizeof(Figura));
                    F->figura = popLst(L2);
                    F->dx = fabs(((Retangulo *)r)->x - ((Texto *)F->figura)->x);
                    F->dy = fabs(((Retangulo *)r)->y - ((Texto *)F->figura)->y);
                    F->tipo = 'T';
                    F->ID = ((Texto *)F->figura)->ID;
                    insertLst(L3, F);
                }
            }
            else if (forma[1] == 'L')
            {
                Figura *F = malloc(sizeof(Figura));
                F->figura = getFirstLst(L2);
                F->dx = fabs(((Retangulo *)r)->x - ((Linha *)F->figura)->x1);
                F->dy = fabs(((Retangulo *)r)->y - ((Linha *)F->figura)->y1);
                F->tipo = 'L';
                F->ID = ((Linha *)F->figura)->ID;
                insertLst(L3, F);
                while (!isEmptyLst(L2))
                {
                    Figura *F = malloc(sizeof(Figura));
                    F->figura = popLst(L2);
                    F->dx = fabs(((Retangulo *)r)->x - ((Linha *)F->figura)->x1);
                    F->dy = fabs(((Retangulo *)r)->y - ((Linha *)F->figura)->y1);
                    F->tipo = 'L';
                    F->ID = ((Linha *)F->figura)->ID;
                    insertLst(L3, F);
                }
            }
        }
        else
        {
            insertLst(L3, getFirstLst(L2));
            while (!isEmptyLst(L2))
            {
                insertLst(L3, popLst(L2));
            }
        }
    }
    return L3;
}
