%{
     #include<stdio.h>
     #include<string.h>

%}

%option yylineno

digit [0-9]
digits {digit}+
letter [_a-zA-Z]
letters {letter}+
INT {digits}
FLOAT {digits}?\.?{digits}
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
TYPE {int}|{float}
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
"." {printf(".");}
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
"int" {printf("int");}
"float" {printf("float");}
{INT} {printf("%s", yytext);}
{FLOAT} {printf("%s", yytext);}
{ID} {printf("%s", yytext);}
" " {printf(" ");}



. {printf("Error type A at Line %d: Mysterious characters \'%s\'\n", yylineno, yytext);}


%%

int main(int argc, char* argv[]){
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}



