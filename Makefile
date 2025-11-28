# Variáveis de compilação
CC = gcc
CFLAGS = -Wall -std=c99 -I./headers
LDFLAGS = -lm

# Arquivos de origem
SRC = src/main.c src/casamentoExato.c src/frequencia.c src/comandos.c src/centralControle.c src/casamentoAproximado.c

# Nome do executável
EXEC = programa

# Alvo padrão
all: $(EXEC)

# Como criar o executável diretamente
$(EXEC): $(SRC)
	$(CC) $(SRC) -o $(EXEC) $(CFLAGS) $(LDFLAGS)

# Limpar arquivos compilados
clean:
	rm -f $(EXEC)

# Alvo para rodar o programa
run: $(EXEC)
	./$(EXEC)
