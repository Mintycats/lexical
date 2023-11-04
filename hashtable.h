#ifndef DEBUG_FLAG
#define DEBUG_FLAG 0
#endif

#ifndef HASH_NUM
#define HASH_NUM 1024
#endif

#ifndef NAME_LEN
#define NAME_LEN 32
#endif

#ifndef STRING
#define STRING
#include <string.h>
#endif

#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

//declare struct type
struct TypeNode;

struct FieldList{
    char name[NAME_LEN];
    struct TypeNode* type;
    struct FieldList* next;
};

struct Structure{
    char name[NAME_LEN];
    struct FieldList* domain;
};

struct Function{
    char name[NAME_LEN];
    int lineno;
    struct TypeNode* type;
    struct FieldList* param;
};

struct TypeNode{
    enum {
        VARIABLE,
        ARRAY,
        STRUCTURE,
        FUNCTION
    } type;
    union {
        int variable;// int1 float2
        struct {
            int size;
            struct TypeNode* type;
        } array;
        struct Structure* structure;
        struct Function* function;
    } info;
    enum {
        LEFT,
        RIGHT,
        BOTH
    } assignType;
};


struct HashNode{
    char nodeName[NAME_LEN];
    struct TypeNode* type;
    struct HashNode* next;
};

//declare global
struct HashNode* hashTable[HASH_NUM];
struct HashNode* funcTable[HASH_NUM];

//declare function

extern int hashNumOf(char*); //calculate Hashing num

extern struct HashNode* hashFind(char*);//find node in table

extern int checkExist(char*);//1 exist 0 not

extern int insertHashNode(char*,struct TypeNode*); //create hashNode and insert it

extern int insertFuncNode(char*, struct TypeNode*);//func declare

extern int checkFuncExist(char*);

extern struct HashNode* funcFind(char* key);

extern void removeFunc(char*);
