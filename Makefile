# Ejemplo básico de Makefile
CC = gcc
CFLAGS = -Iinclude -Wall

mi_programa: src/main.c src/server.c
	$(CC) $(CFLAGS) src/main.c src/server.c -o bin/servidor