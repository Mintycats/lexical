#ifndef ASM
#define ASM
#include "asm.h"
#endif



//global variable
struct Register* reg[32];
struct Variable* allVari = NULL;
int offset = 0;

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
            struct Register* reg = getReg(interCode->info.assign.leftOp);
            fprintf(file, "\tli %s, %d\n", reg->name, interCode->info.assign.rightOp->info.val);
            //assign regVal to stack
            //todo
            return;
        }
        if (interCode->info.assign.rightOp->opType != OP_CONSTANT){//x := y
            struct Register* reg1 = getReg(interCode->info.assign.leftOp);
            struct Register* reg2 = getReg(interCode->info.assign.rightOp);
            fprintf(file, "\tmove %s, %s\n", reg1->name, reg2->name);
            //assign regVal to stack
            //todo
            return;
        }
    }
    if (interCode->icType == IC_ADD || interCode->icType == IC_SUB){
        if (interCode->info.binOp.op2->opType == OP_CONSTANT){//x := y op #k
            struct Register* regVal = getReg(interCode->info.binOp.result);
            struct Register* regOp = getReg(interCode->info.binOp.op1);
            if (interCode->icType == IC_ADD){
                fprintf(file, "\taddi %s, %s, %d\n",regVal->name, regOp->name, interCode->info.binOp.op2->info.val);
                //save regVal
                //todo
                return;
            }
            if (interCode->icType == IC_SUB){
                fprintf(file, "\taddi %s, %s, -%d\n", regVal->name, regOp->name, interCode->info.binOp.op2->info.val);
                //save val
                //todo
                return;
            }
        }
        if (interCode->info.binOp.op2->opType != OP_CONSTANT){//x := y op z
            struct Register* regRes = getReg(interCode->info.binOp.result);
            struct Register* regOp1 = getReg(interCode->info.binOp.op1);
            struct Register* regOp2 = getReg(interCode->info.binOp.op2);
            if (interCode->icType == IC_ADD){
                fprintf(file, "\tadd %s, %s, %s\n", regRes->name, regOp1->name, regOp2->name);
                //save
                //todo
                return;
            }
            if (interCode->icType == IC_SUB){
                fprintf(file, "\tsub %s, %s, %s\n", regRes->name, regOp1->name, regOp2->name);
                //todo
                return;
            }
        }
    }
    if (interCode->icType == IC_MUL){// x = y * z
        struct Register* regRes = getReg(interCode->info.binOp.result);
        struct Register* regOp1 = getReg(interCode->info.binOp.op1);
        struct Register* regOp2 = getReg(interCode->info.binOp.op2);
        fprintf(file, "\tmul %s, %s, %s\n", regRes->name, regOp1->name, regOp2->name);
        //todo
        return;
    }
    if (interCode->icType == IC_DIV){// x = y / z
        struct Register* regRes = getReg(interCode->info.binOp.result);
        struct Register* regOp1 = getReg(interCode->info.binOp.op1);
        struct Register* regOp2 = getReg(interCode->info.binOp.op2);
        fprintf(file, "\tdiv %s, %s\n", regOp1->name, regOp2->name);
        fprintf(file, "\tmflo %s\n", regRes->name);
        //todo
        return;
    }
    if (interCode->icType == IC_ASSIGN_ADDR_VAL){// x := *y
        struct Register* regRes = getReg(interCode->info.binOp.result);
        struct Register* regOp1 = getReg(interCode->info.binOp.op1);
        fprintf(file, "\tlw %s, 0(%s)\n", regRes->name, regOp1->name);
        //todo
        return;
    }
    if (interCode->icType == IC_ADDR_ASSIGN_VAL){// *x := y
        struct Register* regRes = getReg(interCode->info.binOp.result);
        struct Register* regOp1 = getReg(interCode->info.binOp.op1);
        fprintf(file, "\tsw %s, 0(%s)\n", regOp1->name, regRes->name);
        //todo
        return;
    }
    if (interCode->icType == IC_GOTO){//goto x
        fprintf(file, "\tj %d\n", interCode->info.gotoNo);
        return;
    }
    if (interCode->icType == IC_PARAM){// arg
        struct Operand* arg = interCode->info.argOp;
        //fprintf(file, "\tlw $s0, %d($fp)\n", location);
        //fprintf(file, "\tsubu %sp, $sp, 4\n");
        //fprintf(file, "\tsw $s0, 0($sp)\n");
        //argNum++;
        return;
    }
    if (interCode->icType == IC_CALL){// x := CALL f
        //fprintf(file, "\tli $v1,%d\n", argNum*4);
        fprintf(file, "\tsubu $sp, $sp, 4\n");
        fprintf(file, "\tsw $v1, 0($sp)\n");
        //argNum = 0;
        fprintf(file, "\tsubu $sp, $sp, 4\n");
        fprintf(file, "\tsw $ra, 0($sp)\n");
        struct Register* reg = getReg(interCode->info.funcCall.result);
        fprintf(file, "\tjal %s\n", interCode->info.funcCall.function);
        fprintf(file, "\tmove %s, $v0\n", reg->name);
        //save to stack
        //todo
        fprintf(file, "\tlw $ra, 0($sp)\n");//
        fprintf(file, "\taddi $sp, $sp, 4\n");
        //recycle stack space
        //todo
        return;
    }
    if (interCode->icType == IC_FUNCTION){
        fprintf(file, "\n%s:\n", interCode->info.funcName);
        fprintf(file, "\tsw $fp, 0($sp)\n");//save fp
        fprintf(file, "\tmove $fp, $sp\n");//reset fp
        //apply stack size (fp + offset)
        //save local variable
        //initialize stack offset, param Num
        //todo
        return;
    }
    if (interCode->icType == IC_RELOP_GOTO){
        struct Register* reg1 = getReg(interCode->info.relGoto.leftRelOp);
        struct Register* reg2 = getReg(interCode->info.relGoto.rightRelOp);
        char* cond = interCode->info.relGoto.relOp;
        int gotoNo = interCode->info.relGoto.gotoNo;
        if (strcmp(cond, "==") == 0)
            fprintf(file, "\tbeq %s, %s, %d\n", reg1->name, reg2->name, gotoNo);
        else if (strcmp(cond, "!=") == 0)
            fprintf(file, "\tbne %s, %s, %d\n", reg1->name, reg2->name, gotoNo);
        else if (strcmp(cond, ">") == 0)
            fprintf(file, "\tbgt %s, %s, %d\n", reg1->name, reg2->name, gotoNo);
        else if (strcmp(cond, "<") == 0)
            fprintf(file, "\tblt %s, %s, %d\n", reg1->name, reg2->name, gotoNo);
        else if (strcmp(cond, ">=") == 0)
            fprintf(file, "\tbge %s, %s, %d\n", reg1->name, reg2->name, gotoNo);
        else if (strcmp(cond, "<=") == 0)
            fprintf(file, "\tble %s, %s, %d\n", reg1->name, reg2->name, gotoNo);
        return;
    }
    if (interCode->icType == IC_READ){
        fprintf(file, "\taddi $sp, $sp, -4\n");
        fprintf(file, "\tsw $ra, 0($sp)\n");//save ra
        fprintf(file, "\tjal read\n");
        struct Register* reg = getReg(interCode->info.readOp);
        fprintf(file, "\tmove %s, $v0\n", reg->name);
        //todo
        fprintf(file, "\tlw $ra, 0($sp)\n");//reload ra
        fprintf(file, "\taddi $sp, $sp, 4\n");
        return;
    }
    if (interCode->icType == IC_WRITE){
        fprintf(file, "\taddi $sp, $sp, -4\n");
        fprintf(file,"\tsw $ra, 0($sp)\n");//save ra
        struct Register* reg = getReg(interCode->info.writeOp);
        
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












