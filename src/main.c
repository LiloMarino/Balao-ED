#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "geo.h"
#include "qry.h"
#include "arqsvg.h"
#include "listadupla.h"
#include "path.h"

int main(int argc, char **argv)
{
    char *PathInput, *PathOutput, *nomeGeo, *nomeQry, *nomeLog;
    ArgumentosDeComando(&PathInput,&nomeGeo, &PathOutput, &nomeQry,argc, argv);
    if (PathInput[strlen(PathInput) - 1] != '/')
    {
        strcat(PathInput, "/");
    }
    if (PathOutput[strlen(PathOutput) - 1] != '/')
    {
        strcat(PathOutput, "/");
    }
    // EXEMPLO: e- pathe o- patho f- aaa.geo q- bbb.qry
    char *relatorio = ConcatenaNomes(nomeGeo, nomeQry);

    joinFilePath(PathInput,nomeGeo,&nomeGeo);
    joinFilePath(PathInput,nomeQry,&nomeQry);
    joinFilePath(PathOutput,relatorio,&nomeLog);

    Lista Cir = createLst(-1);
    Lista Ret = createLst(-1);
    Lista Lin = createLst(-1);
    Lista Tex = createLst(-1);

    ArqGeo A = abreLeituraGeo(nomeGeo);
    ArqQry B = abreLeituraQry(nomeQry);
    FILE *log = CriaLog(nomeLog);
    
    InterpretaGeo(A, Cir, Ret, Tex, Lin);
    OperaSVG(strcat(nomeLog,"-map"), Cir, Ret, Tex, Lin);
    InterpretaQry(B, Cir, Ret, Tex, Lin,log);
    OperaSVG(nomeLog, Cir, Ret, Tex, Lin);

    fclose(log);
    fechaGeo(A);
    fechaQry(B);

    killLst(Cir);
    killLst(Ret);
    killLst(Lin);
    killLst(Tex);
}
