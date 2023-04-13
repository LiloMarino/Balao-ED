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
    int n[1];
    n[0] = 0;
    
    ArqQry B;

    Lista Cir = createLst(-1);
    Lista Ret = createLst(-1);
    Lista Lin = createLst(-1);
    Lista Tex = createLst(-1);

    ArqGeo A = abreLeituraGeo("02-planta-cidade.geo");
    InterpretaGeo(A, Cir, Ret, Tex, Lin);
    OperaSVG(n, Cir, Ret, Tex, Lin);
    fechaGeo(A);

    B = abreLeituraQry("sobrevoo.qry");
    InterpretaQry(B,Cir,Ret,Tex,Lin);
    OperaSVG(n, Cir, Ret, Tex, Lin);
    fechaQry(B);

    killLst(Cir);
    killLst(Ret);
    killLst(Lin);
    killLst(Tex);
}

