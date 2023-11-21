#ifndef IR_ENABLE
#define IR_ENABLE
#include "irfile.h"
#endif


struct CodeList* startInterCode(struct Node* rootNode){
    debugPrint("start of InterCode");
    if (rootNode == NULL){
        debugPrint("root is null in InterCode");
        return NULL;
    }
    if (strcmp(rootNode->name, "Program") != 0){
        debugPrint("invalid program in InterCode");
        return NULL;
    }
    codeHead = NULL;
    codeTail = NULL;
    variableHead = NULL;
    variableTail = NULL;
    variableNum = 1;
    labelNum = 1;
    tempNum = 1;

    struct Node* node = rootNode->leftchild;
    while (node != NULL){
        node = node->leftchild;
        debugPrint("enter trans_ExtDef in startInterCode");
        insertIR(trans_ExtDef(node));
        node = node->rightbrother;
    }

    return codeHead;
}

struct CodeList* trans_ExtDef(struct Node* node){
    debugPrint("start of trans_ExtDef");
    if (node == NULL){
        debugPrint("node is NULL in trans_ExtDef");
        return NULL;
    }
    struct Node* child = node->leftchild;
    if (strcmp(child->rightbrother->name, "SEMI") == 0){
        debugPrint("Specifier SEMI in ExtDef");
        return NULL;
    }
    if (strcmp(child->rightbrother->name, "ExtDecList") == 0){
        debugPrint("Specifier ExtDecList SEMI in trans_ExtDef");
        return NULL;
    }

    struct CodeList codeList1 = trans_FunDec(child->rightbrother);
    struct CodeList codeList2 = trans_CompSt(child->rightbrother->rightbrother);
    
    return concat(codeList1, codeList2);
}

struct CodeList* trans_FunDec(struct Node* node){
    debugPrint("start of trans_FunDec");
    if (node == NULL){
        debugPrint("node is NULL in trans_FunDec");
        return NULL;
    }
    if (child->rightbrother->rightbrother->rightbrother == NULL){//ID LP RP
        struct InterCode* interCode = makeInterCode(IC_FUNCTION);
        strcpy(interCode->info.funcName, child->strval);
        struct CodeList codeList = makeCodeList(interCode);
        return codeList;
    }
    struct InterCode* interCode = makeInterCode(IR_FUNCTION);
    strcpy(interCode->info.funcName, child->strval);
    struct CodeList* codeList = makeCodeList(interCode);
    struct FieldList* fl = NULL;
    struct HashNode* hashNode = hashFind(child->strval);
    if (hashNode == NULL){
        debugPrint("not find hashNode in trans_FunDec");
    }
    fl = hashNode->type->info.function->param;
    while (fl != NULL){
        if (fl->type->type == VARIABLE){

        }else{

        }
    }
}

struct InterCode* makeInterCode(enum IcType icType){
    struct InterCode* newIc = (struct InterCode*)malloc(sizeof(struct InterCode));
    newIc->icType = icType;
    return newIc;
}

struct CodeList* makeCodeList(struct InterCode* ic){
    struct CodeList* newCl = (struct CodeList*)malloc(sizeof(struct CodeList));
    newCl->last = NULL;
    newCl->next = NULL;
    newCl->interCode = ic;
    return newCl;
}

struct CodeList* trans_CompSt(struct Node* node){
    debugPrint("start of trans_CompSt");
    if (node == NULL){
        debugPrint("node is NULL in trans_CompSt");
        return NULL;
    }
    struct Node* child = node->leftchild;
    if (strcmp(child->rightbrother->name, "RC") == 0){//LC RC
        return NULL;
    }
    struct CodeList* defList = NULL;
    struct CodeList* stmtList = NULL;
    if (strcmp(child->rightbrother->name, "DefList") == 0){
        defList = trans_DefList(child->rightbrother);
        if (strcmp(child->rightbrother->rightbrother->name, "StmtList") == 0){//LC DefList StmtList RC
            stmtList = trans_StmtList(child->rightbrother->rightbrother);
        }
    }
    else if (strcmp(child->rightbrother->name, "StmtList") == 0){//LC StmtList RC
        stmtList = trans_StmtList(child->rightbrother);
    }
    return concat(defList, stmtList);
}

struct CodeList* trans_StmtList(struct Node* node){
    debugPrint("start of trans_StmtList");
    if (node == NULL){
        debugPrint("node is NULL in trans_StmtList");
        return NULL;
    }
    struct CodeList* clStart = NULL;
    struct CodeList* clEnd = NULL;
    while (node != NULL){
        if (clStart == NULL){
            clstart = trans_Stmt(node->leftchild);
            clEnd = clStart;
            while (clEnd->next != NULL){
                clEnd = clEnd->next;
            }
            node = node->leftchild->rightbrother;
        }
        else{
            clEnd->next = trans_Stmt(node->leftchild);
            clEnd->next->last = clEnd;
            while (clEnd->next != NULL){
                clEnd = clEnd->next;
            }
            node = node->leftchild->rightbrother;
        }
    }
    return clStart;
}

struct CodeList* trans_Stmt(struct Node* node){
    debugPrint("start of trans_Stmt");
    if (node == NULL){
        debugPrint("node is NULL in trans_Stmt");
        return NULL;
    }
    struct Node* child = node->leftchild;
    if (strcmp(child->name, "Exp") == 0){//Exp SEMI
        return trans_Exp(child);
    }
    if (strcmp(child->name, "CompSt") == 0){//CompSt
        return trans_CompSt(child);
    }
    if (strcmp(child->name, "RETURN") == 0){//RETURN Exp SEMI
        struct Operand* operand = makeTempOperand();
        struct CodeList* cl1 = trans_Exp(child->rightbrother, operand);
        struct CodeList* cl2 = makeIc(NULL, operand, NULL, IC_RETURN);
        return concat(cl1, cl2);
    }
    if (strcmp(child->name, "IF") == 0 && child->rightbrother->rightbrother->rightbrother->rightbrother->rightbrother == NULL){//IF LP Exp RP Stmt
        struct InterCode* ic1 = makeLabel();
        struct InterCode* ic2 = makeLabel();
        struct CodeList* cl1 = trans_Cond(child->rightbrother->rightbrother, ic1, ic2);
        struct CodeList* cl2 = trans_Stmt(child->rightbrother->rightbrother->rightbrother->rightbrother);
        struct CodeList* cl3 = makeIc(NULL, ic1, NULL, IC_LABEL);
        struct CodeList* cl4 = makeIc(NULL, ic2, NULL, IC_LABEL);
        return concat(concat(cl1, cl3), concat(cl2, cl4));
    }
    else if (strcmp(child->name, "IF") == 0){//IF LP Exp RP Stmt ElSE Stmt
        struct InterCode* ic1 = makeLabel();
        struct InterCode* ic2 = makeLabel();
        struct InterCode* ic3 = makeLabel();
        struct CodeList* cl1 = trans_Cond(child->rightbrother->rightbrother, ic1, ic2);
        struct CodeList* cl2 = trans_Stmt(child->rightbrother->rightbrother->rightbrother->rightbrother);
        struct CodeList* cl3 = makeIc(NULL, ic1, NULL, IC_LABEL);
        struct CodeList* cl4 = makeIc(NULL, ic2, NULL, IC_LABEL);
        struct CodeList* cl5 = trans_Stmt(child->rightbrother->rightbrother->rightbrother->rightbrother->rightbrother->rightbrother);
        struct CodeList* cl6 = makeIc(NULL, ic3, NULL, IC_LABEL);
        return concat(concat(concat(cl1, cl3), concat(cl2, cl4)), concat(cl5, cl6));
    }
    if (strcmp(child->name, "WHILE") == 0){//WHILE LP Exp RP Stmt
        struct InterCode* ic1 = makeLabel();
        struct InterCode* ic2 = makeLabel();
        struct InterCode* ic3 = makeLabel();
        struct CodeList* cl1 = trans_Cond(child->rightbrother->rightbrother, ic2, ic3);
        struct CodeList* cl2 = trans_Stmt(child->rightbrother->rightbrother->rightbrother->rightbrother);
        struct CodeList* cl3 = makeIc(NULL, ic1, NULL, IC_LABEL);
        struct CodeList* cl4 = makeIc(NULL, ic2, NULL, IC_LABEL);
        struct CodeList* cl5 = makeIc(NULL, ic3, NULL, IC_LABEL);
        struct CodeList* cl6 = makeIc(NULL, ic2, NULL, IC_GOTO);
        return concat(concat(concat(cl3, cl1), concat(cl4, cl2)), concat(cl6, cl5));
    }
    return NULL;
}

struct CodeList* trans_Cond(struct Node* node, struct InterCode* trueLabel, struct InterCode* falseLabel){
    struct Node* child = node->leftchild;
    if (strcmp(child->name, "Exp") == 0 && strcmp(child->rightbrother->name, "RELOP") == 0){
        struct Operand* op1 = makeTempOperand();
        struct Operand* op2 = makeTempOperand();
        struct CodeList* cl1 = trans_Exp(child, op1);
        struct CodeList* cl2 = trans_Exp(child->rightbrother->rightbrother, op2);
        struct CodeList* cl3 = makeIfIc(child->rightbrother->strval, op1, op2, trueLabel);
        struct CodeList* cl4 = makeGotoIc(falseLabel);
        return concat(concat(cl1, cl2), concat(cl3, cl4));
    }
    if (strcmp(child->name, "NOT") == 0){//NOT Exp
        return trans_Cond(child->rightbrother, falseLabel, trueLabel);
    }
    if (strcmp(child->name, "Exp") == 0 && strcmp(child->rightbrother->name, "AND") == 0){
        struct InterCode* label1 = makeLabel();
        struct CodeList* cl1 = trans_Cond(child, label1, falseLabel);
        struct CodeList* cl2 = trans_Cond(child->rightbrother->rightbrother, trueLabel, falseLabel);
        struct CodeList* cl3 = makeLabelIc(label1);
        return concat(concat(cl1, cl3), cl2);
    }
    if (strcmp(child->name, "Exp") == 0 && strcmp(child->rightbrother->name, "OR") == 0){//Exp OR Exp
        struct InterCode* label1 = makeLabel();
        struct CodeList* cl1 = trans_Cond(child, trueLabel, label1);
        struct CodeList* cl2 = trans_Cond(child->rightbrother->rightbrother, trueLabel, falseLabel);
        struct CodeList* cl3 = makeLabelIc(label1);
        return concat(concat(cl1, cl3), cl2);
    }
    //else
    struct Operand* op1 = makeTempOperand();
    struct CodeList* cl1 = trans_Exp(node, op1);
    struct CodeList* cl2 = makeIfIc("!=", op1, constZero, trueLabel);
    struct CodeList* cl3 = makeGotoIc(falseLabel);
    return concat(concat(cl1, cl2), cl3);
}

struct CodeList* trans_Exp(struct Node* node, struct Operand* operand){
    debugPrint("start of trans_Exp");
    struct Node* child = node->leftchild;
    if (strcmp(child->name, "ID") == 0 && child->rightbrother == NULL){//ID
        struct HashNode* tmpHash = hashFind(child->strval);
        if (tmpHash == NULL)
            return NULL;
        struct Operand* op = lookUp(str);//
        if (op->opType == OP_ARRAY && op->opType == OP_STRUCT){
            struct InterCode* ic = makeInterCode(IC_ASSIGN_ADDR);
            ic->info.assignAddr.leftOp = operand;
            ic->info.assignAddr.rightOp = op;
            return makeCodeList(ic);
        }else{
            struct InterCode* ic = makeInterCode(IC_ASSIGN);
            ic->info.assign.leftOp = operand;
            ic->info.assign.rightOp = op;
            return makeCodeList(ic);
        }
    }
    if (strcmp(child->name, "INT") == 0 || strcmp(child->name, "FLOAT") == 0){//INT || FLOAT
        int intVal = child->intval;
        struct InterCode* ic = makeInterCode(IC_ASSIGN);
        ic->info.assign.leftOp = operand;
        ic->info.assign.rightOp = makeConstInt(intval);
        return makeCodeList(ic);
    }
    if (strcmp(child->name, "Exp") == 0 && strcmp(child->rightbrother->rightbrother->name, "Exp") == 0 && child->rightbrother->rightbrother->rightbrother == NULL){//Exp op Exp
        
        if (strcmp(child->rightbrother->name, "ASSIGNOP") == 0){
            struct Operand* tmpOp2 = makeTempOperand();
            struct Operand* leftVari = lookUp(findId(child));
            struct CodeList* cl1 = trans_Exp(child->rightbrother->rightbrother, tmpOp2);
            struct CodeList* cl2 = makeIc(NULL, leftVari, tmpOp2, IC_ASSIGN);
            struct CodeList* cl3 = makeIc(NULL, operand, leftVari, IC_ASSIGN);
            return  concat(cl1, concat(cl2, cl3));
        }
        else if (strcmp(child->rightbrother->name, "AND") == 0){
            struct InterCode* label1 = makeLabel();
            struct InterCode* label2 = makeLabel();
            struct CodeList* cl1 = makeIc(NULL, operand, constZero);
            struct CodeList* cl2 = trans_cond(node, label1, label2);
            struct CodeList* cl3 = makeIc(NULL, label1, NULL, IC_LABEL);
            struct CodeList* cl4 = makeIc(NULL, operand, constOne, IC_ASSIGN);
            struct CodeList* cl5 = makeIc(NULL, label2, NULL, IC_LABEL);
            return concat(concat(concat(concat(cl1, cl2), cl3), cl4), cl5);
        }
        else if (strcmp(child->rightbrother->name, "OR") == 0){
            struct InterCode* label1 = makeLabel();
            struct InterCode* label2 = makeLabel();
            struct CodeList* cl1 = makeIc(NULL, operand, constZero);
            struct CodeList* cl2 = trans_cond(node, label1, label2);
            struct CodeList* cl3 = makeIc(NULL, label1, NULL, IC_LABEL);
            struct CodeList* cl4 = makeIc(NULL, operand, constOne, IC_ASSIGN);
            struct CodeList* cl5 = makeIc(NULL, label2, NULL, IC_LABEL);
            return concat(concat(concat(concat(cl1, cl2), cl3), cl4), cl5);
        }
        else if (strcmp(child->rightbrother->name, "RELOP") == 0){
            struct InterCode* label1 = makeLabel();
            struct InterCode* label2 = makeLabel();
            struct CodeList* cl1 = makeIc(NULL, operand, constZero);
            struct CodeList* cl2 = trans_cond(node, label1, label2);
            struct CodeList* cl3 = makeIc(NULL, label1, NULL, IC_LABEL);
            struct CodeList* cl4 = makeIc(NULL, operand, constOne, IC_ASSIGN);
            struct CodeList* cl5 = makeIc(NULL, label2, NULL, IC_LABEL);
            return concat(concat(concat(concat(cl1, cl2), cl3), cl4), cl5);
        }
        else if (strcmp(child->rightbrother->name, "PLUS") == 0){
            struct Operand* tmpOp1 = makeTempOperand();
            struct Operand* tmpOp2 = makeTempOperand();
            struct CodeList* cl1 = trans_Exp(child, tmpOp1);
            struct CodeList* cl2 = trans_Exp(child->rightbrother->rightbrother, tmpOp2);
            struct CodeList* cl3 = makeIc(operand, tmpOp1, tmpOp2, IC_ADD);
            return concat(concat(cl1, cl2), cl3);
        }
        else if (strcmp(child->rightbrother->name, "MINUS") == 0){
            struct Operand* tmpOp1 = makeTempOperand();
            struct Operand* tmpOp2 = makeTempOperand();
            struct CodeList* cl1 = trans_Exp(child, tmpOp1);
            struct CodeList* cl2 = trans_Exp(child->rightbrother->rightbrother, tmpOp2);
            struct CodeList* cl3 = makeIc(operand, tmpOp1, tmpOp2, IC_SUB);
            return concat(concat(cl1, cl2), cl3);
        }
        else if (strcmp(child->rightbrother->name, "STAR") == 0){
            struct Operand* tmpOp1 = makeTempOperand();
            struct Operand* tmpOp2 = makeTempOperand();
            struct CodeList* cl1 = trans_Exp(child, tmpOp1);
            struct CodeList* cl2 = trans_Exp(child->rightbrother->rightbrother, tmpOp2);
            struct CodeList* cl3 = makeIc(operand, tmpOp1, tmpOp2, IC_STAR);
            return concat(concat(cl1, cl2), cl3);
        }
        else if (strcmp(child->rightbrother->name, "DIV") == 0){
            struct Operand* tmpOp1 = makeTempOperand();
            struct Operand* tmpOp2 = makeTempOperand();
            struct CodeList* cl1 = trans_Exp(child, tmpOp1);
            struct CodeList* cl2 = trans_Exp(child->rightbrother->rightbrother, tmpOp2);
            struct CodeList* cl3 = makeIc(operand, tmpOp1, tmpOp2, IC_DIV);
            return concat(concat(cl1, cl2), cl3);
        }
        

    }
    if (strcmp(child->name, "LP") == 0){//LP Exp RP
        struct CodeList* cl1 = trans_Exp(child->rightbrother, operand);
        return cl1;
    }
    if (strcmp(child->name, "MINUS") == 0){//MINUS Exp
        struct Operand* tmp1 = makeTempOperand();
        struct CodeList* cl1 = trans_Exp(child->rightbrother, tmp1);
        struct CodeList* cl2 = makeIc(operand, constZero, tmp1, IC_SUB);
        return concat(cl1, cl2);
    }
    if (strcmp(child->name, "NOT") == 0){//NOT Exp
        struct InterCode* label1 = makeLabel();
        struct InterCode* label2 = makeLabel();
        struct CodeList* cl1 = makeIc(NULL, operand, constZero);
        struct CodeList* cl2 = trans_cond(node, label1, label2);
        struct CodeList* cl3 = makeIc(NULL, label1, NULL, IC_LABEL);
        struct CodeList* cl4 = makeIc(NULL, operand, constOne, IC_ASSIGN);
        struct CodeList* cl5 = makeIc(NULL, label2, NULL, IC_LABEL);
        return concat(concat(concat(concat(cl1, cl2), cl3), cl4), cl5);
    }
    if (strcmp(child->name, "ID") == 0 && strcmp(child->rightbrother->name, "LP") == 0 && strcmp(child->rightbrother->rightbrother->name, "RP") == 0){//ID LP RP
        struct HashNode* tmpHash = hashFind(child->strval);
        if (tmpHash == NULL)
            return NULL;
        struct Function* func = tmpHash->type->info.function;
        if (strcmp(func->name, "read")){
            return makeIc(NULL, operand, NULL, IC_READ);
        }
        return makeCallIc(operand, func->name);
    }
    if (strcmp(child->name, "ID") == 0 && strcmp(child->rightbrother->name, "LP") == 0 && strcmp(child->rightbrother->rightbrother->name, "Args") == 0){//ID LP Args RP
        struct HashNode* tmpHash = hashFind(child->strval);
        if (tmpHash == NULL)
            return NULL;
        struct Function* func = tmpHash->type->info.function;
        struct ArgList* args = NULL;
        struct CodeList* cl1 = trans_Args(child->rightbrother->rightbrother, args);
        struct CodeList* cl2 = NULL;
        if (func->name == "write")
            return concat(concat(cl1, makeWriteIc(args)), makeIc(operand, constZero, NULL, IC_ASSIGN));
        while (args != NULL){
            cl2 = concat(cl2, makeArgIc(args));
            args = args->next;
        }
        return concat(concat(cl1, cl2), makeCallIc(operand, func->name));
    }
    

}

struct CodeList* trans_Args(struct Node* node, struct ArgList* args){
    struct Node* child = node->leftchild;
    if (strcmp(child->name, "Exp") == 0 && child->rightbrother == NULL){//Exp
        struct Operand* op1 = makeTempOperand();
        struct CodeList* cl1 = trans_Exp(child, op1);
        struct ArgList* newArg = (struct ArgList*)malloc(sizeof(struct ArgList));
        newArg->args = op1;
        newArg->next = args;
        args = newArg;
        return cl1;
    }
    //Exp COMMA Args
    struct Operand* op1 = makeTempOperand();
    struct CodeList* cl1 = trans_Exp(child, op1);
    struct ArgList* newArg = (struct ArgList*)malloc(sizeof(struct ArgList));
    newArg->args = op1;
    newArg->next = args;
    args = newArg;
    struct CodeList* cl2 = trans_Args(child->rightbrother->rightbrother, newArg);
    return concat(cl1, cl2);
}

struct Operand* makeConstInt(int val){
    struct Operand* op = (struct Operand*)malloc(sizeof(struct Operand));
    op->opType = OP_CONSTANT;
    op->info.val = val;
    op->type = NULL;
    return op;
}

struct OperandHashNode* operandHashFind(char* name){
    int hashNum = hashNumOf(name);
    for (struct OperandHashNode* tmpNode = operandHashTable[hashNum]; tmpNode != NULL; tmpNode = tmpNode->next){
        if (strcmp(tmpNode->nodeName, name) == 0){//find it
            if (DEBUG_FLAG){
                printf("DEBUG: find operandHashNode named %s\n", name);
            }
            return tmpNode;
        }
    }
    if (DEBUG_FLAG){
        printf("DEBUG: not find operandHashNode named %s\n", name);
    }
    return NULL;
}

int operandCheckExist(char* name){
    if (operandHashFind(name) == NULL)
        return 0;
    return 1;
}

int insertOperandHashNode(char* name,struct Operand* operand){
    if (operandCheckExist(name) == 1){
        if (DEBUG_FLAG){
            printf("DEBUG: %s already exist, insert fail\n", name);
        }
        return 0;
    }
    int hashNum = hashNumOf(name);
    struct OperandHashNode* newNode = (struct OperandHashNode*)malloc(sizeof(struct OperandHashNode));
    strcpy(newNode->nodeName, name);
    newNode->operand = operand;
    newNode->next = NULL;
    struct OperandHashNode* tmpNode = operandHashTable[hashNum];
    if (tmpNode == NULL){
        operandHashTable[hashNum] = newNode;
        if (DEBUG_FLAG){
            printf("DEBUG: successfully insert %s into %d\n", name, hashNum);
        }
        return 1;
    }
    else{
        while (tmpNode->next != NULL){
            tmpNode = tmpNode->next;
        }
        tmpNode->next = newNode;
        if (DEBUG_FLAG){
            printf("DEBUG: successfully insert %s into %d\n", name, hashNum);
        }
        return 1;
    }
}

struct Operand* lookUpOperand(char* name, enum OpType opType){
    struct Operand* op = operandHashFind(name);
    if (op != NULL){
        return op;
    }
    op = (struct Operand*)malloc(sizeof(struct Operand));
    op->opType = opType;
    if (opType == OP_LABEL){
        op->info.labelNo = labelNum;
        labelNum++;
    }
    else if (opType == OP_TEMP){
        op->info.tempNo = tempNum;
        tempNum++;
    }
    //
    op->type = hashFind(name)->type;
    insertOperandHashNode(name, op);
    return op;
}
