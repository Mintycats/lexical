#ifndef ASM
#define ASM
#include "asm.h"
#endif

//global variable
struct Register* reg[32];
struct Variable* allVari = NULL;

FILE* Asmfile = NULL;
struct Fp* fp = NULL;
int argNum = 0;
int paramNum = 0;
int offset = -4;

#ifdef SIMPLE_REG

struct Register* getReg(struct Operand* operand){
    struct Variable* vari = makeVari(operand);
    for (int i = SELF_REG_START1; i <= SELF_REG_END1; i++){
        if (reg[i]->vari == NULL){
            //debugPrint3("find a reg");
            reg[i]->vari = vari;
            vari->reg = reg[i];
            if (i+1 <= SELF_REG_END1 && reg[i+1]->vari != NULL){
                reg[i+1]->vari->reg = NULL;
                reg[i+1]->vari = NULL;
            }
            if (i == SELF_REG_END1){
                reg[SELF_REG_START1]->vari->reg = NULL;
                reg[SELF_REG_START1]->vari = NULL;
            }
            if (operand->opType == OP_CONSTANT){
                fprintf(Asmfile, "\tli %s, %d\n", reg[i]->name, operand->info.val);
                fprintf(Asmfile, "\tsw %s, %d($fp)\n", reg[i]->name, reg[i]->vari->offset);
            }
            return reg[i];
        }
    }
    for (int i = SELF_REG_START2; i <= SELF_REG_END2; i++){
        if (reg[i]->vari == NULL){
            reg[i]->vari = vari;
            vari->reg = reg[i];
            if (i+1 <= SELF_REG_END2 && reg[i+1]->vari != NULL){
                reg[i+1]->vari->reg = NULL;
                reg[i+1]->vari = NULL;
            }
            if (i == SELF_REG_END2){
                reg[SELF_REG_START2]->vari->reg = NULL;
                reg[SELF_REG_START2]->vari = NULL;
            }
            if (operand->opType == OP_CONSTANT){
                fprintf(Asmfile, "\tli %s, %d\n", reg[i]->name, operand->info.val);
                fprintf(Asmfile, "\tsw %s, %d($fp)\n", reg[i]->name, reg[i]->vari->offset);
            } 
            return reg[i];
        }
    }
}
#else

#endif
void clearReg(){
    for (int i = SELF_REG_START1; i <= SELF_REG_END1; i++){
        if (reg[i]->vari != NULL){
            reg[i]->vari->reg = NULL;
            reg[i]->vari = NULL;
        }
    }
    for (int i = SELF_REG_START2; i <= SELF_REG_END2; i++){
        if (reg[i]->vari == NULL){
            reg[i]->vari->reg = NULL;
            reg[i]->vari = NULL;
        }
    }
}

struct Variable* makeVari(struct Operand* operand){
    //debugPrint3("start makeVari");
    struct Variable* vari = findVari(operand);
    if (vari != NULL){
        return vari;
    }
    if (DEBUG_FLAG3){
        //printf("not find\n");
        //printf("cur off is %d", offset);
    }
    vari = (struct Variable*)malloc(sizeof(struct Variable));
    vari->op = operand;
    vari->reg = NULL;
    vari->offset = offset;
    offset -= 4;//
    
    vari->next = allVari;
    allVari = vari;
    //debugPrint3("end makeVari");
    return vari;
}

struct Variable* findVari(struct Operand* operand){
    struct Variable* tmpVari = allVari;
    while (tmpVari != NULL){
        if (tmpVari->op == operand){
            debugPrint3("find vari");
            return tmpVari;
        }
        tmpVari = tmpVari->next;
    }
    debugPrint3("not find");
    return NULL;
}

void makeRegName(char* dst, int num){
    int index = 0;
    dst[index] = '$';
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
    debugPrint3("start initReg");
    for (int i = 0; i < 32; i++){
        reg[i] = (struct Register*)malloc(sizeof(struct Register));
        makeRegName(reg[i]->name, i);
        reg[i]->vari = NULL;
    }
}

void saveCalleeReg(){
    return;
    for (int i = CALLEE_START1; i <= CALLEE_END1; i++){
        fprintf(Asmfile, "\tsw %s, %d($fp)\n", reg[i]->name, offset);
        offset -= 4;
    }
    for (int i = CALLEE_START2; i <= CALLEE_END2; i++){
        fprintf(Asmfile, "\tsw %s, %d($fp)\n", reg[i]->name, offset);
        offset -= 4;
    }
}

void recoverCalleeReg(){
    return;
    int tmpOff = -4;
    for (int i = CALLEE_START1; i <= CALLEE_END1; i++){
        fprintf(Asmfile, "\tlw %s, %d($fp)\n", reg[i]->name, tmpOff);
        tmpOff -= 4;
    }
    for (int i = CALLEE_START2; i <= CALLEE_END2; i++){
        fprintf(Asmfile, "\tlw %s, %d($fp)\n", reg[i]->name, tmpOff);
        tmpOff -= 4;
    }
}

void ir2Asm(struct InterCode* interCode, FILE* file){
    if (DEBUG_FLAG3){
        //printf("icType: %d\n", interCode->icType);
    }

    if (interCode->icType == IC_LABEL){
        fprintf(file, "label%d:\n", interCode->info.labelNo);
        return;
    }
    if (interCode->icType == IC_ASSIGN){
        if (interCode->info.assign.rightOp->opType == OP_CONSTANT){//x := #k
            debugPrint3("assign const");
            struct Register* reg = getReg(interCode->info.assign.leftOp);
            debugPrint3("assign const alive");
            fprintf(file, "\tli %s, %d\n", reg->name, interCode->info.assign.rightOp->info.val);//assign regVal to stack
            fprintf(file, "\tsw %s, %d($fp)\n", reg->name, reg->vari->offset);
            return;
        }
        if (interCode->info.assign.rightOp->opType != OP_CONSTANT){//x := y
            debugPrint3("assign vari");
            struct Register* reg1 = getReg(interCode->info.assign.leftOp);
            struct Register* reg2 = getReg(interCode->info.assign.rightOp);
            fprintf(file, "\tlw %s, %d($fp)\n", reg2->name, reg2->vari->offset);
            fprintf(file, "\tmove %s, %s\n", reg1->name, reg2->name);//assign regVal to stack
            fprintf(file, "\tsw %s, %d($fp)\n", reg1->name, reg1->vari->offset);
            return;
        }
    }
    if (interCode->icType == IC_ADD || interCode->icType == IC_SUB){
        if (interCode->info.binOp.op2->opType == OP_CONSTANT){//x := y op #k
            struct Register* regVal = getReg(interCode->info.binOp.result);
            struct Register* regOp = getReg(interCode->info.binOp.op1);
            fprintf(file, "\tlw %s, %d($fp)\n", regOp->name, regOp->vari->offset);
            if (interCode->icType == IC_ADD){
                fprintf(file, "\taddi %s, %s, %d\n",regVal->name, regOp->name, interCode->info.binOp.op2->info.val);
                fprintf(file, "\tsw %s, %d($fp)\n", regVal->name, regVal->vari->offset);
                return;
            }
            if (interCode->icType == IC_SUB){
                fprintf(file, "\taddi %s, %s, -%d\n", regVal->name, regOp->name, interCode->info.binOp.op2->info.val);
                fprintf(file, "\tsw %s, %d($fp)\n", regVal->name, regVal->vari->offset);
                return;
            }
        }
        if (interCode->info.binOp.op2->opType != OP_CONSTANT){//x := y op z
            struct Register* regRes = getReg(interCode->info.binOp.result);
            struct Register* regOp1 = getReg(interCode->info.binOp.op1);
            fprintf(file, "\tlw %s, %d($fp)\n", regOp1->name, regOp1->vari->offset);
            struct Register* regOp2 = getReg(interCode->info.binOp.op2);
            fprintf(file, "\tlw %s, %d($fp)\n", regOp2->name, regOp2->vari->offset);
            if (interCode->icType == IC_ADD){
                fprintf(file, "\tadd %s, %s, %s\n", regRes->name, regOp1->name, regOp2->name);
                //save
                //todo
                fprintf(file, "\tsw %s, %d($fp)\n", regRes->name, regRes->vari->offset);
                return;
            }
            if (interCode->icType == IC_SUB){
                fprintf(file, "\tsub %s, %s, %s\n", regRes->name, regOp1->name, regOp2->name);
                //todo
                fprintf(file, "\tsw %s, %d($fp)\n", regRes->name, regRes->vari->offset);
                return;
            }
        }
    }
    if (interCode->icType == IC_MUL){// x = y * z
        struct Register* regRes = getReg(interCode->info.binOp.result);
        struct Register* regOp1 = getReg(interCode->info.binOp.op1);
        fprintf(file, "\tlw %s, %d($fp)\n", regOp1->name, regOp1->vari->offset);
        struct Register* regOp2 = getReg(interCode->info.binOp.op2);
        fprintf(file, "\tlw %s, %d($fp)\n", regOp2->name, regOp2->vari->offset);
        fprintf(file, "\tmul %s, %s, %s\n", regRes->name, regOp1->name, regOp2->name);
        fprintf(file, "\tsw %s, %d($fp)\n", regRes->name, regRes->vari->offset);
        return;
    }
    if (interCode->icType == IC_DIV){// x = y / z
        struct Register* regRes = getReg(interCode->info.binOp.result);
        struct Register* regOp1 = getReg(interCode->info.binOp.op1);
        fprintf(file, "\tlw %s, %d($fp)\n", regOp1->name, regOp1->vari->offset);
        struct Register* regOp2 = getReg(interCode->info.binOp.op2);
        fprintf(file, "\tlw %s, %d($fp)\n", regOp2->name, regOp2->vari->offset);
        fprintf(file, "\tdiv %s, %s\n", regOp1->name, regOp2->name);
        fprintf(file, "\tmflo %s\n", regRes->name);
        //todo
        fprintf(file, "\tsw %s, %d($fp)\n", regRes->name, regRes->vari->offset);
        return;
    }
    if (interCode->icType == IC_ASSIGN_ADDR){// x := &y
        struct Register* regRes = getReg(interCode->info.assign.leftOp);
        struct Register* regOp1 = getReg(interCode->info.assign.rightOp);
        struct Variable* vari = regOp1->vari;
        fprintf(file, "\taddi %s, $fp, %d\n", regRes->name, vari->offset);
        fprintf(file, "\tsw %s, %d($fp)\n", regRes->name, regRes->vari->offset);
        return;
    }
    if (interCode->icType == IC_ASSIGN_ADDR_VAL){// x := *y
        struct Register* regRes = getReg(interCode->info.assign.leftOp);
        struct Register* regOp1 = getReg(interCode->info.assign.rightOp);
        fprintf(file, "\tlw %s, %d($fp)\n", regOp1->name, regOp1->vari->offset);
        fprintf(file, "\tlw %s, 0(%s)\n", regRes->name, regOp1->name);
        fprintf(file, "\tsw %s, %d($fp)\n", regRes->name, regRes->vari->offset);
        return;
    }
    if (interCode->icType == IC_ADDR_ASSIGN_VAL){// *x := y
        struct Register* regRes = getReg(interCode->info.assign.leftOp);
        fprintf(file, "\tlw %s, %d($fp)\n", regRes->name, regRes->vari->offset);
        struct Register* regOp1 = getReg(interCode->info.assign.rightOp);
        fprintf(file, "\tlw %s, %d($fp)\n", regOp1->name, regOp1->vari->offset);
        fprintf(file, "\tsw %s, 0(%s)\n", regOp1->name, regRes->name);
        return;
    }
    if (interCode->icType == IC_GOTO){//goto x
        fprintf(file, "\tj label%d\n", interCode->info.gotoNo);
        return;
    }
    if (interCode->icType == IC_ARG){// arg
        struct Operand* arg = interCode->info.argOp;
        struct Variable* vari = makeVari(arg);
        fprintf(file, "\tlw $s0, %d($fp)\n", vari->offset);
        fprintf(file, "\tsubu $sp, $sp, 4\n");
        fprintf(file, "\tsw $s0, 0($sp)\n");
        argNum++;
        return;
    }
    if (interCode->icType == IC_CALL){// x := CALL f
        fprintf(file, "\tli $v1, %d\n", argNum*4);
        fprintf(file, "\tsubu $sp, $sp, 4\n");
        fprintf(file, "\tsw $v1, 0($sp)\n");
        argNum = 0;
        fprintf(file, "\tsubu $sp, $sp, 4\n");
        fprintf(file, "\tsw $ra, 0($sp)\n");
        struct Register* reg = getReg(interCode->info.funcCall.result);
        fprintf(file, "\tjal %s\n", interCode->info.funcCall.function);
        fprintf(file, "\tmove %s, $v0\n", reg->name);
        //save to stack
        fprintf(file, "\tsw %s, %d($fp)\n", reg->name, reg->vari->offset);
        fprintf(file, "\tlw $ra, 0($sp)\n");
        fprintf(file, "\taddi $sp, $sp, 4\n");
        //recycle stack space
        fprintf(file, "\tlw $v1, 0($sp)\n");//load to v1
        fprintf(file, "\taddi $sp, $sp, 4\n");
        fprintf(file, "\tadd $sp, $sp, $v1\n");
        return;
    }
    if (interCode->icType == IC_FUNCTION){
        fprintf(file, "\n%s:\n", interCode->info.funcName);
        fprintf(file, "\tsubu $sp, $sp, 4\n");
        fprintf(file, "\tsw $fp, 0($sp)\n");//save fp
        fprintf(file, "\tmove $fp, $sp\n");//reset fp
        offset = -4;//initialize stack offset
        fprintf(file, "\taddi $sp, $sp, -%d\n", APPLY_SIZE); //apply stack size (fp + offset)
        saveCalleeReg();//save local variable
        //initialize param Num
        paramNum = 1;
        return;
    }
    if (interCode->icType == IC_PARAM){
        struct Register* regPram = getReg(interCode->info.paramOp);
        fprintf(file, "\tlw %s, %d($fp)\n", regPram->name, PARAM_BASE+paramNum*4);
        paramNum += 1;//base 8
        fprintf(file, "\tsw %s, %d($fp)\n", regPram->name, regPram->vari->offset);
        return;
    }
    if (interCode->icType == IC_RETURN){
        struct Register* retReg = getReg(interCode->info.retOp);
        fprintf(file, "\tlw %s, %d($fp)\n", retReg->name, retReg->vari->offset);
        fprintf(file, "\tmove $v0, %s\n", retReg->name);
        recoverCalleeReg();
        fprintf(file, "\tmove $sp, $fp\n");//recover sp
        fprintf(file, "\tlw $fp, 0($fp)\n");//recover fp
        fprintf(file, "\taddi $sp, $sp, 4\n");//recover sp
        fprintf(file, "\tjr $ra\n");
        return;
    }
    if (interCode->icType == IC_RELOP_GOTO){
        struct Register* reg1 = getReg(interCode->info.relGoto.leftRelOp);
        fprintf(file, "\tlw %s, %d($fp)\n", reg1->name, reg1->vari->offset);
        struct Register* reg2 = getReg(interCode->info.relGoto.rightRelOp);
        fprintf(file, "\tlw %s, %d($fp)\n", reg2->name, reg2->vari->offset);
        char* cond = interCode->info.relGoto.relOp;
        int gotoNo = interCode->info.relGoto.gotoNo;
        if (strcmp(cond, "==") == 0)
            fprintf(file, "\tbeq %s, %s, label%d\n", reg1->name, reg2->name, gotoNo);
        else if (strcmp(cond, "!=") == 0)
            fprintf(file, "\tbne %s, %s, label%d\n", reg1->name, reg2->name, gotoNo);
        else if (strcmp(cond, ">") == 0)
            fprintf(file, "\tbgt %s, %s, label%d\n", reg1->name, reg2->name, gotoNo);
        else if (strcmp(cond, "<") == 0)
            fprintf(file, "\tblt %s, %s, label%d\n", reg1->name, reg2->name, gotoNo);
        else if (strcmp(cond, ">=") == 0)
            fprintf(file, "\tbge %s, %s, label%d\n", reg1->name, reg2->name, gotoNo);
        else if (strcmp(cond, "<=") == 0)
            fprintf(file, "\tble %s, %s, label%d\n", reg1->name, reg2->name, gotoNo);
        return;
    }
    if (interCode->icType == IC_READ){
        fprintf(file, "\taddi $sp, $sp, -4\n");
        fprintf(file, "\tsw $ra, 0($sp)\n");//save ra
        fprintf(file, "\tjal read\n");
        struct Register* reg = getReg(interCode->info.readOp);
        fprintf(file, "\tmove %s, $v0\n", reg->name);
        fprintf(file, "\tsw %s, %d($fp)\n", reg->name, reg->vari->offset);
        fprintf(file, "\tlw $ra, 0($sp)\n");//reload ra
        fprintf(file, "\taddi $sp, $sp, 4\n");
        return;
    }
    if (interCode->icType == IC_WRITE){
        fprintf(file, "\taddi $sp, $sp, -4\n");
        fprintf(file,"\tsw $ra, 0($sp)\n");//save ra
        struct Register* reg = getReg(interCode->info.writeOp);
        fprintf(file, "\tlw %s, %d($fp)\n", reg->name, reg->vari->offset);
        if (interCode->info.writeOp->opType == OP_VARIABLE || interCode->info.writeOp->opType == OP_TEMP){
            fprintf(file, "\tmove $a0, %s\n", reg->name);
        }
        else if (interCode->info.writeOp->opType = OP_ADDRESS || interCode->info.writeOp->opType == OP_ARRAY){
            fprintf(file, "\tlw $a0, 0(%s)\n", reg->name);
        }
        fprintf(file, "\tjal write\n");
        fprintf(file, "\tsw %s, %d($fp)\n", reg->name, reg->vari->offset);
        fprintf(file, "\tlw $ra, 0($sp)\n");
        fprintf(file, "\taddi $sp, $sp, 4\n");//recover ra
        return;
    }
    if (interCode->icType == IC_DEC){
        struct Register* reg = getReg(interCode->info.dec.operand);
        offset += 4;
        reg->vari->offset = 0;
        int appSize = interCode->info.dec.size;
        if (DEBUG_FLAG3){
            printf("curOffset is: %d\n", offset);
            printf("apply size is: %d\n", appSize);
        }
        reg->vari->offset = offset - appSize;//head is in low addr
        offset = reg->vari->offset - 4;//reset offset
        return;
    }
}

void makeAsm(struct CodeList* codeList, FILE* file){
    debugPrint3("start makeAsm");
    if (file == NULL)
        return;
    Asmfile = file;
    //save global string
    fprintf(file, ".data\n_prompt: .asciiz \"Enter an integer:\"\n_ret: .asciiz \"\\n\"\n.globl main\n.text\n");
    //define read
    fprintf(file, "\nread:\n");
    //fprintf(file, "\tli $v0, 4\n");
    //fprintf(file, "\tla $a0, _prompt\n");
    //fprintf(file, "\tsyscall\n");
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
    int i = 1;
    while (tmpCl != NULL){
        if (DEBUG_FLAG3){
            //printf("turn %d\n", i);
            //if (i == 3)
                //return;
            i++;
        }
        ir2Asm(tmpCl->interCode, file);
        //debugPrint3("alive");
        tmpCl = tmpCl->next;
    }
}












