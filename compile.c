#include "global.h"
#include "javaclass.h"
#include "bytecode.h"

#define MAX_LABEL 255

int debug_on = 1;

#define DBG_MSG(...)    \
    do {    \   
        if(debug_on)    \
        {printf(__VA_ARGS__);}  \
    }while(0);

struct ClassFile cf;

int p = 0;
int index1 = 0;
int index2 = 0;
int index3 = 0;

int nread = 0;

void read_symbol()
{
	if (nread == 0)  
	{
		p = lexan();
	}	               
}

void stmt()
{
	int test = 0;
	int loc = 0;
	int loc1 = 0;
	int var = 0;

	read_symbol();
	switch (p)
	{
		case BEGIN:
				opt_stmts();
				read_symbol();
				if (p == END)
				{
					nread = 0;
					DBG_MSG("end\n");
					return;
				}
				break;
		case ID:
				var = tokenval;
				read_symbol();
				if (p == ASSIGN)
				{	
					nread = 0;
					expr();
					emit3(istore, var);
				}								
				break;
		case IF:
				DBG_MSG("if\n");
				expr();
				emit(iconst_0);
				loc1 = pc;
				emit3(if_icmpeq, 0);

				read_symbol();
				if (p == THEN)
				{
					nread = 0;
					DBG_MSG("then\n");
					stmt();
					backpatch(loc1, pc - loc1);
				}				
				break;
		case WHILE:
				DBG_MSG("while\n");
                test = pc;
				expr();
				emit(iconst_0);
				loc = pc;
				emit3(if_icmpeq, 0);

				read_symbol();
				if (p == DO)
				{
					DBG_MSG("do\n");
					nread = 0;
					stmt();
					emit3(goto_, test - pc);
					backpatch(loc, pc - loc);
				}
				break;
		case OUTPUT:
				DBG_MSG("output\n");
				expr();
				emit(istore_2);
    			index2 = constant_pool_add_Fieldref(&cf, "java/lang/System", "out", "Ljava/io/PrintStream;");
				emit3(getstatic, index2);
				emit(iload_2);
    			index3 = constant_pool_add_Methodref(&cf, "java/io/PrintStream", "println", "(I)V");
				emit3(invokevirtual, index3);
				break;
		  default:
                nread=1;
				break;

	}
}

void opt_stmts()
{
	stmt();
	read_symbol();
	if (p == ';')
	{
		nread = 0;
		opt_stmts();
	}
}

void expr()
{
	term();
	moreterms();
}

void term()
{
	factor();
	morefactors();
}

void morefactors()
{
	read_symbol();
	if (p == '*')
	{
		nread = 0;
		factor();
		emit(imul);
		morefactors();
	}
	else if (p == DIV)
	{	
		DBG_MSG("div\n");
		nread = 0;
		factor();
		emit(idiv);
		morefactors();
	}
	else if (p == MOD)
	{
		DBG_MSG("mod\n");
		nread = 0;
		factor();
		emit(irem);
		morefactors();
	}
	else
	{
		nread = 1;
	}
}

void moreterms()
{
	read_symbol();
	if (p == '+')
	{
		nread=0;
        DBG_MSG("+\n");
		factor();
		emit(iadd);
		moreterms();
	}
	else if (p == '-')
	{
		nread=0;
        DBG_MSG("-\n");
		factor();
		emit(isub);
		moreterms();
	}
	else
	{
		nread = 1;
	}
}

void factor()
{
	read_symbol();
	if (p == '(')
	{
		nread=0;
		expr();
		read_symbol();
		if (p == ')') 
		{
			nread=0;
			return;
		}
		else
			error("syntax error");
	
	}
	else if (p == '-')
	{
		nread=0;
		factor();
		emit(ineg);
	}
	else if (p == INT8)
	{
        DBG_MSG("$INT8 = %d\n", tokenval);
		nread=0;
		emit2(bipush, tokenval);
	}
	else if (p == INT16)
	{
		nread=0;
        DBG_MSG("$INT16 = %d\n", tokenval);
		emit3(sipush, tokenval);
	}
	else if (p == INT32)
	{
		nread=0;
    	index1 = constant_pool_add_Integer(&cf, tokenval);		
        DBG_MSG("$INT32 = %d\n", tokenval);
		emit2(ldc, index1);
	}
	else if (p == ID)
	{
		nread=0;
		emit2(iload, tokenval);
	}
	else if (p == '$')
	{
		nread=0;
		read_symbol();
		if (p == INT8)
		{
			nread=0;
            DBG_MSG("p = %d, $INT8 = %d\n", p, tokenval);
			emit(aload_1);
			emit2(bipush, tokenval);
			emit(iaload);
    		index1 = constant_pool_add_Methodref(&cf, "java/lang/Integer", "parseInt", "(Ljava/lang/String;)I");
			emit3(invokestatic, index1);
			emit(iastore);
		}
	}
	else
	{
		nread = 1;
	}
}

int main()
{
	
    init_ClassFile(&cf);

    cf.access = ACC_PUBLIC;

    cf.name = "Calc";

    cf.field_count = 0;

    cf.method_count = 1;

    cf.methods = (struct MethodInfo*)malloc(cf.method_count * sizeof(struct MethodInfo));

    cf.methods[0].access = ACC_PUBLIC | ACC_STATIC;

    cf.methods[0].name = "main";

    cf.methods[0].descriptor = "([Ljava/lang/String;)V";

    cf.methods[0].max_stack = 127;

    cf.methods[0].max_locals = 127;

    init_code();

    init();

	stmt();

	emit(return_);	

    cf.methods[0].code_length = pc;

    cf.methods[0].code = copy_code();

    save_classFile(&cf);	
}
