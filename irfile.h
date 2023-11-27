#ifndef HASHING
#define HASHING
#include "hashtable.h"
#endif
#ifndef STDIO
#define STDIO
#include<stdio.h>
#endif
#ifndef SEMA
#define SEMA
#include "sema.h"
#endif
#ifndef DEBUG_FLAG2
#define DEBUG_FLAG2 0
#endif
enum OpType{
    OP_VARIABLE,
    OP_CONSTANT,
    OP_ADDRESS,
    OP_LABEL,
    OP_ARRAY,
    OP_STRUCT,
    OP_TEMP,
    OP_FUNC
} ;

enum IcType{
    IC_LABEL,
    IC_FUNCTION,
    IC_ASSIGN,
    IC_ASSIGN_ADDR,
    IC_ASSIGN_ADDR_VAL,
    IC_ADDR_ASSIGN_VAL,
    IC_ADD,
    IC_SUB,
    IC_MUL,
    IC_DIV,
    IC_GOTO,
    IC_RELOP_GOTO,
    IC_RETURN,
    IC_DEC,
    IC_ARG,
    IC_CALL,
    IC_PARAM,
    IC_READ,
    IC_WRITE
} ;


struct Operand{
    enum OpType opType;

    union{
        int variableNo;
        int labelNo;
        int val;
        int tempNo;
    } info;
    
    char name[32];
    int vt;//v 0 t 1
    struct TypeNode* type;
    int isParam;
};

struct InterCode{
    enum IcType icType;

    union{
        int labelNo;
        char funcName[32];
        struct {struct Operand* rightOp; struct Operand* leftOp;} assign;
        struct {struct Operand* rightOp; struct Operand* leftOp;} assignAddr;
        struct {struct Operand* rightOp; struct Operand* leftOp;} assignAddrVal;
        struct {struct Operand* result; struct Operand* op1; struct Operand* op2;} binOp;
        int gotoNo;
        struct {struct Operand* leftRelOp; struct Operand* rightRelOp; char relOp[3]; int gotoNo;} relGoto;
        struct Operand* retOp;
        struct {struct Operand* operand; int size;} dec;
        struct Operand* argOp;
        struct {struct Operand* result; char function[32];} funcCall;
        struct Operand* paramOp;
        struct Operand* readOp;
        struct Operand* writeOp;
    } info;
};

struct CodeList{
    struct InterCode* interCode;
    struct CodeList* last;
    struct CodeList* next;
};

struct ArgList{
    struct Operand* args;
    struct ArgList* next;
};

/*
struct Variable{
    char* name;
    struct Operand* operand;
    struct Variable* next;
};*/

struct OperandHashNode{
    char nodeName[NAME_LEN];
    struct Operand* operand;
    struct OperandHashNode* next;
};


struct OperandHashNode* operandTable[HASH_NUM];
int variableNum, labelNum, tempNum;
struct CodeList* codeHead;
struct CodeList* codeTail;
struct Operand* constZero;
struct Operand* constOne;
struct Operand* constFour;

//struct Variable variableHead, variableTail;

extern int hashNumOf(char*); //calculate Hashing num

struct OperandHashNode* operandHashFind(char* name);//find node in table

int operandCheckExist(char* name);//1 exist 0 not

int insertOperandHashNode(char* name,struct Operand* operand); //create hashNode and insert it

struct Operand* lookUpOperand(char* name);//


struct CodeList* startInterCode(struct Node* rootNode);//

void writeIR(struct CodeList* codeList, FILE* pFile);

struct CodeList* trans_ExtDef(struct Node* node);//

struct CodeList* trans_FunDec(struct Node* node);//

struct CodeList* trans_CompSt(struct Node* node);//

struct CodeList* trans_DefList(struct Node* node);//

struct CodeList* trans_Def(struct Node* node);//

struct Operand* trans_Specifier(struct Node* node);//

struct CodeList* trans_DecList(struct Node* node, struct Operand* operand);//

struct CodeList* trans_Dec(struct Node* node, struct Operand* operand);//

struct CodeList* trans_VarDec(struct Node* node, struct Operand* operand);//

struct CodeList* trans_StmtList(struct Node* node);//

struct CodeList* trans_Stmt(struct Node* node);//

struct InterCode* makeCallIc(struct Operand* operand, char* name);//

struct CodeList* copyArray(struct Operand* dest, struct Operand* src);//

struct CodeList* trans_Exp(struct Node* node, struct Operand* operand);//

int sizeOfArray(struct TypeNode* typeNode);//

int isOneArray(struct TypeNode* typeNode);//

struct CodeList* concat(struct CodeList* cl1, struct CodeList* cl2);//

struct CodeList* makeCodeList(struct InterCode* interCode);//

struct Operand* makeConstInt(int val);//

struct InterCode* makeIc(struct Operand* valOperand, struct Operand* leftOperand, struct Operand* rightOperand, enum IcType icType);//

struct InterCode* makeIfIc(char* relOp, struct Operand* operand1, struct Operand* operand2, struct Operand* trueLabel);//

struct InterCode* makeArgIc(struct Operand* arg);//

struct CodeList* trans_Cond(struct Node* node, struct Operand* trueLabel, struct Operand* falseLabel);//

struct CodeList* trans_Args(struct Node* node, struct ArgList** args, struct FieldList* fieldList);//

struct Operand* makeOperand(enum OpType opType);//

void insertIR(struct CodeList* codeList);//

struct CodeList* makeParamCl(struct Operand* operand);//

#define debugPrint(msg) \
        if (DEBUG_FLAG2){ \
            printf("%s\n", msg); \
        }


