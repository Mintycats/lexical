
%{

    #include<stdio.h>
    #include<string.h>
    #include<lex.yy.c>
    int yylex(void);
    void yyerror(char*);
    /* declared tree node */
    struct Node{
        int todo;
    }
%}

/* declared types */
%union {
    int type_int;
    float type_float;
    string type_string;
    Node type_node;
}

/* declared tokens */
%token <type_int> INT
%token <type_float> FLOAT
%token <type_string> ID TYPE
%token PLUS MINUS STAR DIV
%token SEMI COMMA
%token ASSIGNOP
%token RELOP
%token AND OR NOT
%token DOT
%token LP RP
%token LB RB
%token LC RC
%token <type_string> STRUCT RETURN IF ELSE WHILE
%token <type_node> Program ExtDefList ExtDef Specifier ExtDecList
%token <type_node> FunDec CompSt VarDec StructSpecifier OptTag DefList Tag
%token <type_node> VarList ParamDec CompSt StmtList Stmt Exp DecList Dec Args


/* declared priority */
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right MINUS NOT
%left LP RP LB RB DOT


%%

Program : ExtDefList
        ;

ExtDefList : /* empty */
           | ExtDef ExtDefList
           ;

ExtDef : Specifier ExtDecList SEMI
       | Specifier SEMI
       | Specifier FunDec CompSt
       ;

ExtDecList : VarDec
           | VarDec COMMA ExtDecList
           ;

Specifier : TYPE
          | StructSpecifier
          ;

StructSpecifier : STRUCT OptTag LC DefList RC
                | STRUCT Tag
                ;

OptTag : /* empty */
       | ID
       ;

Tag : ID
    ;

VarDec : ID
       | VarDec LB INT RB
       ;

FunDec : ID LP VarList RP
       | ID LP RP
       ;

VarList : ParamDec COMMA VarList
        | ParamDec
        ;

ParamDec : Specifier VarDec
         ;

CompSt : LC DefList StmtList RC
       ;

StmtList : /* empty */
         | Stmt StmtList
         ;

Stmt : Exp SEMI
     | CompSt
     | RETURN Exp SEMI
     | IF LP Exp RP Stmt
     | IF LP Exp RP Stmt ELSE Stmt
     | WHILE LP Exp RP Stmt
     ;

DefList : /* empty */
        | Def DefList
        ;

Def : Specifier DecList SEMI
    ;

DecList : Dec
        | Dec COMMA DecList
        ;

Dec : VarDec
    | VarDec ASSIGNOP Exp
    ;

Exp : Exp ASSIGNOP Exp
    | Exp AND Exp
    | Exp OR Exp
    | Exp RELOP Exp
    | Exp PLUS Exp
    | Exp MINUS Exp
    | Exp STAR Exp
    | Exp DIV Exp
    | LP Exp RP
    | MINUS Exp
    | NOT Exp
    | ID LP Args RP
    | ID LP RP
    | Exp LB Exp RB
    | Exp DOT ID
    | ID
    | INT
    | FLOAT
    ;

Args : Exp COMMA Args
     | Exp
     ;

%%




