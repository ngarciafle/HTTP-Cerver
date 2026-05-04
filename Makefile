# Ejemplo básico de Makefile
CC = gcc
CFLAGS = -Iinclude -Wall

mi_programa: src/main.c src/server.c src/parser.c
	$(CC) $(CFLAGS) src/main.c src/server.c src/parser.c -o bin/servidor