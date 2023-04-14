#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "geo.h"
#include "qry.h"
#include "arqsvg.h"
#include "listadupla.h"
#include "path.h"

int main()
{
    char *args[] = {"./ted", "-e", "/home/lilo/Faculdade/EstruturaDeDados/src", "-f", "02-planta-cidade.geo", "-o", "/home/lilo/Faculdade/EstruturaDeDados/src/logs", "-q", "sobrevoo.qry", NULL};
    int argc = sizeof(args) / sizeof(args[0]) - 1; // O último elemento deve ser NULL
    char *PathInput, *PathOutput, *nomeGeo, *nomeQry, *nomeLog;
    ArgumentosDeComando(&PathInput,&nomeGeo, &PathOutput, &nomeQry,argc, args);
    if (PathInput[strlen(PathInput) - 1] != '/')
    {
        char *PathInput1 = malloc(strlen(PathInput) + 1);
        strcpy(PathInput1, PathInput);
        strcat(PathInput1, "/");
        PathInput = PathInput1;
    }
    if (PathOutput[strlen(PathOutput) - 1] != '/')
    {
        char *PathOutput1 = malloc(strlen(PathOutput) + 1);
        strcpy(PathOutput1, PathOutput);
        strcat(PathOutput1, "/");
        PathOutput = PathOutput1;
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
