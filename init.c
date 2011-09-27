
#include "global.h"

struct entry keywords[] =
{ 
	"div", DIV,
	"mod", MOD,
	"begin", BEGIN,
	"do", DO,
	"end", END,
	":=", ASSIGN,
	"if", IF,
	"int8", INT8,
	"int16", INT16,
	"int32", INT32,
	"output", OUTPUT,
	"then", THEN,
	"while", WHILE,
	"eof", DONE,
	0, 0
};

void init()
{ 
	struct entry *p;
	for (p = keywords; p->token; p++)
		insert(p->lexptr, p->token);
}

