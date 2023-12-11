#ifndef IR_FILE
#define IR_FILE
#include "irfile.h"
#endif

struct Register;

struct Variable{
    char name[32];
    struct Register* reg;
    //location
    struct Variable* next;
};

struct Register{
    char name[32];
    struct Variable* vari;
};

void makeRegName(char* dst, int num);
void makeAsm(struct CodeList* codeList, FILE* file);
void initReg();
void ir2Asm(struct InterCode* interCode, FILE* file);
struct Variable* insertVari(struct Operand* operand);
struct Register* getReg(struct Operand* operand);