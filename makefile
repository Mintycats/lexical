parser: main.c lexical.l syntax.y sema.c sema.h hashtable.c hashtable.h
		flex lexical.l
		bison -d syntax.y
		gcc main.c syntax.tab.c sema.c hashtable.c irfile.c -lfl -ly -o parser

clean:  
		rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
		rm -f *.o
