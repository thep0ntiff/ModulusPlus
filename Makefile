# Makefile for ModulusPlus project

# Define the compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinc

make all:
	$(CC) $(CFLAGS) -o modulus_plus examples/main.c src/modplus.c