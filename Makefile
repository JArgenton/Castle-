# Diretório de saída
OUTDIR = bin
# Nome do arquivo de saída (executável)
OUTFILE = $(OUTDIR)/program
# Bibliotecas a serem vinculadas
LIBRARIES = -lsfml-graphics -lsfml-window -lsfml-system 
# Compilador a ser usado
CC = g++
# Flags do compilador
CFLAGS = -g -Wall -I./ -Iinclude
# Arquivos fonte
SRCS = $(shell find src -name "*.cpp")
# Arquivos objeto
OBJS = $(SRCS:.cpp=.o)

all: $(OUTFILE)

$(OUTFILE): $(OBJS)
	mkdir -p $(OUTDIR)
	$(CC) -o $(OUTFILE) $(OBJS) $(LIBRARIES)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OUTFILE)

.PHONY: all clean