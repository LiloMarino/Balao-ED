# Nome do projeto
PROJETO = ted

# Arquivos fonte
FONTES = learquivo.c arqsvg.c main.c path.c listadupla.c

# Arquivos objeto
OBJETOS = $(FONTES:.c=.o)

# Compilador e opções de compilação
CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -g 

# Regra padrão
all: $(PROJETO)

# Regra para compilar o projeto
$(PROJETO): $(OBJETOS)
	$(CC) $(OBJETOS) -o $(PROJETO)

# Regra para criar os arquivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP

# Inclui as dependências dos arquivos objeto
-include $(OBJETOS:.o=.d)

# Regra para limpar os arquivos objeto e o executável
clean:
	rm -f $(OBJETOS) $(PROJETO)

.PHONY: clean
