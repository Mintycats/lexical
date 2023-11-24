#ifndef IR_ENABLE
#define IR_ENABLE
#include "irfile.h"
#endif

void insertIR(struct CodeList* codeList){
    if (codeHead == NULL){
        codeHead = codeList;
        codeTail = codeHead;
        while (codeTail->next != NULL){
            codeTail = codeTail->next;
        }
        return;
    }
    codeTail->next = codeList;
    codeList->last = codeTail;
    while (codeTail->next != NULL)
        codeTail = codeTail->next;
}



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
    /*variableHead = NULL;
    variableTail = NULL;*/
    variableNum = 1;
    labelNum = 1;
    tempNum = 1;
    
    constZero = makeOperand(OP_CONSTANT);
    constZero->info.val = 0;
    
    constOne = makeOperand(OP_CONSTANT);
    constOne->info.val = 1;
    

    struct Node* node = rootNode->leftchild;
    while (node != NULL){
        node = node->leftchild;
        debugPrint("enter trans_ExtDef in startInterCode");
        insertIR(trans_ExtDef(node));
        node = node->rightbrother;
    }

    return codeHead;
}

struct CodeList* concat(struct CodeList* cl1, struct CodeList* cl2){
    struct CodeList* tmpCl = cl1;
    if (cl1 == NULL)
        return cl2;
    if (cl2 == NULL)
        return cl1;
    while (tmpCl->next != NULL){
        tmpCl = tmpCl->next;
    }
    tmpCl->next = cl2;
    cl2->last = tmpCl;
    return cl1;
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

struct CodeList* makeCodeList(struct InterCode* interCode){
    struct CodeList* cl = (struct CodeList*)malloc(sizeof(struct CodeList));
    cl->interCode = interCode;
    cl->last = NULL;
    cl->next = NULL;
    return cl;
}

struct CodeList* makeParamCl(struct Operand* operand){
    struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
    ic->icType = IC_PARAM;
    ic->info.paramOp = operand;
    struct CodeList* cl = (struct CodeList*)malloc(sizeof(struct CodeList));
    cl->interCode = ic;
    cl->last = NULL;
    cl->next = NULL;
    return cl;
}

struct CodeList* trans_FunDec(struct Node* node){
    debugPrint("start of trans_FunDec");
    if (node == NULL){
        debugPrint("node is NULL in trans_FunDec");
        return NULL;
    }
    if (child->rightbrother->rightbrother->rightbrother == NULL){//ID LP RP
        struct InterCode* interCode = makeIc(NULL, NULL, NULL, IC_FUNCTION);
        strcpy(interCode->info.funcName, child->strval);
        struct CodeList codeList = makeCodeList(interCode);
        return codeList;
    }
    struct InterCode* interCode = makeInterCode(NULL, NULL, NULL, IR_FUNCTION);
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
            struct Operand* tmpOp = makeOperand(OP_VARIABLE);
            tmpOp->type = fl->type;
            tmpOp->isParam = 1;
            strcpy(tmpOp->name, fl->name);
            insertOperandHashNode(fl->name, tmpOp);
            struct CodeList* tmpCl = makeParamCl(tmpOp);
            codeList = concat(codeList, tmmCl);
            fl = fl->next;
        }else{
            struct Operand* tmpOp = NULL;
            if (fl->type->type == STRUCTURE)
            	tmpOp = makeOperand(OP_STRUCTURE);
            else if (fl->type->type == ARRAY)
            	tmpOp = makeOperand(OP_ARRAY);
            tmpOp->type = fl->type;
            tmpOp->isParam = 1;
            strcpy(tmpOp->name, fl->name);
            insertOperandHashNode(fl->name, tmpOp);
            struct CodeList* tmpCl = makeParamCl(tmpOp);
            codeList = concat(codeList, tmmCl);
            fl = fl->next;
        }
    }
    return codeList;
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

struct CodeList* trans_DefList(struct Node* node){
    if (node == NULL)
        return NULL;
    struct CodeList* cl1 = NULL;
    while (node != NULL){
        cl1 = concat(cl1, trans_Def(node->leftchild));
        node = node->leftchild->rightbrother;
    }
    return cl1;
}

struct CodeList* trans_Def(struct Node* node){
    struct Node* child = node->leftchild;
    struct Operand* op = trans_Specifier(child);
    return trans_DecList(child->rightbrother, op);
}

struct Operand* trans_Specifier(struct Node* node){
    if (node == NULL)
        return NULL;
    struct Node* child = node->leftchild;

    
    struct Operand* op = makeOperand(OP_VARIABLE);
    return op;
}

struct CodeList* trans_DecList(struct Node* node, struct Operand* operand){
    if (node == NULL)
        return NULL;
    struct CodeList* cl1 = trans_Dec(node->leftchild, operand);
    struct CodeList* cl2 = trans_DecList(node->leftchild->rightbrother->rightbrother, operand);
    return concat(cl1, cl2);
}

struct CodeList* trans_Dec(struct Node* node, struct Operand* operand){
    struct Node* child = node->leftchild;
    if (child->rightbrother == NULL){//VarDec
            trans_VarDec(child, operand);
            return NULL;
    }
    else{//VarDec ASSIGNOP Exp
        trans_VarDec(child, operand);
        struct Operand* op1 = makeOperand(OP_TEMP);
        struct CodeList* cl1 = trans_Exp(child->right, operand);
        struct InterCode* ic1 = makeInterCode(IC_ASSIGN);
        ic1->info.assign.leftOp = operand;
        ic1->info,assign.rightOp = op1;
        struct CodeList* cl2 = makeCodeList(ic1);
        return concat(cl1, cl2);
    }
}

void trans_VarDec(struct Node* node, struct Operand* operand){
    if(node == NULL)
        return NULL;
    struct Node* child = node->leftchild;

    if (child->rightbrother == NULL){// ID
        strcpy(operand->name, child->strval);
        insertOperandHashNode(child->strval, operand);
        return ;
    }
    //VarDec LB INT RB
    struct Operand* op = (struct Operand*)malloc(sizeof(struct Operand));
    op->opType = OP_ARRAY;
    op->info.variableNo = operand->info.variableNo;
    struct TypeNode* typeArr = (struct TypeNode*)malloc(sizeof(struct TypeNode));
    typeArr->type = ARRAY;
    typeArr->info.array.size = child->rightbrother->rightbrother->intval;
    typeArr->info.array.type = operand->type;
    op->type = typeArr;
    trans_VarDec(child, op);
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

struct InterCode* makeIc(struct Operand* valOperand, struct Operand* leftOperand, struct Operand* rightOperand, enum IcType icType){
    if (icType == IC_RETURN){
    	struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
    	ic->icType = icType;
    	ic->info.retOp = leftOperand;
    	return ic;
    }
    if (icType == IC_LABEL){
    	struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
    	ic->icType = icType;
    	ic->info.labelNo = leftOperand->info.labelNo;
    	return ic;
    }
    if (icType == IC_FUNCTION){
    	struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
    	ic->icType = icType;
    	return ic;
    }
    if (icType == IC_GOTO){
    	struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
    	ic->icType = icType;
    	ic->info.gotoNo = leftOperand->info.labelNo;
    	return ic;
    }
    if (icType ==  IC_ASSIGN){
    	struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
    	ic->icType = icType;
    	ic->info.assign.leftOp = leftOperand;
    	ic->info.assign.rightOp = rightOperand;
    	return ic;
    }
    if (icType ==  IC_ASSIGN_ADDR){
    	struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
    	ic->icType = icType;
    	ic->info.assignAddr.leftOp = leftOperand;
    	ic->info.assignAddr.rightOp = rightOperand;
    	return ic;
    }
    if (icType == IC_ADD || icType == IC_SUB || icType == IC_MUL || icType == IC_DIV){
        struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
    	ic->icType = icType;
    	ic->info.binOp.result = valOperand;
    	ic->info.binOp.op1 = leftOperand;
    	ic->info.binOp.op2 = rightOperand;
    	return ic;
    }
    if (icType == IC_READ){
    
    }
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
        struct Operand* operand = makeOperand(OP_TEMP);
        struct CodeList* cl1 = trans_Exp(child->rightbrother, operand);
        struct CodeList* cl2 = makeCodeList(makeIc(NULL, operand, NULL, IC_RETURN));
        return concat(cl1, cl2);
    }
    if (strcmp(child->name, "IF") == 0 && child->rightbrother->rightbrother->rightbrother->rightbrother->rightbrother == NULL){//IF LP Exp RP Stmt
        struct Operand* op1 = makeOperand(OP_LABEL);
        struct Operand* op2 = makeOperand(OP_LABEL);
        struct CodeList* cl1 = trans_Cond(child->rightbrother->rightbrother, op1, op2);
        struct CodeList* cl2 = trans_Stmt(child->rightbrother->rightbrother->rightbrother->rightbrother);
        struct CodeList* cl3 = makeCodeList(makeIc(NULL, op1, NULL, IC_LABEL));
        struct CodeList* cl4 = makeCodeList(makeIc(NULL, op2, NULL, IC_LABEL));
        return concat(concat(cl1, cl3), concat(cl2, cl4));
    }
    else if (strcmp(child->name, "IF") == 0){//IF LP Exp RP Stmt ElSE Stmt
        struct Operand* op1 = makeOperand(OP_LABEL);
        struct Operand* op2 = makeOperand(OP_LABEL);
        struct Operand* op3 = makeOperand(OP_LABEL);
        struct CodeList* cl1 = trans_Cond(child->rightbrother->rightbrother, op1, op2);
        struct CodeList* cl2 = trans_Stmt(child->rightbrother->rightbrother->rightbrother->rightbrother);
        struct CodeList* cl3 = makeCodeList(makeIc(NULL, op1, NULL, IC_LABEL));
        struct CodeList* cl4 = makeCodeList(makeIc(NULL, op2, NULL, IC_LABEL));
        struct CodeList* cl5 = trans_Stmt(child->rightbrother->rightbrother->rightbrother->rightbrother->rightbrother->rightbrother);
        struct CodeList* cl6 = makeCodeList(makeIc(NULL, op3, NULL, IC_LABEL));
        struct CodeList* cl7 = makeCodeList(makeIc(NULL, op3, NULL, IC_GOTO));
        return concat(concat(concat(cl1, cl3), concat(cl2, cl7)), concat(concat(cl4, cl5), cl6));
    }
    if (strcmp(child->name, "WHILE") == 0){//WHILE LP Exp RP Stmt
        struct Operand* op1 = makeOperand(OP_LABEL);
        struct Operand* op2 = makeOperand(OP_LABEL);
        struct Operand* op3 = makeOperand(OP_LABEL);
        struct CodeList* cl1 = trans_Cond(child->rightbrother->rightbrother, op2, op3);
        struct CodeList* cl2 = trans_Stmt(child->rightbrother->rightbrother->rightbrother->rightbrother);
        struct CodeList* cl3 = makeCodeList(makeIc(NULL, op1, NULL, IC_LABEL));
        struct CodeList* cl4 = makeCodeList(makeIc(NULL, op2, NULL, IC_LABEL));
        struct CodeList* cl5 = makeCodeList(makeIc(NULL, op3, NULL, IC_LABEL));
        struct CodeList* cl6 = makeCodeList(makeIc(NULL, op1, NULL, IC_GOTO));
        return concat(concat(concat(cl3, cl1), concat(cl4, cl2)), concat(cl6, cl5));
    }
    return NULL;
}

struct InterCode* makeIfIc(char* relOp, struct Operand* operand1, struct Operand* operand2, struct Operand* trueLabel){
    struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
    ic->icType == IC_RELOP_GOTO;
    syrcpy(ic->info.relGoto.relOp, relOp);
    ic->info.relGoto.leftRelOp = operand1;
    ic->info.relGoto.rightRelOp = operand2;
    ic->info.relGoto.gotoNo = trueLabel->info.labelNo;
    return ic;
}

struct CodeList* trans_Cond(struct Node* node, struct Operand* trueLabel, struct Operand* falseLabel){
    struct Node* child = node->leftchild;
    if (strcmp(child->name, "Exp") == 0 && strcmp(child->rightbrother->name, "RELOP") == 0){
        struct Operand* op1 = makeOperand(OP_TEMP);
        struct Operand* op2 = makeOperand(OP_TEMP);
        struct CodeList* cl1 = trans_Exp(child, op1);
        struct CodeList* cl2 = trans_Exp(child->rightbrother->rightbrother, op2);
        struct CodeList* cl3 = makeCodeList(makeIfIc(child->rightbrother->strval, op1, op2, trueLabel));
        struct CodeList* cl4 = makeCodeList(makeIc(NULL, falseLabel, NULL, IC_GOTO));
        return concat(concat(cl1, cl2), concat(cl3, cl4));
    }
    if (strcmp(child->name, "NOT") == 0){//NOT Exp
        return trans_Cond(child->rightbrother, falseLabel, trueLabel);
    }
    if (strcmp(child->name, "Exp") == 0 && strcmp(child->rightbrother->name, "AND") == 0){
        struct Operand* label1 = makeOperand(OP_LABEL);
        struct CodeList* cl1 = trans_Cond(child, label1, falseLabel);
        struct CodeList* cl2 = trans_Cond(child->rightbrother->rightbrother, trueLabel, falseLabel);
        struct CodeList* cl3 = makeCodeList(makeIc(NULL, label1, NULL, IC_LABEL));
        return concat(concat(cl1, cl3), cl2);
    }
    if (strcmp(child->name, "Exp") == 0 && strcmp(child->rightbrother->name, "OR") == 0){//Exp OR Exp
        struct Operand* label1 = makeOperand(OP_LABEL);
        struct CodeList* cl1 = trans_Cond(child, trueLabel, label1);
        struct CodeList* cl2 = trans_Cond(child->rightbrother->rightbrother, trueLabel, falseLabel);
        struct CodeList* cl3 = makeCodeList(makeIc(NULL, label1, NULL, IC_LABEL));
        return concat(concat(cl1, cl3), cl2);
    }
    //else
    struct Operand* op1 = makeOperand(OP_TEMP);
    struct CodeList* cl1 = trans_Exp(node, op1);
    struct CodeList* cl2 = makeIfIc("!=", op1, constZero, trueLabel);
    struct CodeList* cl3 = makeCodeList(makeIc(NULL, falseLabel,  NULL, IC_GOTO));
    return concat(concat(cl1, cl2), cl3);
}



struct CodeList* trans_Exp(struct Node* node, struct Operand* operand){
    debugPrint("start of trans_Exp");
    struct Node* child = node->leftchild;
    if (strcmp(child->name, "ID") == 0 && child->rightbrother == NULL){//ID
        struct Operand* op = lookUpOperand(str);
        if (op->opType == OP_ARRAY && op->opType == OP_STRUCT){
            struct InterCode* ic = makeIc(NULL, operand, op, IC_ASSIGN_ADDR);
            return makeCodeList(ic);
        }else{
            struct InterCode* ic = makeIc(NULL, operand, op, IC_ASSIGN);
            return makeCodeList(ic);
        }
    }
    if (strcmp(child->name, "INT") == 0 || strcmp(child->name, "FLOAT") == 0){//INT || FLOAT
        int intVal = child->intval;
        struct Operand* constOp = makeOperand(OP_CONSTANT);
        constOp->info.val = intVal;
        struct InterCode* ic = makeIc(NULL, operand, constOp, IC_ASSIGN);
        return makeCodeList(ic);
    }
    if (strcmp(child->name, "Exp") == 0 && strcmp(child->rightbrother->rightbrother->name, "Exp") == 0 && child->rightbrother->rightbrother->rightbrother == NULL){//Exp op Exp
        
        if (strcmp(child->rightbrother->name, "ASSIGNOP") == 0){
            if (strcmp(child->leftchild->name, "ID") == 0){//ID ASSIGN Exp
            	struct Operand* tmpOp2 = makeOperand(OP_TEMP);
            	struct Operand* leftVari = lookUpOperand(child->leftchild->strval);
            	struct CodeList* cl1 = trans_Exp(child->rightbrother->rightbrother, tmpOp2);
            	struct CodeList* cl2 = makeCodeList(makeIc(NULL, leftVari, tmpOp2, IC_ASSIGN));
            	struct CodeList* cl3 = makeCodeList(makeIc(NULL, operand, leftVari, IC_ASSIGN));
            	return  concat(cl1, concat(cl2, cl3));
            }
            else{//Exp ASSIGN Exp
            	
            }
        }
        else if (strcmp(child->rightbrother->name, "AND") == 0){
            struct Operand* label1 = makeOperand(OP_LABEL);
            struct Operand* label2 = makeOperand(OP_LABEL);
            struct CodeList* cl1 = makeCodeList(makeIc(NULL, operand, constZero, IC_ASSIGN));
            struct CodeList* cl2 = trans_cond(node, label1, label2);
            struct CodeList* cl3 = makeCodeList(makeIc(NULL, label1, NULL, IC_LABEL));
            struct CodeList* cl4 = makeCodeList(makeIc(NULL, operand, constOne, IC_ASSIGN));
            struct CodeList* cl5 = makeCodeList(makeIc(NULL, label2, NULL, IC_LABEL));
            return concat(concat(concat(concat(cl1, cl2), cl3), cl4), cl5);
        }
        else if (strcmp(child->rightbrother->name, "OR") == 0){
            struct Operand* label1 = makeOperand(OP_LABEL);
            struct Operand* label2 = makeOperand(OP_LABEL);
            struct CodeList* cl1 = makeCodeList(makeIc(NULL, operand, constZero, IC_ASSIGN));
            struct CodeList* cl2 = trans_cond(node, label1, label2);
            struct CodeList* cl3 = makeCodeList(makeIc(NULL, label1, NULL, IC_LABEL));
            struct CodeList* cl4 = makeCodeList(makeIc(NULL, operand, constOne, IC_ASSIGN));
            struct CodeList* cl5 = makeCodeList(makeIc(NULL, label2, NULL, IC_LABEL));
            return concat(concat(concat(concat(cl1, cl2), cl3), cl4), cl5);
        }
        else if (strcmp(child->rightbrother->name, "RELOP") == 0){
            struct Operand* label1 = makeOperand(OP_LABEL);
            struct Operand* label2 = makeOperand(OP_LABEL);
            struct CodeList* cl1 = makeCodeList(makeIc(NULL, operand, constZero, IC_ASSIGN));
            struct CodeList* cl2 = trans_cond(node, label1, label2);
            struct CodeList* cl3 = makeCodeList(makeIc(NULL, label1, NULL, IC_LABEL));
            struct CodeList* cl4 = makeCodeList(makeIc(NULL, operand, constOne, IC_ASSIGN));
            struct CodeList* cl5 = makeCodeList(makeIc(NULL, label2, NULL, IC_LABEL));
            return concat(concat(concat(concat(cl1, cl2), cl3), cl4), cl5);
        }
        else if (strcmp(child->rightbrother->name, "PLUS") == 0){
            struct Operand* tmpOp1 = makeOperand(OP_TEMP);
            struct Operand* tmpOp2 = makeOperand(OP_TEMP);
            struct CodeList* cl1 = trans_Exp(child, tmpOp1);
            struct CodeList* cl2 = trans_Exp(child->rightbrother->rightbrother, tmpOp2);
            struct CodeList* cl3 = makeCodeList(makeIc(operand, tmpOp1, tmpOp2, IC_ADD));
            return concat(concat(cl1, cl2), cl3);
        }
        else if (strcmp(child->rightbrother->name, "MINUS") == 0){
            struct Operand* tmpOp1 = makeOperand(OP_TEMP);
            struct Operand* tmpOp2 = makeOperand(OP_TEMP);
            struct CodeList* cl1 = trans_Exp(child, tmpOp1);
            struct CodeList* cl2 = trans_Exp(child->rightbrother->rightbrother, tmpOp2);
            struct CodeList* cl3 = makeCodeList(makeIc(operand, tmpOp1, tmpOp2, IC_SUB));
            return concat(concat(cl1, cl2), cl3);
        }
        else if (strcmp(child->rightbrother->name, "STAR") == 0){
            struct Operand* tmpOp1 = makeOperand(OP_TEMP);
            struct Operand* tmpOp2 = makeOperand(OP_TEMP);
            struct CodeList* cl1 = trans_Exp(child, tmpOp1);
            struct CodeList* cl2 = trans_Exp(child->rightbrother->rightbrother, tmpOp2);
            struct CodeList* cl3 = makeCodeList(makeIc(operand, tmpOp1, tmpOp2, IC_MUL));
            return concat(concat(cl1, cl2), cl3);
        }
        else if (strcmp(child->rightbrother->name, "DIV") == 0){
            struct Operand* tmpOp1 = makeOperand(OP_TEMP);
            struct Operand* tmpOp2 = makeOperand(OP_TEMP);
            struct CodeList* cl1 = trans_Exp(child, tmpOp1);
            struct CodeList* cl2 = trans_Exp(child->rightbrother->rightbrother, tmpOp2);
            struct CodeList* cl3 = makeCodeList(makeIc(operand, tmpOp1, tmpOp2, IC_DIV));
            return concat(concat(cl1, cl2), cl3);
        }
    }
    if (strcmp(child->name, "LP") == 0){//LP Exp RP
        struct CodeList* cl1 = trans_Exp(child->rightbrother, operand);
        return cl1;
    }
    if (strcmp(child->name, "MINUS") == 0){//MINUS Exp
        struct Operand* tmp1 = makeOperand(OP_TEMP);
        struct CodeList* cl1 = trans_Exp(child->rightbrother, tmp1);
        struct CodeList* cl2 = makeCodeList(makeIc(operand, constZero, tmp1, IC_SUB));
        return concat(cl1, cl2);
    }
    if (strcmp(child->name, "NOT") == 0){//NOT Exp
        struct Operand* label1 = makeOperand(OP_LABEL);
        struct Operand* label2 = makeOperand(OP_LABEL);
        struct CodeList* cl1 = makeCodeList(makeIc(NULL, operand, constZero, IC_ASSIGN));
        struct CodeList* cl2 = trans_cond(node, label1, label2);
        struct CodeList* cl3 = makeCodeList(makeIc(NULL, label1, NULL, IC_LABEL));
        struct CodeList* cl4 = makeCodeList(makeIc(NULL, operand, constOne, IC_ASSIGN));
        struct CodeList* cl5 = makeCodeList(makeIc(NULL, label2, NULL, IC_LABEL));
        return concat(concat(concat(concat(cl1, cl2), cl3), cl4), cl5);
    }
    if (strcmp(child->name, "ID") == 0 && strcmp(child->rightbrother->name, "LP") == 0 && strcmp(child->rightbrother->rightbrother->name, "RP") == 0){//ID LP RP
        struct HashNode* tmpHash = hashFind(child->strval);
        if (tmpHash == NULL)
            return NULL;
        struct Function* func = tmpHash->type->info.function;
        if (strcmp(func->name, "read") == 0){
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
    if (strcmp(child->name, "Exp") == 0 && strcmp(child->rightbrother, "DOT") == 0){//Exp DOT ID
        struct Operand* baseOp = makeTempOperand();
        baseOp->opType = OP_ADDRESS;
        struct CodeList* cl1 = trans_Exp(child, baseOp);
        struct Operand* finalAddr = makeTempOperand();
        struct InterCode* ic = makeInterCode(IC_ADDRESS);
        ic->info.binOp.result = finalAddr;
        ic->info.binOp.op1 = baseOp;
        ic->info.binOp.op2 = sizeOfStruct(child->rightbrother->rightbrother->strval);
        struct CodeList* cl2 = makeCodeList(ic);
        struct InterCode* ic2 = makeInterCode(IC_ASSIGN);
        ic2->info.assign.leftOp = operand;
        ic2->info.assign.rightOp = finalAddr;
        struct CodeList* cl3 = makeCodeList(ic2);
        return concat(concat(cl1, cl2), cl3);
    }
    if (strcmp(child->name, "Exp") == 0 && strcmp(child->rightbrother->name, "LB") == 0){//Exp LB Exp RB
        struct Operand* baseOp = makeTempOperand();
        baseOp->opType = OP_ADDRESS;
        struct Operand* tmpOp = lookUpOperand(child->leftchild->strval);
        struct InterCode* ic1 = makeInterCode(IC_ASSIGN);
        ic1->info.assign.leftOp = baseOp;
        ic1->info.assign.rightOp = tmpOp;
        struct CodeList* cl1 = makeCodeList(ic1);
        struct Operand* offset = makeTempOperand();
        struct Operand* finalAddr = makeTempOperand();
        finalAddr->opType = OP_ADDR;
        struct CodeList* cl2 = trans_Exp(child->rightbrother->rightbrother, offset);
        ic1 = makeInterCode(IC_MUL);
        ic1->info.binOp.result = offset;
        ic1->info.binOp.op1 = offset;
        ic1->info.binOp.op2 = constFour;
        struct CodeList* cl3 = makeCodeList(ic1);
        ic1 = makeInterCode(IC_ADDRESS);
        ic1->info.binOp.result = finalAddr;
        ic1->info.binOp.op1 = baseOp;
        ic1->info.binOp.op2 = offset;
        struct CodeList* cl4 = makeCodeList(ic1);
        ic1 = makeInterCode(IC_ASSIGN);
        ic1->info.leftOp = operand;
        ic1->info.rightOp = finalAddr;
        struct CodeList* cl5 = makeCodeList(ic1);
        return concat(concat(concat(concat(cl1, cl2), cl3), cl4), cl5);
    }

}

struct CodeList* trans_Args(struct Node* node, struct ArgList* args, struct FieldList* fieldList){
    struct Node* child = node->leftchild;
    if (strcmp(child->name, "Exp") == 0 && child->rightbrother == NULL){//Exp
        struct Operand* op1 = makeTempOperand();
        if (fieldList != NULL && (fieldList->type->type == ARRAY || fieldList->type->type == STRUCTURE))
            op1->opType = OP_ADDRESS;
        struct CodeList* cl1 = trans_Exp(child, op1);
        struct ArgList* newArg = (struct ArgList*)malloc(sizeof(struct ArgList));
        newArg->args = op1;
        newArg->next = args;
        args = newArg;
        return cl1;
    }
    //Exp COMMA Args
    struct Operand* op1 = makeTempOperand();
    if (fieldList != NULL && (fieldList->type->type == ARRAY || fieldList->type->type == STRUCTURE))
            op1->opType = OP_ADDRESS;
    struct CodeList* cl1 = trans_Exp(child, op1);
    struct ArgList* newArg = (struct ArgList*)malloc(sizeof(struct ArgList));
    newArg->args = op1;
    newArg->next = args;
    args = newArg;
    if (fieldList != NULL)
        fieldList = fieldList->next;
    struct CodeList* cl2 = trans_Args(child->rightbrother->rightbrother, newArg, fieldList);
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

struct Operand* lookUpOperand(char* name){
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

struct Operand* makeOperand(enum OpType opType){
    struct Operand* op = (struct Operand*)malloc(sizeof(struct Operand));
    op->opType = opType;
    op->type = NULL;
    op->isParam = 0;
    if (opType == OP_VARIABLE){
        op->info.variableNo = variableNum;
        variableNum += 1;
        return op;
    }
    if (opType == OP_LABEL){
        op->info.labelNo = labelNum;
        labelNum += 1;
        return op;
    }
    if (opType == OP_TEMP){
        op->info.tempNo = tempNum;
        tempNum += 1;
        return op;
    }
    return op;
}


