%{
     #include<stdio.h>
     #include<string.h>
     int E2INT(char* text);
     int TS2INT(char* text);

%}

%option yylineno

digit [0-9]
digits {digit}+
letter [_a-zA-Z]
letters {letter}+
INT 0|[1-9][0-9]*
EINT 0[0-7]*
TSINT 0[xX][0-9A-Fa-f]+
FLOAT {INT}\.{digits}|{digit}*\.{digit}*[Ee][\+\-]?{digits}
ID {letters}[_a-zA-Z0-9]*

SEMI ;
COMMA ,
ASSIGNOP =
RELOP >|<|>=|<=|==|!=
PLUS +
MINUS -
STAR *
DIV /
AND &&
OR \|\|
DOT \.
NOT !
TYPE int|float
LP (
RP )
LB \[
RB \]
LC \{
RC \}
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while
EOF <<EOF>>

%%
"+" {printf("+");}
"-" {printf("-");}
"*" {printf("*");}
"/" {printf("/");}
";" {printf(";");}
"," {printf(",");}
"=" {printf("=");}
">" {printf(">");}
"<" {printf("<");}
">=" {printf(">=");}
"<=" {printf("<=");}
"==" {printf("==");}
"!=" {printf("!=");}
"&&" {printf("&&");}
"||" {printf("||");}
"!" {printf("!");}
"(" {printf("(");}
")" {printf(")");}
"[" {printf("[");}
"]" {printf("]");}
"{" {printf("{");}
"}" {printf("}");}
"struct" {printf("struct");}
"return" {printf("return");}
"if" {printf("if");}
"else" {printf("else");}
"while" {printf("while");}
{TYPE} {printf("%s", yytext);}
{INT} {printf("%s", yytext);}
{EINT} {printf("%d", E2INT(yytext));}
{TSINT} {printf("%d", TS2INT(&yytext[2]));}
{FLOAT} {printf("%s", yytext);}
{ID} {printf("%s", yytext);}
" " {printf(" ");}

\n {printf("\n");}


. {fprintf(stderr, "Error type A at line %d: Mysterious character \'%s\'\n", yylineno, yytext);}



%%

int LocalPow(int bnum, int expnum){// bnum*bnum****bnum
     int ansnum = 1;
     for (int i = 0; i < expnum; i++){
          ansnum = ansnum * bnum;
     }
     return ansnum;
}

int E2INT(char* text){
     int cnt = 0;
     for (cnt = 0; text[cnt] != '\0'; cnt++);
     cnt -= 1;
     int num = 0;
     for (int exp = 0; exp <= cnt; exp++){
             num = num + LocalPow(8, exp) * (text[cnt-exp]-'0');
     }
     return num;
}

int TS2INT(char* text){
     int cnt = 0;
     for (cnt = 0; text[cnt] != '\0'; cnt++)
          ;
     cnt -= 1;
     int num = 0;
     for (int exp = 0; exp <= cnt; exp++){
	  int fnum = 0;
	  int index = cnt-exp;
          if (text[index] >= '0' && text[index] <= '9'){
	          fnum = text[index] - '0';
  	  }
	  else if (text[index] >= 'A' && text[index] <= 'F'){
	       fnum = (text[index] - 'A') + 10;
	  }
  	  else{
	       printf("TS2INT ERROR\n");
	       return 0;
     	  }
  	  num = num + LocalPow(16, exp) * fnum;
     }
     return num;
}


