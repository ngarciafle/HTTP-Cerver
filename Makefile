# Ejemplo básico de Makefile
CC = gcc
CFLAGS = -Iinclude -Wall

all: create_bin mi_programa

mi_programa: src/main.c src/server.c src/proxy.c
	$(CC) $(CFLAGS) src/main.c src/server.c src/proxy.c -o bin/servidor 

clean:
	rm ./bin/servidor

create_bin:
	mkdir -p bin