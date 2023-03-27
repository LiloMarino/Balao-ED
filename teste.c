#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char linha[100];
    char *buf;
    fgets(linha, 100, stdin);
    printf("A linha lida foi: %s %lld", linha,strlen(linha));
    buf = fgets(linha, 100, stdin);
    printf("A linha lida foi: %s %lld", buf,strlen(buf));
}