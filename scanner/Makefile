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
all:		scanner
scanner: symbol.o lextest.o error.o init.o lexer.o
		$(CC) $(CFLAGS) -o lextest symbol.o lextest.o error.o init.o lexer.o
.c.o:
		$(CC) $(CFLAGS) -c $<
.PHONY: clean distclean
clean:
		rm -f *.o
distclean:
		rm -f calcclass *.o *.class
