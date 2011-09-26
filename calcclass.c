/*
 *  calcclass.c
 *  
 *  Program to generate calculator class file Calc.class
 *
 *  This program generates a class file for 'example.java':
 *  
 *    import java.lang.*;
 *    public class example
 *    { public static void main(String[] arg)
 *      { int[] val = new int[arg.length];
 *        for (int i = 0; i < arg.length; i++)
 *          val[i] = Integer.parseInt(arg[i]);
 *        int result;
 *        result = val[0] + val[1];
 *        System.out.println(result);
 *      }
 *    }
 *
 *  To build calcclass:
 *  gcc -o calcclass calcclass.c javaclass.c bytecode.c
 *
 *  To generate the class file:
 *  ./calcclass
 *
 *  To disassemble Calc.class:
 *  javap -c Calc
 *
 *  To run Calc.class:
 *  java Calc 1 2
 *
 *  Created by Robert van Engelen on 1/2/05.
 *  Copyright 2005 Robert van Engelen. All rights reserved.
 *
 */

#include "javaclass.h"
#include "bytecode.h"

int main()
{
	struct ClassFile cf;
	int index1, index2, index3;
	int label1, label2;

	// set up new class file structure
	init_ClassFile(&cf);

	// class has public access
	cf.access = ACC_PUBLIC;

	// class name is "Calc"
	cf.name = "Calc";

	// no fields
	cf.field_count = 0;

	// one method
	cf.method_count = 1;

	// allocate array of methods (just one "main" in our example)
	cf.methods = (struct MethodInfo*)malloc(cf.method_count * sizeof(struct MethodInfo));

	// method has public access and is static
	cf.methods[0].access = ACC_PUBLIC | ACC_STATIC;

	// method name is "main"
	cf.methods[0].name = "main";

	// method descriptor of "void main(String[] arg)"
	cf.methods[0].descriptor = "([Ljava/lang/String;)V";

	// max operand stack size of this method
	cf.methods[0].max_stack = 100;

	// the number of local variables in the local variable array
	//   local variable 0 contains "arg"
	//   local variable 1 contains "val"
	//   local variable 2 contains "i" and "result"
	cf.methods[0].max_locals = 3;

	// set up new bytecode buffer
	init_code();
	
	// generate code
/*LOC*/
/*000*/	emit(aload_0);
/*001*/	emit(arraylength);		// arg.length
/*002*/	emit2(newarray, T_INT);
/*004*/	emit(astore_1);			// val = new int[arg.length]
/*005*/	emit(iconst_0);
/*006*/	emit(istore_2);			// i = 0
	label1 = pc;			// label1:
/*007*/	emit(iload_2);
/*008*/	emit(aload_0);
/*009*/	emit(arraylength);
	label2 = pc;
/*010*/	emit3(if_icmpge, PAD);		// if i >= arg.length then goto label2
/*013*/	emit(aload_1);
/*014*/	emit(iload_2);
/*015*/	emit(aload_0);
/*016*/	emit(iload_2);
/*017*/	emit(aaload);			// push arg[i] parameter for parseInt
	index1 = constant_pool_add_Methodref(&cf, "java/lang/Integer", "parseInt", "(Ljava/lang/String;)I");
/*018*/	emit3(invokestatic, index1);	// invoke Integer.parseInt(arg[i])
/*021*/	emit(iastore);			// val[i] = Integer.parseInt(arg[i])
/*022*/	emit32(iinc, 2, 1);		// i++
/*025*/	emit3(goto_, label1 - pc);	// goto label1
	backpatch(label2, pc - label2);	// label2:
/*028*/	emit(aload_1);
/*029*/	emit(iconst_0);
/*030*/	emit(iaload);			// push val[0]
/*031*/	emit(aload_1);
/*032*/	emit(iconst_1);
/*033*/	emit(iaload);			// push val[1]
/*034*/	emit(iadd);			// add
/*035*/	emit(istore_2);			// result = val[0] + val[1]
	index2 = constant_pool_add_Fieldref(&cf, "java/lang/System", "out", "Ljava/io/PrintStream;");
/*036*/	emit3(getstatic, index2);	// get static field System.out of type PrintStream
/*039*/	emit(iload_2);			// push parameter for println()
	index3 = constant_pool_add_Methodref(&cf, "java/io/PrintStream", "println", "(I)V");
/*040*/	emit3(invokevirtual, index3);	// invoke System.out.println(result)
/*043*/	emit(return_);			// return

	// length of bytecode is in the emmiter's pc variable
	cf.methods[0].code_length = pc;
	
	// must copy code to make it persistent
	cf.methods[0].code = copy_code();

	// save class file to "Calc.class"
	save_classFile(&cf);

	return 0;
}
