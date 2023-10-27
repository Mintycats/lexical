#ifndef HASHING
#define HASHING
#include "hashtable.h"
#endif

int checkTypeNode(struct TypeNode* type1, struct TypeNode* type2);//check if type1 == type2

int checkParam(struct FieldList* fl1, struct FieldList* fl2);//check function param

int checkFunc(struct Function* func);//check func if it is valid

int checkSema(struct Node* node);//start sema

void ExtDefList(struct Node* node);//handle ExtDefList

void ExtDef(struct Node* node);//ExtDef

void ExtDecList(struct Node* node, int type);//int1 float2  global variable

int getSpecifier(struct Node* speci);//int1 float2 struct3

void Specifier(struct Node* node, int type);//int1 float2 struct3

void FunDec(struct Node* node);//

void VarList(struct Node* node);//

void CompSt(struct Node* node, struct TypeNode* typeNode);//block in {}

void DefList(struct Node* node);//

void StmtList(struct Node* node);//

void Stmt(struct Node* node, struct TypeNode* typeNode);//

struct FieldList VarDec();//

void initsema();
