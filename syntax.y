
%locations
%{

    #include<stdio.h>
    #include<string.h>
    #include<stdarg.h>
    #include<ctype.h>
    #include "lex.yy.c"

    /* declared funcion */
    int yylex(void);
    void yyerror(char*);
    int PrintError(char , int , char*);
    int isNewError(int);

    /* declared tree node */
    enum Nodetype {
        Expression,//a sentance
        Noval,//don't have val
        Val//have val
    };
    enum ValType {
        StringType,
        IntType,
        FloatType,
        NoneType
    };
    struct Node {
        enum Nodetype type;//type of node
        enum ValType valtype;//type of val
        char name[32];
        int lineno;//use for print
        union {//union of value
            int intval;
            float floatval;
            char strval[32];
        };
        struct Node* leftchild;
        struct Node* rightbrother;
    };

    /* declared tree funcion */
    struct Node* MakeNode(char* nodename, enum Nodetype type, int lineno);
    void PrintTree(struct Node* rootnode, int spaceNum);
    void MakeTree(struct Node* father, struct Node* child);
    void TearsDown(struct Node* rootnode);
    
    /* declared global value */
    int hasError = 0;
    int lastErrorLine = 0;
    struct Node* Root = NULL;

    struct Node* debugger = NULL;
    struct Node* debugger2 = NULL;
%}

/* declared types */
%union {
    int type_int;
    float type_float;
    char* type_string;
    struct Node* type_node;
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
%token STRUCT IF ELSE WHILE RETURN
%type <type_node> Program ExtDefList ExtDef Specifier ExtDecList Def
%type <type_node> FunDec CompSt VarDec StructSpecifier OptTag DefList Tag
%type <type_node> VarList ParamDec StmtList Stmt Exp DecList Dec Args


/* declared priority */
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS
%left STAR DIV
%right MINUS NOT
%left LP RP LB RB DOT


%nonassoc LOWER_ELSE
%nonassoc ELSE

%%

Program : ExtDefList {
            $$ = MakeNode("Program", Expression, @$.first_line);
            $$->valtype = NoneType;
            Root = $$;
            MakeTree($$, $1);
            //printf("[Program]:\n");
            //PrintTree(debugger, 0);
          }
        | ExtDefList error {
             if (PrintError('B', @2.first_line, "[Program]: error")){
                struct Node* errorNode = MakeNode("ERROR", Noval, @2.first_line);
                errorNode->valtype = NoneType;
                $$ = MakeNode("Program", Expression, @$.first_line);
                $$->valtype = NoneType;
                MakeTree($$, $1);
                MakeTree($$, errorNode);
             }
             else{
                $$ = NULL;
             }
          }
        ;

ExtDefList : ExtDef ExtDefList {
                $$ = MakeNode("ExtDefList", Expression, @$.first_line);
                $$->valtype = NoneType;
                MakeTree($$, $1);
                MakeTree($$, $2);
             }
           | {$$ = NULL;}
           ;

ExtDef : Specifier ExtDecList SEMI{
            $$ = MakeNode("ExtDef", Expression, @$.first_line);
            $$->valtype = NoneType;
            struct Node* seminode = MakeNode("SEMI", Noval, @3.first_line);
            seminode->valtype = NoneType;
            MakeTree($$, $1);
            MakeTree($$, $2);
            MakeTree($$, seminode);
         }
       | Specifier SEMI{
            $$ = MakeNode("ExtDef", Expression, @$.first_line);
            $$->valtype = NoneType;
            struct Node* seminode = MakeNode("SEMI", Noval, @2.first_line);
            seminode->valtype = NoneType;
            MakeTree($$, $1);
            MakeTree($$, seminode);
         }
       | Specifier FunDec CompSt{
            $$ = MakeNode("ExtDef", Expression, @$.first_line);
            $$->valtype = NoneType;
            MakeTree($$, $1);
            MakeTree($$, $2);
            MakeTree($$, $3);
         }
       ;

ExtDecList : VarDec{
                $$ = MakeNode("ExtDecList", Expression, @$.first_line);
                $$->valtype = NoneType;
                MakeTree($$, $1);
             }
           | VarDec COMMA ExtDecList{
                $$ = MakeNode("ExtDecList", Expression, @$.first_line);
                $$->valtype = NoneType;
                struct Node* commanode = MakeNode("COMMA", Noval, @2.first_line);
                commanode->valtype = NoneType;
                MakeTree($$, $1);
                MakeTree($$, commanode);
                MakeTree($$, $3);
             }
           ;

Specifier : TYPE{
                $$ = MakeNode("Specifier", Expression, @$.first_line);
                $$->valtype = NoneType;
                struct Node* typenode = MakeNode("TYPE", Val, @1.first_line);
                typenode->valtype = StringType;
                strcpy(typenode->strval, $1);
                MakeTree($$, typenode);
            }
          | StructSpecifier{
                $$ = MakeNode("Specifier", Expression, @$.first_line);
                $$->valtype = NoneType;
                MakeTree($$, $1);
            }
          ;

StructSpecifier : STRUCT OptTag LC DefList RC{
                    $$ = MakeNode("StructSpecifier", Expression, @$.first_line);
                    $$->valtype = NoneType;
                    struct Node* structnode = MakeNode("STRUCT", Noval, @1.first_line);
                    structnode->valtype = NoneType;
                    struct Node* lcnode = MakeNode("LC", Noval, @3.first_line);
                    struct Node* rcnode = MakeNode("RC", Noval, @5.first_line);
                    lcnode->valtype = NoneType;
                    rcnode->valtype = NoneType;
                    MakeTree($$, structnode);
                    MakeTree($$, $2);
                    MakeTree($$, lcnode);
                    MakeTree($$, $4);
                    MakeTree($$, rcnode);
                  }
                | STRUCT Tag{
                    $$ = MakeNode("StructSpecifier", Expression, @$.first_line);
                    $$->valtype = NoneType;
                    struct Node* structnode = MakeNode("STRUCT", Noval, @1.first_line);
                    structnode->valtype = NoneType;
                    MakeTree($$, structnode);
                    MakeTree($$, $2);
                  }
                ;

OptTag : ID{
            $$ = MakeNode("OptTag", Expression, @$.first_line);
            $$->valtype = NoneType;
            struct Node* idnode = MakeNode("ID", Val, @1.first_line);
            idnode->valtype = StringType;
            strcpy(idnode->strval, $1);
            MakeTree($$, idnode);
         }
       | { $$ = NULL; }
       ;

Tag : ID{
        $$ = MakeNode("Tag", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* idnode = MakeNode("ID", Val, @1.first_line);
        idnode->valtype = StringType;
        strcpy(idnode->strval, $1);
        MakeTree($$, idnode);
      }
    ;

VarDec : ID{
            $$ = MakeNode("VarDec", Expression, @$.first_line);
            $$->valtype = NoneType;
            struct Node* idnode = MakeNode("ID", Val, @1.first_line);
            idnode->valtype = StringType;
            strcpy(idnode->strval, $1);
            MakeTree($$, idnode);
         }
       | VarDec LB INT RB{
            $$ = MakeNode("VarDec", Expression, @$.first_line);
            $$->valtype = NoneType;
            struct Node* lbnode = MakeNode("LB", Noval, @2.first_line);
            lbnode->valtype = NoneType;
            struct Node* intnode = MakeNode("INT", Val, @3.first_line);
            intnode->valtype = IntType;
            intnode->intval = $3;
            struct Node* rbnode = MakeNode("RB", Noval, @4.first_line);
            rbnode->valtype = NoneType;
            MakeTree($$, $1);
            MakeTree($$, lbnode);
            MakeTree($$, intnode);
            MakeTree($$, rbnode);
         }
       | VarDec LB error RB{
            if (PrintError('B', @3.first_line, "[VarDec]: error []")){
                struct Node* errorNode = MakeNode("ERROR", Noval, @3.first_line);
                errorNode->valtype = NoneType;
                $$ = MakeNode("VarDec", Expression, @$.first_line);
                $$->valtype = NoneType;
                struct Node* lbNode = MakeNode("LB", Noval, @2.first_line);
                lbNode->valtype = NoneType;
                struct Node* rbNode = MakeNode("RB", Noval, @4.first_line);
                rbNode->valtype = NoneType;
                MakeTree($$, $1);
                MakeTree($$, lbNode);
                MakeTree($$, errorNode);
                MakeTree($$, rbNode);
            }
            else{
                $$ = NULL;
            }
         } 
       ;

FunDec : ID LP VarList RP{
           $$ = MakeNode("FunDec", Expression, @$.first_line);
           $$->valtype = NoneType;
           struct Node* idnode = MakeNode("ID", Val, @1.first_line);
           idnode->valtype = StringType;
           strcpy(idnode->strval, $1);
           struct Node* lpnode = MakeNode("LP", Noval, @2.first_line);
           lpnode->valtype = NoneType;
           struct Node* rpnode = MakeNode("RP", Noval, @4.first_line);
           rpnode->valtype = NoneType;
           MakeTree($$, idnode);
           MakeTree($$, lpnode);
           MakeTree($$, $3);
           MakeTree($$, rpnode);
         }
       | ID LP RP{
            $$ = MakeNode("FunDec", Expression, @$.first_line);
            $$->valtype = NoneType;
            struct Node* idnode = MakeNode("ID", Val, @1.first_line);
            idnode->valtype = StringType;
            strcpy(idnode->strval, $1);
            struct Node* lpnode = MakeNode("LP", Noval, @2.first_line);
            lpnode->valtype = NoneType;
            struct Node* rpnode = MakeNode("RP", Noval, @3.first_line);
            rpnode->valtype = NoneType;
            MakeTree($$, idnode);
            MakeTree($$, lpnode);
            MakeTree($$, rpnode);
         }
       ;

VarList : ParamDec COMMA VarList{
            $$ = MakeNode("VarList", Expression, @$.first_line);
            $$->valtype = NoneType;
            struct Node* commanode = MakeNode("COMMA", Noval, @2.first_line);
            commanode->valtype = NoneType;
            MakeTree($$, $1);
            MakeTree($$, commanode);
            MakeTree($$, $3);
          }
        | ParamDec{
            $$ = MakeNode("VarList", Expression, @$.first_line);
            $$->valtype = NoneType;
            MakeTree($$, $1);
          }
        ;

ParamDec : Specifier VarDec{
            $$ = MakeNode("ParamDec", Expression, @$.first_line);
            $$->valtype = NoneType;
            MakeTree($$, $1);
            MakeTree($$, $2);
           }
         ;

CompSt : LC DefList StmtList RC{
            $$ = MakeNode("CompSt", Expression, @$.first_line);
            $$->valtype = NoneType;
            struct Node* lcnode = MakeNode("LC", Noval, @1.first_line);
            lcnode->valtype = NoneType;
            struct Node* rcnode = MakeNode("RC", Noval, @4.first_line);
            rcnode->valtype = NoneType;
            //printf("[CompSt]:\n");
            //PrintTree(debugger, 0);
            MakeTree($$, lcnode);
            MakeTree($$, $2);
            MakeTree($$, $3);
            MakeTree($$, rcnode);
            //printf("[CompSt]:\n");
            //PrintTree(debugger, 0);
         }
       | error RC{
            if (PrintError('B', @1.first_line, "[CompSt]: error \(")){
                struct Node* errorNode = MakeNode("ERROR", Noval, @1.first_line);
                errorNode->valtype = NoneType;
                $$ = MakeNode("CompSt", Expression, @$.first_line);
                $$->valtype = NoneType;
                struct Node* rcNode = MakeNode("RC", Noval, @2.first_line);
                rcNode->valtype = NoneType;
                MakeTree($$, errorNode);
                MakeTree($$, rcNode);
            }
            else{
                $$ = NULL;
            }
         }
       ;

StmtList : Stmt StmtList{
            $$ = MakeNode("StmtList", Expression, @$.first_line);
            $$->valtype = NoneType;
            MakeTree($$, $1);
            MakeTree($$, $2);
           }
         | { $$ = NULL; }
         ;

Stmt : Exp SEMI{
        $$ = MakeNode("Stmt", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* seminode = MakeNode("SEMI", Noval, @2.first_line);
        seminode->valtype = NoneType;
        MakeTree($$, $1);
        MakeTree($$, seminode);
       }
     | CompSt{
        $$ = MakeNode("Stmt", Expression, @$.first_line);
        $$->valtype = NoneType;
        MakeTree($$, $1);
       }
     | RETURN Exp SEMI{
        $$ = MakeNode("Stmt", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* retnode = MakeNode("RETURN", Noval, @1.first_line);
        retnode->valtype = NoneType;
        struct Node* seminode = MakeNode("SEMI", Noval, @3.first_line);
        seminode->valtype = NoneType;
        MakeTree($$, retnode);
        MakeTree($$, $2);
        MakeTree($$, seminode);
       }
     | IF LP Exp RP Stmt %prec LOWER_ELSE{
        $$ = MakeNode("Stmt", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* ifnode = MakeNode("IF", Noval, @1.first_line);
        ifnode->valtype = NoneType;
        struct Node* lpnode = MakeNode("LP", Noval, @2.first_line);
        lpnode->valtype = NoneType;
        struct Node* rpnode = MakeNode("RP", Noval, @4.first_line);
        rpnode->valtype = NoneType;
        MakeTree($$, ifnode);
        MakeTree($$, lpnode);
        MakeTree($$, $3);
        MakeTree($$, rpnode);
        MakeTree($$, $5);
       }
     | IF LP Exp RP Stmt ELSE Stmt{
        $$ = MakeNode("Stmt", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* ifnode = MakeNode("IF", Noval, @1.first_line);
        ifnode->valtype = NoneType;
        struct Node* lpnode = MakeNode("LP", Noval, @2.first_line);
        lpnode->valtype = NoneType;
        struct Node* rpnode = MakeNode("RP", Noval, @4.first_line);
        rpnode->valtype = NoneType;
        struct Node* elsenode = MakeNode("ELSE", Noval, @6.first_line);
        elsenode->valtype = NoneType;
        MakeTree($$, ifnode);
        MakeTree($$, lpnode);
        MakeTree($$, $3);
        MakeTree($$, rpnode);
        MakeTree($$, $5);
        MakeTree($$, elsenode);
        MakeTree($$, $7);
       }
     | WHILE LP Exp RP Stmt{
        $$ = MakeNode("Stmt", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* whinode = MakeNode("WHILE", Noval, @1.first_line);
        whinode->valtype = NoneType;
        struct Node* lpnode = MakeNode("LP", Noval, @2.first_line);
        lpnode->valtype = NoneType;
        struct Node* rpnode = MakeNode("RP", Noval, @4.first_line);
        rpnode->valtype = NoneType;
        MakeTree($$, whinode);
        MakeTree($$, lpnode);
        MakeTree($$, $3);
        MakeTree($$, rpnode);
        MakeTree($$, $5);
       }
     | error SEMI{
        if (PrintError('B', @1.first_line, "[Stmt]: error ;")){
            struct Node* errorNode = MakeNode("ERROR", Noval, @1.first_line);
            errorNode->valtype = NoneType;
            $$ = MakeNode("Stmt", Expression, @$.first_line);
            $$->valtype = NoneType;
            struct Node* semiNode = MakeNode("SEMI", Noval, @2.first_line);
            semiNode->valtype = NoneType;
            MakeTree($$, errorNode);
            MakeTree($$, semiNode);
        }
        else{
            $$ = NULL;
        }
       }
     ;

DefList : Def DefList{
            $$ = MakeNode("DefList", Expression, @$.first_line);
            $$->valtype = NoneType;
            //printf("[DefList]:\n");
            //PrintTree(debugger, 0);
            MakeTree($$, $1);
            MakeTree($$, $2);
            //debugger = $$;
            //printf("[DefList]:\n");
            //PrintTree($1, 0);
            //PrintTree(debugger, 0);
          }
        | { $$ = NULL; }
        ;

Def : Specifier DecList SEMI{
        $$ = MakeNode("Def", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* seminode = MakeNode("SEMI", Noval, @3.first_line);
        seminode->valtype = NoneType;
        /*
        if ($1 != NULL)
            printf("[Def]$1 %s\n", $1->name);
        if ($2 != NULL)
            printf("[Def]$2 %s\n", $2->name);
        */
        MakeTree($$, $1);
        //printf("[Def]child %s\n", $$->leftchild->name);
        MakeTree($$, $2);
        MakeTree($$, seminode);
        //printf("[Def]:\n");
        //PrintTree($$, 0);
        debugger2 = $$;
      }
    ;

DecList : Dec{
            $$ = MakeNode("DecList", Expression, @$.first_line);
            $$->valtype = NoneType;
            MakeTree($$, $1);
          }
        | Dec COMMA DecList{
            $$ = MakeNode("DecList", Expression, @$.first_line);
            $$->valtype = NoneType;
            struct Node* commanode = MakeNode("COMMA", Noval, @2.first_line);
            commanode->valtype = NoneType;
            MakeTree($$, $1);
            MakeTree($$, commanode);
            MakeTree($$, $3);
          }
        ;

Dec : VarDec{
        $$ = MakeNode("Dec", Expression, @$.first_line);
        $$->valtype = NoneType;
        MakeTree($$, $1);
      }
    | VarDec ASSIGNOP Exp{
        $$ = MakeNode("Dec", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* assnode = MakeNode("ASSIGNOP", Noval, @2.first_line);
        assnode->valtype = NoneType;
        MakeTree($$, $1);
        MakeTree($$, assnode);
        MakeTree($$, $3);
      }
    ;

Exp : Exp ASSIGNOP Exp{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* assnode = MakeNode("ASSIGNOP", Noval, @2.first_line);
        assnode->valtype = NoneType;
        MakeTree($$, $1);
        MakeTree($$, assnode);
        MakeTree($$, $3);
      }
    | Exp AND Exp{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* andnode = MakeNode("AND", Noval, @2.first_line);
        andnode->valtype = NoneType;
        MakeTree($$, $1);
        MakeTree($$, andnode);
        MakeTree($$, $3);
      }
    | Exp OR Exp{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* ornode = MakeNode("OR", Noval, @2.first_line);
        ornode->valtype = NoneType;
        MakeTree($$, $1);
        MakeTree($$, ornode);
        MakeTree($$, $3);
      }
    | Exp RELOP Exp{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* relopnode = MakeNode("RELOP", Noval, @2.first_line);
        relopnode->valtype = NoneType;
        MakeTree($$, $1);
        MakeTree($$, relopnode);
        MakeTree($$, $3);
      }
    | Exp PLUS Exp{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* plusnode = MakeNode("PLUS", Noval, @2.first_line);
        plusnode->valtype = NoneType;
        MakeTree($$, $1);
        MakeTree($$, plusnode);
        MakeTree($$, $3);
      }
    | Exp MINUS Exp{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* minnode = MakeNode("MINUS", Noval, @2.first_line);
        minnode->valtype = NoneType;
        MakeTree($$, $1);
        MakeTree($$, minnode);
        MakeTree($$, $3);
      }
    | Exp STAR Exp{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* starnode = MakeNode("STAR", Noval, @2.first_line);
        starnode->valtype = NoneType;
        MakeTree($$, $1);
        MakeTree($$, starnode);
        MakeTree($$, $3);
      }
    | Exp DIV Exp{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* divnode = MakeNode("DIV", Noval, @2.first_line);
        divnode->valtype = NoneType;
        MakeTree($$, $1);
        MakeTree($$, divnode);
        MakeTree($$, $3);
      }
    | LP Exp RP{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* lpnode = MakeNode("LP", Noval, @1.first_line);
        lpnode->valtype = NoneType;
        struct Node* rpnode = MakeNode("RP", Noval, @3.first_line);
        rpnode->valtype = NoneType;
        MakeTree($$, lpnode);
        MakeTree($$, $2);
        MakeTree($$, rpnode);
      }
    | MINUS Exp{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* minnode = MakeNode("MINUS", Noval, @1.first_line);
        minnode->valtype = NoneType;
        MakeTree($$, minnode);
        MakeTree($$, $2);
      }
    | NOT Exp{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* notnode = MakeNode("NOT", Noval, @1.first_line);
        notnode->valtype = NoneType;
        MakeTree($$, notnode);
        MakeTree($$, $2);
      }
    | ID LP Args RP{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* idnode = MakeNode("ID", Val, @1.first_line);
        idnode->valtype = StringType;
        strcpy(idnode->strval, $1);
        struct Node* lpnode = MakeNode("LP", Noval, @2.first_line);
        lpnode->valtype = NoneType;
        struct Node* rpnode = MakeNode("RP", Noval, @4.first_line);
        rpnode->valtype = NoneType;
        MakeTree($$, idnode);
        MakeTree($$, lpnode);
        MakeTree($$, $3);
        MakeTree($$, rpnode);
      }
    | ID LP RP{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* idnode = MakeNode("ID", Val, @1.first_line);
        idnode->valtype = StringType;
        strcpy(idnode->strval, $1);
        struct Node* lpnode = MakeNode("LP", Noval, @2.first_line);
        lpnode->valtype = NoneType;
        struct Node* rpnode = MakeNode("RP", Noval, @3.first_line);
        rpnode->valtype = NoneType;
        MakeTree($$, idnode);
        MakeTree($$, lpnode);
        MakeTree($$, rpnode);
      }
    | Exp LB Exp RB{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* lbnode = MakeNode("LB", Noval, @2.first_line);
        lbnode->valtype = NoneType;
        struct Node* rbnode = MakeNode("RB", Noval, @4.first_line);
        rbnode->valtype = NoneType;
        MakeTree($$, $1);
        MakeTree($$, lbnode);
        MakeTree($$, $3);
        MakeTree($$, rbnode);
      }
    | Exp DOT ID{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* dotnode = MakeNode("DOT", Expression, @2.first_line);
        dotnode->valtype = NoneType;
        struct Node* idnode = MakeNode("ID", Val, @3.first_line);
        idnode->valtype = StringType;
        strcpy(idnode->strval, $3);
        MakeTree($$, $1);
        MakeTree($$, dotnode);
        MakeTree($$, idnode);
      }
    | ID{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* idnode = MakeNode("ID", Val, @1.first_line);
        idnode->valtype = StringType;
        strcpy(idnode->strval, $1);
        MakeTree($$, idnode);
      }
    | INT{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* intnode = MakeNode("INT", Val, @1.first_line);
        intnode->valtype = IntType;
        intnode->intval = $1;
        MakeTree($$, intnode);
      }
    | FLOAT{
        $$ = MakeNode("Exp", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* flonode = MakeNode("FLOAT", Val, @1.first_line);
        flonode->valtype = FloatType;
        flonode->floatval = $1;
        MakeTree($$, flonode);
      }
    | error RP{
        if (PrintError('B', @1.first_line, "Error in Exp")){
            struct Node* errorNode = MakeNode("ERROR", Noval, @1.first_line);
            errorNode->valtype = NoneType;
            $$ = MakeNode("Exp", Expression, @$.first_line);
            $$->valtype = NoneType;
            struct Node* rpNode = MakeNode("RP", Noval, @2.first_line);
            rpNode->valtype = NoneType;
            MakeTree($$, errorNode);
            MakeTree($$, rpNode);
        }
        else{
            $$ = NULL;
        }
      }
    | Exp LB error RB{
        if (PrintError('B', @3.first_line, "[Exp]: []error")){
            struct Node* errorNode = MakeNode("ERROR", Noval, @3.first_line);
            errorNode->valtype = NoneType;
            $$ = MakeNode("Exp", Expression, @$.first_line);
            $$->valtype = NoneType;
            struct Node* lbnode = MakeNode("LB", Noval, @2.first_line);
            lbnode->valtype = NoneType;
            struct Node* rbnode = MakeNode("RB", Noval, @4.first_line);
            rbnode->valtype = NoneType;
            MakeTree($$, $1);
            MakeTree($$, lbnode);
            MakeTree($$, errorNode);
            MakeTree($$, rbnode);
        }
        else{
            $$ = NULL;
        }
      }
    ;

Args : Exp COMMA Args{
        $$ = MakeNode("Args", Expression, @$.first_line);
        $$->valtype = NoneType;
        struct Node* commanode = MakeNode("COMMA", Noval, @2.first_line);
        commanode->valtype = NoneType;
        MakeTree($$, $1);
        MakeTree($$, commanode);
        MakeTree($$, $3);
       }
     | Exp{
        $$ = MakeNode("Args", Expression, @$.first_line);
        $$->valtype = NoneType;
        MakeTree($$, $1);
       }
     ;

%%

void yyerror(char* msg){
    
}

/*
enum Nodetype {
        Expression;//a sentance
        Noval;//don't have val
        Val;//have val
    };
enum ValType {
        StringType;
        IntType;
        FloatType;
        NoneType;
    }
struct Node {
        enum Nodetype type;//type of node
        char[32] name;
        int lineno;//use for print
        union {//union of value
            int intval;
            float floatval;
            char strval;
        };
        struct Node* leftchild;
        struct Node* rightbrother;
    };
*/
struct Node* MakeNode(char* nodename, enum Nodetype type, int lineno){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL)
        printf("ERROR in MakeNode: malloc empty\n");
    strcpy(node->name, nodename);
    node->type = type;
    node->lineno = lineno;
    node->leftchild = NULL;
    node->rightbrother = NULL;
    return node;
}

void MakeTree(struct Node* father, struct Node* child){
    if (father == NULL){
        printf("ERROR in MakeTree: Father is NULL\n");
        return;
    }
    /*if (child == NULL){
        printf("ERROR in MakeTree: child is NULL, whose farther is %s\n", father->name);
        return;
    }*/
    //error report
    
    if (child == NULL)
        return;
    
    if (father->leftchild == NULL)
        father->leftchild = child;
    else{
        struct Node* tmpnode = father->leftchild;
        while (tmpnode->rightbrother != NULL){
            tmpnode = tmpnode->rightbrother;
        }
        tmpnode->rightbrother = child;
    }
}

void PrintSpace(int spaceNum){
    for (int i = 0; i < spaceNum; i++)
        printf(" ");
}

void PrintVal(struct Node* node){
    switch (node->type){
        case Expression:
            printf("%s (%d)\n", node->name, node->lineno);
            break;
        case Noval:
            printf("%s\n", node->name);
            break;
        case Val:
            printf("%s: ", node->name);
            switch (node->valtype){
                case StringType:
                    printf("%s\n", node->strval);
                    break;
                case IntType:
                    printf("%d\n", node->intval);
                    break;
                case FloatType:
                    printf("%f\n", node->floatval);
                    break;
                default:
                    printf("ERROR in PrintVal\n");
            };
            break;
        default:
            printf("ERROR in PrintVal\n");
    };
}

void PrintTree(struct Node* rootnode, int spaceNum){
    if (rootnode == NULL)
        return;
    PrintSpace(spaceNum);
    /*debug*/
    /*
    printf("/*cur:%s", rootnode->name);
    if (rootnode->leftchild != NULL)
        printf(" leftchild:%s ", rootnode->leftchild->name);
    else
        printf(" leftchild:NULL");
    if (rootnode->rightbrother != NULL)
        printf(" rightbrother:%s\n", rootnode->rightbrother->name);
    else
        printf(" rightbrother:NULL\n");
    */
    /*debug*/
    PrintVal(rootnode);
    PrintTree(rootnode->leftchild, spaceNum+1);
    PrintTree(rootnode->rightbrother, spaceNum);
}

int PrintError(char errorType, int lineno, char* msg){
    if (isNewError(lineno)){
        fprintf(stderr, "Error type %c at Line %d: %s.\n", errorType, lineno, msg);
        return 1;
    }
    return 0;
}

void TearsDown(struct Node* rootnode){
    if (rootnode == NULL){
        return;
    }
    TearsDown(rootnode->leftchild);//rec
    TearsDown(rootnode->rightbrother);
    free(rootnode);
}

int isNewError(int lineno){
    if (lastErrorLine != lineno){
        lastErrorLine = lineno;
        hasError = 1;
        return 1;
    }
    return 0;
}
