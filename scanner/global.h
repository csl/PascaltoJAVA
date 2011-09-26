
/**** global.h ****/
#include <stdio.h>
#include <ctype.h>

#define BSIZE 128

#define NONE -1

#define EOS '\0'

#define NUM 256
#define DIV 257
#define MOD 258
#define ID 259
#define DONE 260
#define ASSIGN 261
#define BEGIN  262
#define DO 263
#define END 264
#define IF 265
#define INT8 266
#define INT16 267
#define INT32 268
#define OUTPUT 269
#define THEN 270
#define WHILE 271

int tokenval;
int lineno;

struct entry
{  
	char *lexptr;
	int token;
};

struct entry symtable[];
