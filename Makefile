# ============================================================================
#
# Uso:
#   make        compila e gera o executável "sync_car"
#   make run    compila (se necessário) e executa os testes
#   make clean  remove os .o e o executável
# ============================================================================

# Compilador utilizado
CC = gcc

# Flags de pré-processador:
#   -D_DEFAULT_SOURCE expõe random(), srandom() e usleep() da glibc, que o
#   runner usa e que ficam ocultas quando se compila com -std=c99 estrito.
CPPFLAGS = -D_DEFAULT_SOURCE

# Flags do compilador:
#   -Wall -Wextra  -> ativa avisos úteis
#   -std=c99       -> padrão C99
#   -pthread       -> suporte à biblioteca POSIX Threads
CFLAGS = -Wall -Wextra -std=c99 -pthread

# Flags de linkagem (o -pthread também é necessário aqui)
LDFLAGS = -pthread

# Nome do executável final (exigido pelo trabalho)
TARGET = sync_car

# Arquivos-fonte e seus respectivos objetos (.c -> .o)
SRCS = sync_car.c sync_car-runner.c
OBJS = $(SRCS:.c=.o)

# Alvo padrão: executado ao digitar apenas "make"
all: $(TARGET)

# Linkagem: junta os objetos e gera o executável
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Regra genérica de compilação: cada .c vira um .o
# Depende do sync_car.h para recompilar quando o cabeçalho mudar
%.o: %.c sync_car.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Compila (se preciso) e executa o programa de testes
run test: $(TARGET)
	./$(TARGET)

# Remove arquivos intermediários e o executável
clean:
	rm -f $(OBJS) $(TARGET)

# Alvos que não representam arquivos
.PHONY: all clean run test