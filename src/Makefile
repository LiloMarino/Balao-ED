PROJ_NAME=ted

ALUNO= muriloa
LIBS=-lm 
OBJETOS=$(patsubst %.c,%.o,$(wildcard *.c))

# compilador
CC=gcc

# Flags
CFLAGS= -ggdb -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration -g
LDFLAGS= -O0

$(PROJ_NAME): $(OBJETOS)
	$(CC) -o $(PROJ_NAME) $(LDFLAGS)  $(OBJETOS) $(LIBS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

#
# COLOCAR DEPENDENCIAS DE CADA MODULO
#

# Exemplo: suponha que o arquivo a.c possua os seguintes includes:
#
#   #include "a.h"
#   #include "b.h"
#   #include "c.h"
# 
# a.o: a.h b.h c.h a.c


clean:
	rm -f *.o $(PROJ_NAME)
	rm -rf $(LOGS)

run:
	valgrind --leak-check=full /home/lilo/Faculdade/Balao-ED/src/ted
#
# EMPACOTAR PARA ENTREGA
#
#   -  se necessario: sudo apt install zip

pack: $(PROJ_NAME)
	rm -f ../$(ALUNO).zip
	echo $(ALUNO)
	date >> .entrega
	cd ..; zip $(ALUNO).zip -r src/*.c src/*.h src/Makefile LEIA-ME.txt .entrega
