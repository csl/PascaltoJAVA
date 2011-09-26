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
all:		calcclass Calc
calcclass:	javaclass.h bytecode.h calcclass.c javaclass.o bytecode.o
		$(CC) $(CFLAGS) -o calcclass calcclass.c javaclass.o bytecode.o
Calc:		calcclass
		./calcclass
.c.o:
		$(CC) $(CFLAGS) -c $<
.PHONY: clean distclean
clean:
		rm -f *.o
distclean:
		rm -f calcclass *.o *.class
