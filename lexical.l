%{
     #include "syntax.tab.h"
     int yycolumn = 1;
     #define YY_USER_ACTION \
        yylloc.first_line = yylloc.last_line = yylineno;\
        yylloc.first_column = yycolumn;\
        yylloc.last_column = yycolumn + yyleng - 1;\
        yycolumn += yyleng;
     /*declared funcion*/
     int E2INT(char* text);
     int TS2INT(char* text);
     void JumpALine();
     extern int PrintError(char, int, char*);
     extern int isNewError(int);

     /*declared global*/
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
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return STAR;}
"/" {return DIV;}
";" {return SEMI;}
"," {return COMMA;}
"=" {return ASSIGNOP;}
">" {return RELOP;}
"<" {return RELOP;}
">=" {return RELOP;}
"<=" {return RELOP;}
"==" {return RELOP;}
"!=" {return RELOP;}
"&&" {return AND;}
"||" {return OR;}
"!" {return NOT;}
"(" {return LP;}
")" {return RP;}
"[" {return LB;}
"]" {return RB;}
"{" {return LC;}
"}" {return RC;}
"struct" {return STRUCT;}
"return" {return RETURN;}
"if" {return IF;}
"else" {return ELSE;}
"while" {return WHILE;}
{TYPE} {
        yylval.type_string = strdup(yytext);
        return TYPE;
       }
{INT} {
        yylval.type_int = atoi(yytext);
        return INT;
      }
{EINT} {
        yylval.type_int = E2INT(yytext);
        return INT;
       }
{TSINT} {
        yylval.type_int = TS2INT(&yytext[2]);
        return INT;
        }
{FLOAT} {
        yylval.type_float = atof(yytext);
        return FLOAT;
        }
{ID} {
        yylval.type_string = strdup(yytext);
        return ID;
     }
" " {}
"//" {
        JumpALine();
     }
\n {
    yycolumn = 1;
   }


. {
    PrintError('A', yylineno, "Mysterious character");
  }



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

void JumpALine(){
    char tmpchar = input();
    while (tmpchar != '\n'){
        tmpchar = input();
    }
}

