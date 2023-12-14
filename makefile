parser: main.c lexical.l syntax.y sema.c sema.h hashtable.c hashtable.h irfile.c irfile.h asm.c asm.h
		flex lexical.l
		bison -d syntax.y
		gcc main.c syntax.tab.c sema.c hashtable.c irfile.c asm.c -lfl -ly -o parser

clean:  
		rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output output.s outIr.ir output.ir
		rm -f *.o
