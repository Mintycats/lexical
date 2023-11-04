#ifndef HASHING
#define HASHING
#include "hashtable.h"
#endif

#ifndef SYNTAX
#define SYNTAX
#include "syntax.tab.h"
#endif

#ifndef STDIO
#define STDIO
#include<stdio.h>
#endif

extern int yylineno;

extern int lastErrorLine;

extern int hasError;

extern int isNewError(int lineno);

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

void finalCheckFunc();

int checkTypeNode(struct TypeNode* type1, struct TypeNode* type2);//check if type1 == type2

int checkParam(struct FieldList* fl1, struct FieldList* fl2);//check function param

int checkMoreParam(struct FieldList* fl1, struct FieldList* fl2);

int checkSema(struct Node* node);//start sema

void ExtDefList(struct Node* node);//handle ExtDefList

void ExtDef(struct Node* node);//ExtDef

void ExtDecList(struct Node* node, struct TypeNode* typeNode);//

struct TypeNode* Specifier(struct Node* node);

struct Function* FunDec(struct Node* node, struct TypeNode* typeNode, int isDeclare);//

struct FieldList* VarList(struct Node* node);//

void CompSt(struct Node* node, struct TypeNode* typeNode);//block in {}

struct FieldList* DefList(struct Node* node, int isStruct);//

struct FieldList* Def(struct Node* node, int isStruct);

void StmtList(struct Node* node, struct TypeNode* typeNode);//

void Stmt(struct Node* node, struct TypeNode* typeNode);//

struct TypeNode* Exp(struct Node* node);//

struct FieldList* VarDec(struct Node* node, struct TypeNode* typeNode, int isStruct);//

struct TypeNode* StructSpecifier(struct Node* node);

struct FieldList* Dec(struct Node* node, struct TypeNode* typeNode, int isStruct);//

struct FieldList* DecList(struct Node* node, struct TypeNode* typeNode, int isStruct);

struct TypeNode* findFieldList(struct FieldList* fl, char* name);

void initSema();

void semaError(char* type, int lineno, char* msg);

struct FieldList* ParamDec(struct Node* node);

struct FieldList* Args(struct Node* node);
