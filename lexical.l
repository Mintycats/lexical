%{   
     #include "syntax.tab.h"
     int yycolumn = 1;
     #define YY_USER_ACTION \
        yylloc.first_line = yylloc.last_line = yylineno;\
        yylloc.first_column = yycolumn;\
        yylloc.last_column = yycolumn + yyleng - 1;\
        yycolumn += yyleng;
     /*declared funcion*/
     void textDealer();
     int E2INT(char* text);
     int TS2INT(char* text);
     void JumpALine();
     extern int PrintError(char, int, char*);
     extern int isNewError(int);
     extern void ErrorPrinter(char, char*);

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
FLOAT {digit}*\.{digits}|{digits}\.|({digit}*\.{digits}|{digits}\.)[Ee][\+\-]?{digits}

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
OR ||
DOT .
NOT !
TYPE int|float
LP (
RP )
LB [
RB ]
LC {
RC }
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while
del [ \t\r]
EOF <<EOF>>
UNDEFINE [_a-zA-Z0-9]*

%%
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return STAR;}
"//" {
        if (isNewError(yylineno)){
            fprintf(stdout, "Error type B at Line %d: [jump]\n", yylineno);
        }
        JumpALine();
     }
"/*" {
        if (isNewError(yylineno)){
            fprintf(stdout, "Error type B at Line %d: [jump]\n", yylineno);
        }
        textDealer();
     }
"*/" {
        if (isNewError(yylineno)){
            fprintf(stdout, "Error type B at Line %d: [jump]\n", yylineno);
        }
        JumpALine();
     }
"/" {return DIV;}
";" {return SEMI;}
"," {return COMMA;}
"." {return DOT;}
"=" {return ASSIGNOP;}
">" {yylval.type_string = strdup(yytext);return RELOP;}
"<" {yylval.type_string = strdup(yytext);return RELOP;}
">=" {yylval.type_string = strdup(yytext);return RELOP;}
"<=" {yylval.type_string = strdup(yytext);return RELOP;}
"==" {yylval.type_string = strdup(yytext);return RELOP;}
"!=" {yylval.type_string = strdup(yytext);return RELOP;}
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
        //printf("[lexical INT]:%s\n", yytext);
        yylval.type_int = atoi(yytext);
        return INT;
      }
{FLOAT} {
            //printf("[FLOAT]%s\n", yytext);
            yylval.type_float = atof(yytext);
            return FLOAT;
        }
{ID} {
        //printf("[lexical ID]:%s\n", yytext);
        yylval.type_string = strdup(yytext);
        return ID;
     }


\n {
        yycolumn = 1;
   }

{del} { }

{UNDEFINE} {
            ErrorPrinter('B', "[UNDEFINE]");
            }

. {
     ErrorPrinter('A', "[default]");
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

void textDealer(){//jump through text
    char lastChar;
    while (1){
        lastChar = input();
        ErrorPrinter('B', "[textDealer]");
        if (lastChar == '*' && input() == '/'){
            ErrorPrinter('B', "[textDealer]");
            JumpALine();
            return;
        }
    }
}

