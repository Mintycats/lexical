#ifndef IR_FILE
#define IR_FILE
#include "irfile.h"
#endif

#ifndef DEBUG_FLAG3
#define DEBUG_FLAG3 1
#endif

#define SELF_REG_START1 8
#define SELF_REG_END1 15
#define SELF_REG_START2 24
#define SELF_REG_END2 25

#define debugPrint3(msg) \
        if (DEBUG_FLAG3){ \
            printf("%s\n", msg); \
        }

#define SIMPLE_REG

struct Register;

struct Variable{
    struct Operand* op;
    struct Register* reg;
    //location
    int offset;
    struct Variable* next;
};

struct Register{
    char name[32];
    struct Variable* vari;
};

void clearReg();
struct Variable* makeVari(struct Operand* operand);
struct Variable* findVari(struct Operand* operand);
void makeRegName(char* dst, int num);
void makeAsm(struct CodeList* codeList, FILE* file);
void initReg();
void ir2Asm(struct InterCode* interCode, FILE* file);
struct Variable* insertVari(struct Operand* operand);
struct Register* getReg(struct Operand* operand);