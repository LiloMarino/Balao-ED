# Nome do projeto
PROJETO = ted

# Arquivos fonte
FONTES = learquivo.c arqsvg.c path.c listadupla.c geo_qry.c main.c 

# Pasta de saída
OUTPUT = output/

# Cria a pasta de saída se ela não existir
$(shell mkdir -p $(OUTPUT))
$(shell cp 02-planta-cidade.geo $(OUTPUT))
$(shell cp foto-dl-gira-atira.qry $(OUTPUT))
$(shell cp foto-gira-atira.qry $(OUTPUT))
$(shell cp gira-atira.qry $(OUTPUT))
$(shell cp sobrevoo.qry $(OUTPUT))

# Arquivos objeto na pasta de saída
OBJETOS = $(addprefix $(OUTPUT), $(FONTES:.c=.o))

# Compilador e opções de compilação
CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -g 

# Regra padrão
all: $(OUTPUT)$(PROJETO)

# Regra para compilar o projeto
$(OUTPUT)$(PROJETO): $(OBJETOS)
	$(CC) $(OBJETOS) -o $@

# Regra para criar os arquivos objeto
$(OUTPUT)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP

# Inclui as dependências dos arquivos objeto
-include $(OBJETOS:.o=.d)

# Regra para limpar os arquivos objeto e o executável
clean:
	rm -rf $(OUTPUT) $(PROJETO)

# Regra para executar o programa com o Valgrind
run:
	valgrind --leak-check=full $(OUTPUT)$(PROJETO)

.PHONY: all clean
