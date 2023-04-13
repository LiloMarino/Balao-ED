#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "geo.h"
#include "qry.h"
#include "arqsvg.h"
#include "listadupla.h"

int main()
{
    char nome[50] = "mapa01.svg";
    
    ArqQry B;

    Lista Cir = createLst(-1);
    Lista Ret = createLst(-1);
    Lista Lin = createLst(-1);
    Lista Tex = createLst(-1);

    ArqGeo A = abreLeituraGeo("02-planta-cidade.geo");
    InterpretaGeo(A, Cir, Ret, Tex, Lin);
    OperaSVG(nome, Cir, Ret, Tex, Lin);
    fechaGeo(A);
    strcpy(nome,"mapa02.svg");
    B = abreLeituraQry("sobrevoo.qry");
    InterpretaQry(B,Cir,Ret,Tex,Lin);
    OperaSVG(nome, Cir, Ret, Tex, Lin);
    fechaQry(B);

    killLst(Cir);
    killLst(Ret);
    killLst(Lin);
    killLst(Tex);
}

