#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "geo.h"
#include "arqsvg.h"
#include "listadupla.h"

int main()
{
    ArqSvg B = abreEscritaSvg("teste");
    ArqGeo A = abreLeituraGeo("02-planta-cidade.geo");

    Lista Cir = createLst(-1);
    Lista Ret = createLst(-1);
    Lista Lin = createLst(-1);
    Lista Tex = createLst(-1);

    InterpretaGeo(A, Cir, Ret, Tex, Lin);

    Iterador J = createIterador(Ret, false);

    while (!isIteratorEmpty(Ret, J))
        CriaRetanguloSvg(B, getIteratorNext(Ret, J));

    Iterador F = createIterador(Lin, false);

    while (!isIteratorEmpty(Lin, F))
        CriaLinhaSvg(B, getIteratorNext(Lin, F));

    Iterador K = createIterador(Cir, false);

    while (!isIteratorEmpty(Cir, K))
        CriaCirculoSvg(B, getIteratorNext(Cir, K));

    Iterador Z = createIterador(Tex, false);

    while (!isIteratorEmpty(Tex, Z))
        CriaTextoSvg(B, getIteratorNext(Tex, Z));

    killIterator(J);
    killIterator(F);
    killIterator(K);
    killIterator(Z);

    killLst(Cir);
    killLst(Ret);
    killLst(Lin);
    killLst(Tex);

    fechaSvg(B);
    fechaGeo(A);
    return 0;
}