#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "geo.h"
#include "qry.h"
#include "arqsvg.h"
#include "listadupla.h"

/*=============================================PARA TESTES======================================================*/
void OperaSVG(int n[], Lista Circ, Lista Ret, Lista Tex, Lista Lin);

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

void OperaSVG(int n[], Lista Circ, Lista Ret, Lista Tex, Lista Lin)
{
    char nomearq[30];
    sprintf(nomearq, "teste-%d.svg", n[0]);
    n[0]++;

    ArqSvg B = abreEscritaSvg(nomearq);

    Iterador R = createIterador(Ret, false);

    while (!isIteratorEmpty(Ret, R))
        CriaRetanguloSvg(B, getIteratorNext(Ret, R));

    Iterador L = createIterador(Lin, false);

    while (!isIteratorEmpty(Lin, L))
        CriaLinhaSvg(B, getIteratorNext(Lin, L));

    Iterador C = createIterador(Circ, false);

    while (!isIteratorEmpty(Circ, C))
        CriaCirculoSvg(B, getIteratorNext(Circ, C));

    Iterador T = createIterador(Tex, false);

    while (!isIteratorEmpty(Tex, T))
        CriaTextoSvg(B, getIteratorNext(Tex, T));

    killIterator(R);
    killIterator(L);
    killIterator(C);
    killIterator(T);

    fechaSvg(B);
}