#	Makefile for Compiler Construction Assignment 1
#	Robert van Engelen, January 2007
CC=gcc
CPP=g++
LIBS=
COFLAGS=-g
CWFLAGS=-Wall
CIFLAGS=
CMFLAGS=
CFLAGS=$(CWFLAGS) $(COFLAGS) $(CIFLAGS) $(CMFLAGS)

all:		compiler

compiler:	compile.o javaclass.h bytecode.h javaclass.o bytecode.o symbol.o error.o init.o lexer.o
		$(CC) $(CFLAGS) -o compile compile.o javaclass.o bytecode.o symbol.o error.o init.o lexer.o

.c.o:
		$(CC) $(CFLAGS) -c $<
.PHONY: clean distclean
clean:
		rm -f *.o
distclean:
		rm -f calcclass *.o *.class
