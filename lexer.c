
/**** lexer.c ****/
#include "global.h"

char lexbuf[BSIZE];
int lineno = 1;
int tokenval = NONE;

int lexan()
{
	int t;
	while (1)
	{ 
		t = getchar();
		if (t== ' ' || t == '\t')
		;
		else if (t == '\n')
			lineno = lineno + 1;
		else if (isdigit(t)) {
			ungetc(t, stdin);
			scanf("%d", &tokenval);
			
			if (tokenval <= 127)
				return INT8;
            else if (tokenval <= 32676)
                return INT16;
           	else
                return INT32;
			//return NUM;
		}
		else if (isalpha(t) || t == ':')
		{ 
			int p, b = 0;
			int eq = 0;

		  //ASSIGN
		  if (t == ':')
		  {
		  	t = getchar();
			if (t == '=')
			{
				strcpy(lexbuf, ":=");
				eq = 1;
			}
		  }

		  if (eq == 0)
		  {
			while (isalnum(t))
			{ 
				lexbuf[b] = t;
				t = getchar();
				b = b + 1;
				if (b >= BSIZE)
					error("compiler error");
			}

			lexbuf[b] = EOS;
          }

			if (t != EOF)
				ungetc(t, stdin);

			p = lookup(lexbuf);
			if (p == 0)
			{
				//printf("calling insert ID, %s\n",lexbuf);
				p = insert(lexbuf, ID);
			}
			tokenval = p;
			return symtable[p].token;
		}
		else if (t == EOF)
			return DONE;
		else if (t == '=')
			continue;
		else
		{
			//printf("%c\n", t);
			tokenval = NONE;
			return t;
		}
	}
}

