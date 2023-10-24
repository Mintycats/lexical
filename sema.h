#ifndef HASHING
#define HASHING
#include "hashtable.h"
#endif

int checkTypeNode(struct TypeNode* type1, struct TypeNode* type2);//check if type1 == type2

int checkParam(struct FieldList* fl1, struct FieldList* fl2);//check function param

int checkFunc(struct Function* func);//check func if it is valid

int checkSema(struct Node* node);//start sema
