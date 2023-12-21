#ifndef IR_FILE
#define IR_FILE
#include "irfile.h"
#endif

#ifndef DEBUG_FLAG3
#define DEBUG_FLAG3 0
#endif

#define SELF_REG_START1 8
#define SELF_REG_END1 15
#define SELF_REG_START2 24
#define SELF_REG_END2 25

#define CALLEE_START1 16
#define CALLEE_END1 23
#define CALLEE_START2 30
#define CALLEE_END2 30

#define APPLY_SIZE 4096

#define PARAM_BASE 8

#define debugPrint3(msg) \
        if (DEBUG_FLAG3){ \
            printf("%s\n", msg); \
        }

#define SIMPLE_REG

struct Register;

struct Variable{
    struct Operand* op;
    struct Register* reg;
    int offset;
    struct Variable* next;
};

struct Register{
    char name[32];
    struct Variable* vari;
};


void clearReg();
void saveCalleeReg();
void recoverCalleeReg();
struct Variable* makeVari(struct Operand* operand);
struct Variable* findVari(struct Operand* operand);
void makeRegName(char* dst, int num);
void makeAsm(struct CodeList* codeList, FILE* file);
void initReg();
void ir2Asm(struct InterCode* interCode, FILE* file);
struct Variable* insertVari(struct Operand* operand);
struct Register* getReg(struct Operand* operand);