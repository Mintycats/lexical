#ifndef ASM
#define ASM
#include "asm.h"
#endif



//global variable
struct Register* reg[32];
struct Variable* allVari = NULL;

void makeRegName(char* dst, int num){
    int index = 0;
    dst[index] = 'r';
    index++;
    if (num < 10){
        dst[index] = (num + '0');
        index++;
        dst[index] = '\0';
        return;
    }
    dst[index + 1] = ((num % 10) + '0');
    num = num / 10;
    dst[index] = ((num % 10) + '0');
    index += 2;
    dst[index] = '\0';
}

void initReg(){
    for (int i = 0; i < 32; i++){
        reg[i] = (struct Register*)malloc(sizeof(struct Register));
        makeRegName(reg[i]->name, i);
        reg[i]->vari = NULL;
    }
}

void ir2Asm(struct InterCode* interCode, FILE* file){
    if (interCode->icType == IC_LABEL){
        fprintf(file, "%d:\n", interCode->info.labelNo);
        return;
    }
    if (interCode->icType == IC_ASSIGN){
        if (interCode->info.assign.rightOp->opType == OP_CONSTANT){//x := #k
            
        }
    }
}

void makeAsm(struct CodeList* codeList, FILE* file){
    if (file == NULL)
        return;
    //save global string
    fprintf(file, ".data\n_prompt: .asciiz \"Enter an integer:\"\n_ret: .asciiz \"\\n\"\n.global main\n.text\n");
    //define read
    fprintf(file, "\nread:\n");
    fprintf(file, "\tli $v0, 4\n");
    fprintf(file, "\tla $a0, _prompt\n");
    fprintf(file, "\tsyscall\n");
    fprintf(file, "\tli $v0, 5\n");
    fprintf(file, "\tsyscall\n");
    fprintf(file, "\tjr $ra\n");
    //define write
    fprintf(file, "\nwrite:\n");
    fprintf(file, "\tli $v0, 1\n");
    fprintf(file, "\tsyscall\n");
    fprintf(file, "\tli $v0, 4\n");
    fprintf(file, "\tla $a0, _ret\n");
    fprintf(file, "\tsyscall\n");
    fprintf(file, "\tmove $v0, $0\n");
    fprintf(file, "\tjr $ra\n\n");
    //init register
    initReg();
    //start write asm
    struct CodeList* tmpCl = codeList;
    while (tmpCl != NULL){
        ir2Asm(tmpCl->interCode, file);
        tmpCl = tmpCl->next;
    }
}












