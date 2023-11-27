#ifndef IR_ENABLE
#define IR_ENABLE
#include "irfile.h"
#endif

void insertIR(struct CodeList* codeList){
    if (codeHead == NULL){
        codeHead = codeList;
        codeTail = codeHead;
        while (codeTail->next != NULL){
            /*if (DEBUG_FLAG2){
                printf("cotail:%d\n", codeTail);
            }*/
            codeTail = codeTail->next;
        }
        //debugPrint("live3");
        return;
    }
    //debugPrint("live4");
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
    
    constFour = makeOperand(OP_CONSTANT);
    constFour->info.val = 4;
    
    

    struct Node* node = rootNode->leftchild;
    while (node != NULL){
        node = node->leftchild;
        debugPrint("enter trans_ExtDef in startInterCode");
        insertIR(trans_ExtDef(node));
        //debugPrint("live7");
        node = node->rightbrother;
    }

    return codeHead;
}

void writeIR(struct CodeList* codeList, FILE* pFile){
    debugPrint("start writeIR");
    int i = 0;
    while (codeList != NULL){
        if (DEBUG_FLAG2){
            i++;
            printf("%d\n", i);
            if (i == 7){
                //printf("%d\n", codeList->interCode->info.assign.leftOp->opType);
                //return;
            }
        }
        struct InterCode* ic;
        ic = codeList->interCode;
        char valStr[2];
        char op1Str[2];
        char op2Str[2];
    	if (ic->icType == IC_LABEL){
    	    debugPrint("label");
    	    fprintf(pFile, "LABEL label%d :\n", ic->info.labelNo);
 	    codeList = codeList->next;
 	    continue;
    	}
    	if (ic->icType == IC_FUNCTION){
    	    fprintf(pFile, "FUNCTION %s :\n", ic->info.funcName);
    	    codeList = codeList->next;
 	    continue;
    	}
    	if (ic->icType == IC_ASSIGN){
    	    debugPrint("assign");
    	    //printf("ic: %d\n", ic->info.assign);
    	    int op1Int, op2Int;
    	    if (ic->info.assign.leftOp->opType == OP_VARIABLE || ic->info.assign.leftOp->vt == 0){
    	        //debugPrint("1");
    	    	op1Str[0] = 'v';
    	    	op1Str[1] = '\0';
    	    	op1Int = ic->info.assign.leftOp->info.variableNo;
    	    }
    	    else if (ic->info.assign.leftOp->opType == OP_TEMP || ic->info.assign.leftOp->vt == 1){
    	    	//debugPrint("2");
    	    	op1Str[0] = 't';
    	    	op1Str[1] = '\0';
    	    	op1Int = ic->info.assign.leftOp->info.tempNo;
    	    }
    	    else if (ic->info.assign.leftOp->opType == OP_CONSTANT){
    	    	//debugPrint("3");
    	    	op1Str[0] = '#';
    	    	op1Str[1] = '\0';
    	    	op1Int = ic->info.assign.leftOp->info.val;
    	    	//debugPrint("1");
    	    }
    	    //debugPrint("11");
    	    //debugPrint("11");
    	    debugPrint("live");
    	    //printf("ic: %d\n", ic->info.assign);
    	    if (ic->info.assign.rightOp->opType == OP_VARIABLE || ic->info.assign.rightOp->vt == 0){
    	    	op2Str[0] = 'v';
    	    	op2Str[1] = '\0';
    	    	op2Int = ic->info.assign.rightOp->info.variableNo;
    	    }
    	    else if (ic->info.assign.rightOp->opType == OP_TEMP || ic->info.assign.rightOp->vt == 1){
    	    	op2Str[0] = 't';
    	    	op2Str[1] = '\0';
    	    	op2Int = ic->info.assign.rightOp->info.tempNo;
    	    }
    	    else if (ic->info.assign.rightOp->opType == OP_CONSTANT){
    	    	op2Str[0] = '#';
    	    	op2Str[1] = '\0';
    	    	op2Int = ic->info.assign.rightOp->info.val;
    	    }
    	    //debugPrint("11");
    	    fprintf(pFile, "%s%d := %s%d\n", op1Str, op1Int, op2Str, op2Int);
    	    codeList = codeList->next;
    	    debugPrint("assign continue");
 	    continue;
    	}
    	if (ic->icType == IC_ASSIGN_ADDR){
    	    int op1Int, op2Int;
    	    if (ic->info.assign.leftOp->vt == 0){
    	    	op1Str[0] = 'v';
    	    	op1Str[1] = '\0';
    	    	op1Int = ic->info.assign.leftOp->info.variableNo;
    	    }
    	    else if (ic->info.assign.leftOp->vt == 1){
    	    	op1Str[0] = 't';
    	    	op1Str[1] = '\0';
    	    	op1Int = ic->info.assign.leftOp->info.tempNo;
    	    }
    	    if (ic->info.assign.rightOp->vt == 0){
    	    	op2Str[0] = 'v';
    	    	op2Str[1] = '\0';
    	    	op2Int = ic->info.assign.rightOp->info.variableNo;
    	    }
    	    else if (ic->info.assign.rightOp->vt == 1){
    	    	op2Str[0] = 't';
    	    	op2Str[1] = '\0';
    	    	op2Int = ic->info.assign.rightOp->info.tempNo;
    	    }
  	    fprintf(pFile, "%s%d := &%s%d\n", op1Str, op1Int, op2Str, op2Int);
  	    codeList = codeList->next;
 	    continue;
    	}
    	if (ic->icType == IC_ASSIGN_ADDR_VAL){
    	    int op1Int, op2Int;
    	    if (ic->info.assign.leftOp->vt == 0){
    	    	op1Str[0] = 'v';
    	    	op1Str[1] = '\0';
    	    	op1Int = ic->info.assign.leftOp->info.variableNo;
    	    }
    	    else if (ic->info.assign.leftOp->vt == 1){
    	    	op1Str[0] = 't';
    	    	op1Str[1] = '\0';
    	    	op1Int = ic->info.assign.leftOp->info.tempNo;
    	    }
    	    if (ic->info.assign.rightOp->vt == 0){
    	    	op2Str[0] = 'v';
    	    	op2Str[1] = '\0';
    	    	op2Int = ic->info.assign.rightOp->info.variableNo;
    	    }
    	    else if (ic->info.assign.rightOp->vt == 1){
    	    	op2Str[0] = 't';
    	    	op2Str[1] = '\0';
    	    	op2Int = ic->info.assign.rightOp->info.tempNo;
    	    }
  	    fprintf(pFile, "%s%d := *%s%d\n", op1Str, op1Int, op2Str, op2Int);
  	    codeList = codeList->next;
 	    continue;
    	}
    	if (ic->icType == IC_ADDR_ASSIGN_VAL){
    	    int op1Int, op2Int;
    	    if (ic->info.assign.leftOp->vt == 0){
    	    	op1Str[0] = 'v';
    	    	op1Str[1] = '\0';
    	    	op1Int = ic->info.assign.leftOp->info.variableNo;
    	    }
    	    else if (ic->info.assign.leftOp->vt == 1){
    	    	op1Str[0] = 't';
    	    	op1Str[1] = '\0';
    	    	op1Int = ic->info.assign.leftOp->info.tempNo;
    	    }
    	    if (ic->info.assign.rightOp->vt == 0){
    	    	op2Str[0] = 'v';
    	    	op2Str[1] = '\0';
    	    	op2Int = ic->info.assign.rightOp->info.variableNo;
    	    }
    	    else if (ic->info.assign.rightOp->vt == 1){
    	    	op2Str[0] = 't';
    	    	op2Str[1] = '\0';
    	    	op2Int = ic->info.assign.rightOp->info.tempNo;
    	    }
  	    fprintf(pFile, "*%s%d := %s%d\n", op1Str, op1Int, op2Str, op2Int);
  	    codeList = codeList->next;
 	    continue;
    	}
    	if (ic->icType == IC_ADD || ic->icType == IC_SUB || ic->icType == IC_MUL || ic->icType == IC_DIV){
    	    int valInt, op1Int, op2Int;
    	    if (ic->info.binOp.result->opType == OP_VARIABLE || ic->info.binOp.result->vt == 0){
    	    	valStr[0] = 'v';
    	    	valStr[1] = '\0';
    	    	valInt = ic->info.binOp.result->info.variableNo;
    	    }
    	    else if (ic->info.binOp.result->opType == OP_TEMP || ic->info.binOp.result->vt == 1){
    	    	valStr[0] = 't';
    	    	valStr[1] = '\0';
    	    	valInt = ic->info.binOp.result->info.tempNo;
    	    }
    	    if (ic->info.binOp.op1->opType == OP_VARIABLE || ic->info.binOp.op1->vt == 0){
    	    	op1Str[0] = 'v';
    	    	op1Str[1] = '\0';
    	    	op1Int = ic->info.binOp.op1->info.variableNo;
    	    }
    	    else if (ic->info.binOp.op1->opType == OP_TEMP || ic->info.binOp.op1->vt == 1){
    	    	op1Str[0] = 't';
    	    	op1Str[1] = '\0';
    	    	op1Int = ic->info.binOp.op1->info.tempNo;
    	    }
    	    else if (ic->info.binOp.op1->opType == OP_CONSTANT){
    	    	op1Str[0] = '#';
    	    	op1Str[1] = '\0';
    	    	op1Int = ic->info.binOp.op1->info.val;
    	    }
    	    if (ic->info.binOp.op2->opType == OP_VARIABLE || ic->info.binOp.op2->vt == 0){
    	    	op2Str[0] = 'v';
    	    	op2Str[1] = '\0';
    	    	op2Int = ic->info.binOp.op2->info.variableNo;
    	    }
    	    else if (ic->info.binOp.op2->opType == OP_TEMP || ic->info.binOp.op2->vt == 1){
    	    	op2Str[0] = 't';
    	    	op2Str[1] = '\0';
    	    	op2Int = ic->info.binOp.op2->info.tempNo;
    	    }
    	    else if (ic->info.binOp.op2->opType == OP_CONSTANT){
    	    	op2Str[0] = '#';
    	    	op2Str[1] = '\0';
    	    	op2Int = ic->info.binOp.op2->info.val;
    	    }
    	    if (ic->icType == IC_ADD)
    	    	fprintf(pFile, "%s%d := %s%d + %s%d\n", valStr, valInt, op1Str, op1Int, op2Str, op2Int);
    	    else if (ic->icType == IC_SUB)
    	    	fprintf(pFile, "%s%d := %s%d - %s%d\n", valStr, valInt, op1Str, op1Int, op2Str, op2Int);
    	    else if (ic->icType == IC_MUL)
    	    	fprintf(pFile, "%s%d := %s%d * %s%d\n", valStr, valInt, op1Str, op1Int, op2Str, op2Int);
    	    else if (ic->icType == IC_DIV)
    	    	fprintf(pFile, "%s%d := %s%d / %s%d\n", valStr, valInt, op1Str, op1Int, op2Str, op2Int);
    	    codeList = codeList->next;
 	    continue;
    	}
    	if (ic->icType == IC_GOTO){
    	    fprintf(pFile, "GOTO label%d\n", ic->info.gotoNo);
    	    codeList = codeList->next;
 	    continue;
    	}
    	if (ic->icType == IC_RELOP_GOTO){
    	    int op1Int, op2Int;
    	    if (ic->info.relGoto.leftRelOp->opType == OP_VARIABLE){
    	    	op1Str[0] = 'v';
    	    	op1Str[1] = '\0';
    	    	op1Int = ic->info.relGoto.leftRelOp->info.variableNo;
    	    }
    	    else if (ic->info.relGoto.leftRelOp->opType == OP_TEMP){
    	    	op1Str[0] = 't';
    	    	op1Str[1] = '\0';
    	    	op1Int = ic->info.relGoto.leftRelOp->info.tempNo;
    	    }
    	    else if (ic->info.relGoto.leftRelOp->opType == OP_CONSTANT){
    	    	op1Str[0] = '#';
    	    	op1Str[1] = '\0';
    	    	op1Int = ic->info.relGoto.leftRelOp->info.val;
    	    }
    	    if (ic->info.relGoto.rightRelOp->opType == OP_VARIABLE){
    	    	op2Str[0] = 'v';
    	    	op2Str[1] = '\0';
    	    	op2Int = ic->info.relGoto.rightRelOp->info.variableNo;
    	    }
    	    else if (ic->info.relGoto.rightRelOp->opType == OP_TEMP){
    	    	op2Str[0] = 't';
    	    	op2Str[1] = '\0';
    	    	op2Int = ic->info.relGoto.rightRelOp->info.tempNo;
    	    }
    	    else if (ic->info.relGoto.rightRelOp->opType == OP_CONSTANT){
    	    	op2Str[0] = '#';
    	    	op2Str[1] = '\0';
    	    	op2Int = ic->info.relGoto.rightRelOp->info.val;
    	    }
    	    fprintf(pFile, "IF %s%d %s %s%d GOTO label%d\n", op1Str, op1Int, ic->info.relGoto.relOp, op2Str, op2Int, ic->info.relGoto.gotoNo);
    	    codeList = codeList->next;
 	    continue;
    	}
    	if (ic->icType == IC_RETURN){
    	    int valInt;
    	    if (ic->info.retOp->opType == OP_VARIABLE || ic->info.retOp->vt == 0){
    	    	valStr[0] = 'v';
    	    	valStr[1] = '\0';
    	    	valInt = ic->info.retOp->info.variableNo;
    	    }
    	    else if (ic->info.retOp->opType == OP_TEMP || ic->info.retOp->vt == 1){
    	    	valStr[0] = 't';
    	    	valStr[1] = '\0';
    	    	valInt = ic->info.retOp->info.tempNo;
    	    }
    	    fprintf(pFile, "RETURN %s%d\n", valStr, valInt);
    	    codeList = codeList->next;
 	    continue;
    	}
    	if (ic->icType == IC_DEC){
    	    int valInt;
    	    if (ic->info.dec.operand->opType == OP_VARIABLE || ic->info.dec.operand->vt == 0){
    	    	valStr[0] = 'v';
    	    	valStr[1] = '\0';
    	    	valInt = ic->info.dec.operand->info.variableNo;
    	    }
    	    else if (ic->info.dec.operand->opType == OP_TEMP || ic->info.dec.operand->vt == 1){
    	    	valStr[0] = 't';
    	    	valStr[1] = '\0';
    	    	valInt = ic->info.dec.operand->info.tempNo;
    	    }
    	    fprintf(pFile, "DEC %s%d %d\n", valStr, valInt, ic->info.dec.size);
    	    codeList = codeList->next;
 	    continue;
    	}
    	if (ic->icType == IC_ARG){
    	    int valInt;
    	    if (ic->info.argOp->opType == OP_VARIABLE || ic->info.argOp->vt == 0){
    	    	valStr[0] = 'v';
    	    	valStr[1] = '\0';
    	    	valInt = ic->info.argOp->info.variableNo;
    	    }
    	    else if (ic->info.argOp->opType == OP_TEMP || ic->info.argOp->vt == 1){
    	    	valStr[0] = 't';
    	    	valStr[1] = '\0';
    	    	valInt = ic->info.argOp->info.tempNo;
    	    }
    	    fprintf(pFile, "ARG %s%d\n", valStr, valInt);
    	    codeList = codeList->next;
 	    continue;
    	}
    	if (ic->icType == IC_CALL){
    	    int valInt;
    	    if (ic->info.funcCall.result->opType == OP_VARIABLE || ic->info.funcCall.result->vt == 0){
    	    	valStr[0] = 'v';
    	    	valStr[1] = '\0';
    	    	valInt = ic->info.funcCall.result->info.variableNo;
    	    }
    	    else if (ic->info.funcCall.result->opType == OP_TEMP || ic->info.funcCall.result->vt == 1){
    	    	valStr[0] = 't';
    	    	valStr[1] = '\0';
    	    	valInt = ic->info.funcCall.result->info.tempNo;
    	    }
    	    fprintf(pFile, "%s%d := CALL %s\n", valStr, valInt, ic->info.funcCall.function);
    	    codeList = codeList->next;
 	    continue;
    	}
    	if (ic->icType == IC_PARAM){
    	    int valInt;
    	    if (ic->info.paramOp->opType == OP_VARIABLE || ic->info.paramOp->vt == 0){
    	    	valStr[0] = 'v';
    	    	valStr[1] = '\0';
    	    	valInt = ic->info.paramOp->info.variableNo;
    	    }
    	    else if (ic->info.paramOp->opType == OP_TEMP || ic->info.paramOp->vt == 1){
    	    	valStr[0] = 't';
    	    	valStr[1] = '\0';
    	    	valInt = ic->info.paramOp->info.tempNo;
    	    }
    	    fprintf(pFile, "PARAM %s%d\n", valStr, valInt);
    	    codeList = codeList->next;
 	    continue;
    	}
    	if (ic->icType == IC_READ){
    	    int valInt;
    	    if (ic->info.readOp->opType == OP_VARIABLE || ic->info.readOp->vt == 0){
    	    	valStr[0] = 'v';
    	    	valStr[1] = '\0';
    	    	valInt = ic->info.readOp->info.variableNo;
    	    }
    	    else if (ic->info.readOp->opType == OP_TEMP || ic->info.readOp->vt == 1){
    	    	valStr[0] = 't';
    	    	valStr[1] = '\0';
    	    	valInt = ic->info.readOp->info.tempNo;
    	    }
    	    fprintf(pFile, "READ %s%d\n", valStr, valInt);
    	    codeList = codeList->next;
 	    continue;
    	}
    	if (ic->icType == IC_WRITE){
    	    int valInt;
    	    if (ic->info.writeOp->opType == OP_VARIABLE || ic->info.writeOp->vt == 0){
    	    	valStr[0] = 'v';
    	    	valStr[1] = '\0';
    	    	valInt = ic->info.writeOp->info.variableNo;
    	    }
    	    else if (ic->info.writeOp->opType == OP_TEMP || ic->info.writeOp->vt == 1){
    	    	valStr[0] = 't';
    	    	valStr[1] = '\0';
    	    	valInt = ic->info.writeOp->info.tempNo;
    	    }
    	    fprintf(pFile, "WRITE %s%d\n", valStr, valInt);
    	    codeList = codeList->next;
 	    continue;
    	}
    }
}

struct CodeList* concat(struct CodeList* cl1, struct CodeList* cl2){
    struct CodeList* tmpCl = cl1;
    if (cl1 == NULL)
        return cl2;
    if (cl2 == NULL)
        return cl1;
    while (tmpCl->next != NULL){
        //printf("%d\n", tmpCl->next);
        //debugPrint("alive");
        tmpCl = tmpCl->next;
        //printf("%d\n", tmpCl->next);
    }
    tmpCl->next = cl2;
    cl2->last = tmpCl;
    //debugPrint("alive");
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

    struct CodeList* codeList1 = trans_FunDec(child->rightbrother);
    struct CodeList* codeList2 = trans_CompSt(child->rightbrother->rightbrother);
    //debugPrint("live2");
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
    struct Node* child = node->leftchild;
    if (child->rightbrother->rightbrother->rightbrother == NULL){//ID LP RP
        struct InterCode* interCode = makeIc(NULL, NULL, NULL, IC_FUNCTION);
        strcpy(interCode->info.funcName, child->strval);
        struct CodeList* codeList = makeCodeList(interCode);
        debugPrint("ret FunDec");
        return codeList;
    }
    debugPrint("funDec param");
    struct InterCode* interCode = makeIc(NULL, NULL, NULL, IC_FUNCTION);
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
            codeList = concat(codeList, tmpCl);
            fl = fl->next;
        }else{
            struct Operand* tmpOp = NULL;
            if (fl->type->type == STRUCTURE)
            	tmpOp = makeOperand(OP_STRUCT);
            else if (fl->type->type == ARRAY)
            	tmpOp = makeOperand(OP_ARRAY);
            tmpOp->type = fl->type;
            if (DEBUG_FLAG2){
                printf("funDec: %s %d\n", fl->name, tmpOp->type);
            }
            tmpOp->isParam = 1;
            strcpy(tmpOp->name, fl->name);
            insertOperandHashNode(fl->name, tmpOp);
            struct CodeList* tmpCl = makeParamCl(tmpOp);
            codeList = concat(codeList, tmpCl);
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
        debugPrint("live");
    }
    else if (strcmp(child->rightbrother->name, "StmtList") == 0){//LC StmtList RC
        stmtList = trans_StmtList(child->rightbrother);
    }
    debugPrint("live2");
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
    debugPrint("ret trans_DefList");
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
    struct TypeNode* typeNode = (struct TypeNode*)malloc(sizeof(struct TypeNode));
    typeNode->type = VARIABLE;
    op->type = typeNode;
    return op;
}

struct CodeList* trans_DecList(struct Node* node, struct Operand* operand){
    if (node == NULL)
        return NULL;
    struct CodeList* cl1 = trans_Dec(node->leftchild, operand);
    if (node->leftchild->rightbrother == NULL){
        debugPrint("ret trans_DecList");
    	return cl1;
    }

    struct Operand* newOp = makeOperand(OP_VARIABLE);
    newOp->type = operand->type;
    struct CodeList* cl2 = trans_DecList(node->leftchild->rightbrother->rightbrother, newOp);
    debugPrint("ret trans_DecList");
    return concat(cl1, cl2);
}

struct CodeList* trans_Dec(struct Node* node, struct Operand* operand){
    debugPrint("start trans_Dec");
    struct Node* child = node->leftchild;
    if (child->rightbrother == NULL){//VarDec
            struct CodeList* cl1 = trans_VarDec(child, operand);
            debugPrint("ret trans_Dec");
            return cl1;
    }
    else{//VarDec ASSIGNOP Exp
        trans_VarDec(child, operand);
        struct Operand* op1 = makeOperand(OP_TEMP);
        struct CodeList* cl1 = trans_Exp(child->rightbrother->rightbrother, op1);
        struct InterCode* ic1 = (struct InterCode*)malloc(sizeof(struct InterCode));
        ic1->icType = IC_ASSIGN;
        ic1->info.assign.leftOp = operand;
        ic1->info.assign.rightOp = op1;
        struct CodeList* cl2 = makeCodeList(ic1);
        return concat(cl1, cl2);
    }
}

struct CodeList* trans_VarDec(struct Node* node, struct Operand* operand){
    if(node == NULL)
        return NULL;
    struct Node* child = node->leftchild;

    if (child->rightbrother == NULL){// ID
        strcpy(operand->name, child->strval);

        insertOperandHashNode(child->strval, operand);
        debugPrint("ret VarDec");
        if (operand->opType == OP_ARRAY){
            struct InterCode* ic = makeIc(NULL, operand, NULL, IC_DEC);
            return makeCodeList(ic);
        }
        return NULL;
    }
    //VarDec LB INT RB
    struct Operand* op = (struct Operand*)malloc(sizeof(struct Operand));
    op->opType = OP_ARRAY;
    op->info.variableNo = operand->info.variableNo;
    struct TypeNode* typeArr = (struct TypeNode*)malloc(sizeof(struct TypeNode));
    typeArr->type = ARRAY;
    typeArr->info.array.size = child->rightbrother->rightbrother->intval;//
    typeArr->info.array.type = operand->type;
    op->type = typeArr;
    if (DEBUG_FLAG2){
        //printf("VarDec: type is int?%d\n", operand->type->type == VARIABLE);
    }
    return trans_VarDec(child, op);
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
            clStart = trans_Stmt(node->leftchild);
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
    debugPrint("ret StmtList");
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
    	printf("makeic: %d\n", ic->info);
    	ic->info.assign.rightOp = rightOperand;
    	if (DEBUG_FLAG2){
    	    printf("makeic: %d\n", leftOperand);
    	}
    	return ic;
    }
    if (icType ==  IC_ASSIGN_ADDR){
    	struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
    	ic->icType = icType;
    	ic->info.assignAddr.leftOp = leftOperand;
    	ic->info.assignAddr.rightOp = rightOperand;
    	return ic;
    }
    if (icType ==  IC_ASSIGN_ADDR_VAL){
    	struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
    	ic->icType = icType;
    	ic->info.assignAddr.leftOp = leftOperand;
    	ic->info.assignAddr.rightOp = rightOperand;
    	return ic;
    }
    if (icType ==  IC_ADDR_ASSIGN_VAL){
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
    	struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
    	ic->icType = icType;
    	ic->info.readOp = leftOperand;
    	return ic;
    }
    if (icType == IC_WRITE){
    	debugPrint("live");
    	struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
    	ic->icType = icType;
    	ic->info.writeOp = leftOperand;
    	return ic;
    }
    if (icType == IC_DEC){
        struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
    	ic->icType = icType;
    	ic->info.dec.operand = leftOperand;
        ic->info.dec.size = sizeOfArray(leftOperand->type);
    	return ic;
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
    	//struct Operand* operand = makeOperand(OP_TEMP);
        return trans_Exp(child, NULL);
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
    	//debugPrint("01");
        struct Operand* op1 = makeOperand(OP_LABEL);
        struct Operand* op2 = makeOperand(OP_LABEL);
        struct Operand* op3 = makeOperand(OP_LABEL);
        struct CodeList* cl1 = trans_Cond(child->rightbrother->rightbrother, op1, op2);
        //debugPrint("1");
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
    ic->icType = IC_RELOP_GOTO;
    debugPrint("ific ok0");
    strcpy(ic->info.relGoto.relOp, relOp);
    debugPrint("ific ok1");
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
        if (op1->opType == OP_ARRAY){
            struct Operand* tmpOp1 = makeOperand(OP_TEMP);
            struct InterCode* ic = makeIc(NULL, tmpOp1, op1, IC_ASSIGN_ADDR_VAL);
            cl1 = concat(cl1, makeCodeList(ic));
            op1 = tmpOp1;
        }
        if (op2->opType == OP_ARRAY){
            struct Operand* tmpOp2 = makeOperand(OP_TEMP);
            struct InterCode* ic = makeIc(NULL, tmpOp2, op2, IC_ASSIGN_ADDR_VAL);
            cl2 = concat(cl2, makeCodeList(ic));
            op2 = tmpOp2;
        }
        if (DEBUG_FLAG2){
            printf("cl2:%d\n", cl2->interCode->info);
        }
        debugPrint("live");
        struct CodeList* cl3 = makeCodeList(makeIfIc(child->rightbrother->strval, op1, op2, trueLabel));
        if (DEBUG_FLAG2){
            printf("relop: %s", child->rightbrother->strval);
        }
        debugPrint("live");
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
    struct CodeList* cl2 = makeCodeList(makeIfIc("!=", op1, constZero, trueLabel));
    struct CodeList* cl3 = makeCodeList(makeIc(NULL, falseLabel,  NULL, IC_GOTO));
    return concat(concat(cl1, cl2), cl3);
}

struct InterCode* makeCallIc(struct Operand* operand, char* name){
    struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
    ic->icType = IC_CALL;
    ic->info.funcCall.result = operand;
    strcpy(ic->info.funcCall.function, name);
    return ic;
}

struct InterCode* makeArgIc(struct Operand* arg){
    struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
    ic->icType = IC_ARG;
    ic->info.argOp = arg;
    return ic;
}

struct CodeList* trans_Exp(struct Node* node, struct Operand* operand){
    debugPrint("start of trans_Exp");
    struct Node* child = node->leftchild;
    if (strcmp(child->name, "ID") == 0 && child->rightbrother == NULL){//ID
        struct Operand* op = lookUpOperand(child->strval);
        operand->type = op->type;
        if (DEBUG_FLAG2){
            printf("\n\nExpID: %s 's type is %d\n", child->strval, operand->type);
            printf("***checkID***\n");
            if (operand->type->type == ARRAY){
                printf("%s 's contain is NULL ? %d\n", child->strval, operand->type->info.array.type == NULL);
                if (operand->type->info.array.type->type == ARRAY){
                    printf("double array\n");
                    printf("double %s 's contain is NULL ? %d\n", child->strval, operand->type->info.array.type->info.array.type == NULL);
                }
            }
        }
        if (op->opType == OP_ARRAY && op->isParam == 0){
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
        if (DEBUG_FLAG2){
            printf("ic:: %d\n", ic->info.assign.leftOp);
            printf("ic:: %d\n", ic->info.assign.rightOp);
        }
        return makeCodeList(ic);
    }
    if (strcmp(child->name, "Exp") == 0 && strcmp(child->rightbrother->rightbrother->name, "Exp") == 0 && child->rightbrother->rightbrother->rightbrother == NULL){//Exp op Exp
        
        if (strcmp(child->rightbrother->name, "ASSIGNOP") == 0){
            debugPrint("Exp = Exp");
            if (strcmp(child->leftchild->name, "ID") == 0){//ID ASSIGN Exp
            	struct Operand* tmpOp2 = makeOperand(OP_TEMP);
            	struct Operand* leftVari = lookUpOperand(child->leftchild->strval);
            	struct CodeList* cl1 = trans_Exp(child->rightbrother->rightbrother, tmpOp2);
            	struct CodeList* cl2 = makeCodeList(makeIc(NULL, leftVari, tmpOp2, IC_ASSIGN));
                if (DEBUG_FLAG2){
                    printf("assign::%d\n", operand == NULL);
                }
                if (operand != NULL){
            	    struct CodeList* cl3 = makeCodeList(makeIc(NULL, operand, leftVari, IC_ASSIGN));
            	    return  concat(cl1, concat(cl2, cl3));
                }
                return concat(cl1, cl2);
            }
            else{//Exp ASSIGN Exp
                debugPrint("");
                debugPrint("Exp assign");
            	struct Operand* tmpOp1 = makeOperand(OP_TEMP);
            	struct Operand* tmpOp2 = makeOperand(OP_TEMP);
            	struct CodeList* cl1 = trans_Exp(child, tmpOp1);
            	struct CodeList* cl2 = trans_Exp(child->rightbrother->rightbrother, tmpOp2);
                struct CodeList* cl3 = NULL;
                if (tmpOp1->opType == OP_ARRAY && tmpOp2->opType != OP_ARRAY){
                    debugPrint("111");
                    cl3 = makeCodeList(makeIc(NULL, tmpOp1, tmpOp2, IC_ADDR_ASSIGN_VAL));
                }
                else{
            	    cl3 = makeCodeList(makeIc(NULL, tmpOp1, tmpOp2, IC_ASSIGN));
                }
                debugPrint("Exp assign live1");
                if (operand != NULL){
            	    struct CodeList* cl4 = makeCodeList(makeIc(NULL, operand, tmpOp1, IC_ASSIGN));
            	    return concat(concat(cl1, cl2), concat(cl3, cl4));
                }
                return concat(concat(cl1, cl2), cl3);
            }
        }
        else if (strcmp(child->rightbrother->name, "AND") == 0){
            struct Operand* label1 = makeOperand(OP_LABEL);
            struct Operand* label2 = makeOperand(OP_LABEL);
            struct CodeList* cl1 = makeCodeList(makeIc(NULL, operand, constZero, IC_ASSIGN));
            struct CodeList* cl2 = trans_Cond(node, label1, label2);
            struct CodeList* cl3 = makeCodeList(makeIc(NULL, label1, NULL, IC_LABEL));
            struct CodeList* cl4 = makeCodeList(makeIc(NULL, operand, constOne, IC_ASSIGN));
            struct CodeList* cl5 = makeCodeList(makeIc(NULL, label2, NULL, IC_LABEL));
            return concat(concat(concat(concat(cl1, cl2), cl3), cl4), cl5);
        }
        else if (strcmp(child->rightbrother->name, "OR") == 0){
            struct Operand* label1 = makeOperand(OP_LABEL);
            struct Operand* label2 = makeOperand(OP_LABEL);
            struct CodeList* cl1 = makeCodeList(makeIc(NULL, operand, constZero, IC_ASSIGN));
            struct CodeList* cl2 = trans_Cond(node, label1, label2);
            struct CodeList* cl3 = makeCodeList(makeIc(NULL, label1, NULL, IC_LABEL));
            struct CodeList* cl4 = makeCodeList(makeIc(NULL, operand, constOne, IC_ASSIGN));
            struct CodeList* cl5 = makeCodeList(makeIc(NULL, label2, NULL, IC_LABEL));
            return concat(concat(concat(concat(cl1, cl2), cl3), cl4), cl5);
        }
        else if (strcmp(child->rightbrother->name, "RELOP") == 0){
            struct Operand* label1 = makeOperand(OP_LABEL);
            struct Operand* label2 = makeOperand(OP_LABEL);
            struct CodeList* cl1 = makeCodeList(makeIc(NULL, operand, constZero, IC_ASSIGN));
            struct CodeList* cl2 = trans_Cond(node, label1, label2);
            struct CodeList* cl3 = makeCodeList(makeIc(NULL, label1, NULL, IC_LABEL));
            struct CodeList* cl4 = makeCodeList(makeIc(NULL, operand, constOne, IC_ASSIGN));
            struct CodeList* cl5 = makeCodeList(makeIc(NULL, label2, NULL, IC_LABEL));
            return concat(concat(concat(concat(cl1, cl2), cl3), cl4), cl5);
        }
        else if (strcmp(child->rightbrother->name, "PLUS") == 0){
            debugPrint("plus alive");
            struct Operand* tmpOp1 = makeOperand(OP_TEMP);
            struct Operand* tmpOp2 = makeOperand(OP_TEMP);
            struct CodeList* cl1 = trans_Exp(child, tmpOp1);
            if (DEBUG_FLAG2){
                printf("plus: tmpOp1:%d\n", tmpOp1->type);
            }
            debugPrint("plus cl1");
            struct CodeList* cl2 = trans_Exp(child->rightbrother->rightbrother, tmpOp2);
            struct CodeList* cl3 = makeCodeList(makeIc(operand, tmpOp1, tmpOp2, IC_ADD));
            debugPrint("plus ret");
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
        struct CodeList* cl2 = trans_Cond(node, label1, label2);
        struct CodeList* cl3 = makeCodeList(makeIc(NULL, label1, NULL, IC_LABEL));
        struct CodeList* cl4 = makeCodeList(makeIc(NULL, operand, constOne, IC_ASSIGN));
        struct CodeList* cl5 = makeCodeList(makeIc(NULL, label2, NULL, IC_LABEL));
        return concat(concat(concat(concat(cl1, cl2), cl3), cl4), cl5);
    }
    if (strcmp(child->name, "ID") == 0 && strcmp(child->rightbrother->name, "LP") == 0 && strcmp(child->rightbrother->rightbrother->name, "RP") == 0){//ID LP RP
    	debugPrint("ID LP RP");
        struct HashNode* tmpHash = hashFind(child->strval);
        if (tmpHash == NULL)
            return NULL;
        struct Function* func = tmpHash->type->info.function;
        if (strcmp(func->name, "read") == 0){
            debugPrint("read");
            return makeCodeList(makeIc(NULL, operand, NULL, IC_READ));
        }
        
        return makeCodeList(makeCallIc(operand, func->name));
    }
    if (strcmp(child->name, "ID") == 0 && strcmp(child->rightbrother->name, "LP") == 0 && strcmp(child->rightbrother->rightbrother->name, "Args") == 0){//ID LP Args RP
        struct HashNode* tmpHash = hashFind(child->strval);
        if (tmpHash == NULL)
            return NULL;
        struct Function* func = tmpHash->type->info.function;
        struct ArgList* args = NULL;
        struct CodeList* cl1 = trans_Args(child->rightbrother->rightbrother, &args, func->param);
        struct CodeList* cl2 = NULL;
        if (strcmp(func->name, "write") == 0){
            return concat(cl1, makeCodeList(makeIc(NULL, args->args, NULL, IC_WRITE)));
            //return concat(concat(cl1, makeCodeList(makeIc(NULL, args->args, NULL, IC_WRITE))), makeCodeList(makeIc(NULL, operand, constZero, IC_ASSIGN)));
            
        }
        while (args != NULL){
            cl2 = concat(cl2, makeCodeList(makeArgIc(args->args)));
            args = args->next;
        }
        return concat(concat(cl1, cl2), makeCodeList(makeCallIc(operand, func->name)));
    }
    if (strcmp(child->name, "Exp") == 0 && strcmp(child->rightbrother->name, "DOT") == 0){//Exp DOT ID
        /*struct Operand* baseOp = makeOperand(OP_TEMP);
        baseOp->opType = OP_ADDRESS;
        struct CodeList* cl1 = trans_Exp(child, baseOp);
        struct Operand* finalAddr = makeOperand(OP_TEMP);
        struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct Intercode));
        ic->icType = IC_ADDRESS;
        ic->info.binOp.result = finalAddr;
        ic->info.binOp.op1 = baseOp;
        ic->info.binOp.op2 = sizeOfStruct(child->rightbrother->rightbrother->strval);
        struct CodeList* cl2 = makeCodeList(ic);
        struct InterCode* ic2 = (struct InterCode*)malloc(sizeof(struct Intercode));
        ic2->icType = IC_ASSIGN;
        ic2->info.assign.leftOp = operand;
        ic2->info.assign.rightOp = finalAddr;
        struct CodeList* cl3 = makeCodeList(ic2);
        return concat(concat(cl1, cl2), cl3);*/
    }
    if (strcmp(child->name, "Exp") == 0 && strcmp(child->rightbrother->name, "LB") == 0){//Exp LB Exp RB
        debugPrint("array start");
        operand->opType = OP_ARRAY;//
        struct Operand* baseAddr = makeOperand(OP_TEMP);
        baseAddr->opType = OP_ADDRESS;
        struct CodeList* cl1 = trans_Exp(child, baseAddr);
        debugPrint("array base");
        struct Operand* offset = makeOperand(OP_TEMP);
        struct Operand* finalAddr = makeOperand(OP_TEMP);
        finalAddr->opType = OP_ADDRESS;
        struct CodeList* cl2 = trans_Exp(child->rightbrother->rightbrother, offset);
        debugPrint("array cl2");
        struct InterCode* ic = (struct InterCode*)malloc(sizeof(struct InterCode));
        ic->icType = IC_MUL;
        ic->info.binOp.result = offset;
        ic->info.binOp.op1 = offset;
        struct Operand* sizeOp = makeOperand(OP_CONSTANT);
        debugPrint("enter sizeof Array");
        if (DEBUG_FLAG2){
            printf("arrType is NULL? %d\n", baseAddr->type == NULL);
        }
        sizeOp->info.val = sizeOfArray(baseAddr->type->info.array.type);
        debugPrint("array alive");
        ic->info.binOp.op2 = sizeOp;
        debugPrint("array cl3");
        struct CodeList* cl3 = makeCodeList(ic);
        //debugPrint("array alive");
        ic = (struct InterCode*)malloc(sizeof(struct InterCode));
        ic->icType = IC_ADD;
        if (DEBUG_FLAG2){
            printf("final:%d\n", finalAddr->info.val);
            printf("base:%d\n", baseAddr->info.val);
            printf("off:%d\n", offset->info.val);
        }
        ic->info.binOp.result = finalAddr;
        ic->info.binOp.op1 = baseAddr;
        ic->info.binOp.op2 = offset;
        struct CodeList* cl4 = makeCodeList(ic);
        ic = (struct InterCode*)malloc(sizeof(struct InterCode));
        //debugPrint("array alive");
        if (isOneArray(baseAddr->type) == 1){//operand = *arr[index]
            debugPrint("array : single arr");
            ic->icType = IC_ASSIGN;
            ic->info.assignAddrVal.leftOp = operand;
            ic->info.assignAddrVal.rightOp = finalAddr;
            struct CodeList* cl5 = makeCodeList(ic);

            return concat(concat(cl1, concat(cl2, cl3)), concat(cl4, cl5));
        }
        debugPrint("array alive");
        //operand = arr[index]
        operand->type = baseAddr->type->info.array.type;
        ic->icType = IC_ASSIGN;
        ic->info.assign.leftOp = operand;
        ic->info.assign.rightOp = finalAddr;
        struct CodeList* cl5 = makeCodeList(ic);
        return concat(concat(cl1, cl2), concat(cl3, concat(cl4, cl5)));
    }

}

int sizeOfArray(struct TypeNode* typeNode){
    debugPrint("sizeof array alive");
    if (typeNode == NULL){
        if (DEBUG_FLAG2){
            printf("sizeOfArray: typeNode is NULL\n");
        }
        return 0;
    }
    debugPrint("sizeof array alive");
    if (typeNode->type == VARIABLE || typeNode->type != ARRAY){
        return 4;
    }
    debugPrint("sizeof array alive");
    return (typeNode->info.array.size * sizeOfArray(typeNode->info.array.type));
}

int isOneArray(struct TypeNode* typeNode){
    debugPrint("start isOneArray");
    if (typeNode == NULL){
        return 0;
    }
    if (DEBUG_FLAG2){
        if (typeNode->type == ARRAY)
            printf("isArray\n");
        if (typeNode->info.array.type == NULL)
            printf("isArray type is NULL\n");
    }
    if (typeNode->type == ARRAY && (typeNode->info.array.type == NULL || typeNode->info.array.type->type != ARRAY)){
        return 1;
    }
    debugPrint("end isOneArray");
    return 0;
}

struct CodeList* trans_Args(struct Node* node, struct ArgList** args, struct FieldList* fieldList){
    struct Node* child = node->leftchild;
    if (strcmp(child->name, "Exp") == 0 && child->rightbrother == NULL){//Exp
        debugPrint("trans_args exp");
        struct Operand* op1 = makeOperand(OP_TEMP);
        op1->isParam = 1;
        if (fieldList != NULL && (fieldList->type->type == ARRAY || fieldList->type->type == STRUCTURE))
            op1->opType = OP_ADDRESS;
        struct CodeList* cl1 = trans_Exp(child, op1);
        if (DEBUG_FLAG2){
            printf("fieldlist is NULL? %d\n", fieldList == NULL);
            if (fieldList != NULL)
                printf("fieldList: %d\n", fieldList->type->type);
        }
        if (fieldList != NULL && fieldList->type->type == VARIABLE && op1->opType == OP_ARRAY){//
            struct Operand* op2 = makeOperand(OP_TEMP);
            struct InterCode* ic = makeIc(NULL, op2, op1, IC_ASSIGN_ADDR_VAL);
            struct CodeList* cl2 = makeCodeList(ic);
            struct ArgList* newArg = (struct ArgList*)malloc(sizeof(struct ArgList));
            newArg->args = op2;
            newArg->next = *args;
            *args = newArg;
            return concat(cl1, cl2);
        }
            
        struct ArgList* newArg = (struct ArgList*)malloc(sizeof(struct ArgList));
        newArg->args = op1;
        newArg->next = *args;
        *args = newArg;
        return cl1;
    }
    //Exp COMMA Args
    struct Operand* op1 = makeOperand(OP_TEMP);
    op1->isParam = 1;
    if (fieldList != NULL && (fieldList->type->type == ARRAY || fieldList->type->type == STRUCTURE))
            op1->opType = OP_ADDRESS;
    struct CodeList* cl1 = trans_Exp(child, op1);
    if (fieldList != NULL && fieldList->type->type == VARIABLE && op1->opType == OP_ARRAY){//
        struct Operand* op2 = makeOperand(OP_TEMP);
        struct InterCode* ic = makeIc(NULL, op2, op1, IC_ASSIGN_ADDR_VAL);
        struct CodeList* cl2 = makeCodeList(ic);
        struct ArgList* newArg = (struct ArgList*)malloc(sizeof(struct ArgList));
        newArg->args = op2;
        newArg->next = *args;
        *args = newArg;
        if (fieldList != NULL)
            fieldList = fieldList->next;
        struct CodeList* cl3 = trans_Args(child->rightbrother->rightbrother, &newArg, fieldList);
        return concat(cl1, concat(cl2, cl3));
    }
    struct ArgList* newArg = (struct ArgList*)malloc(sizeof(struct ArgList));
    newArg->args = op1;
    newArg->next = *args;
    *args = newArg;
    if (fieldList != NULL)
        fieldList = fieldList->next;
    struct CodeList* cl2 = trans_Args(child->rightbrother->rightbrother, &newArg, fieldList);
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
    for (struct OperandHashNode* tmpNode = operandTable[hashNum]; tmpNode != NULL; tmpNode = tmpNode->next){
        if (strcmp(tmpNode->nodeName, name) == 0){//find it
            if (DEBUG_FLAG2){
                printf("DEBUG: find operandHashNode named %s\n", name);
            }
            return tmpNode;
        }
    }
    if (DEBUG_FLAG2){
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
        if (DEBUG_FLAG2){
            printf("DEBUG: %s already exist, insert fail\n", name);
        }
        return 0;
    }
    int hashNum = hashNumOf(name);
    struct OperandHashNode* newNode = (struct OperandHashNode*)malloc(sizeof(struct OperandHashNode));
    strcpy(newNode->nodeName, name);
    newNode->operand = operand;
    newNode->next = NULL;
    struct OperandHashNode* tmpNode = operandTable[hashNum];
    if (tmpNode == NULL){
        operandTable[hashNum] = newNode;
        if (DEBUG_FLAG2){
            printf("DEBUG: successfully insert %s into %d\n", name, hashNum);
        }
        return 1;
    }
    else{
        while (tmpNode->next != NULL){
            tmpNode = tmpNode->next;
        }
        tmpNode->next = newNode;
        if (DEBUG_FLAG2){
            printf("DEBUG: successfully insert %s into %d\n", name, hashNum);
        }
        return 1;
    }
}

struct Operand* lookUpOperand(char* name){
    struct OperandHashNode* opHN = operandHashFind(name);
    if (opHN != NULL){
        return opHN->operand;
    }/*
    struct Operand* op = (struct Operand*)malloc(sizeof(struct Operand));
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
    return op;*/
    return NULL;
}

struct Operand* makeOperand(enum OpType opType){
    struct Operand* op = (struct Operand*)malloc(sizeof(struct Operand));
    op->opType = opType;
    op->vt = -1;
    op->type = NULL;
    op->isParam = 0;
    if (opType == OP_VARIABLE || opType == OP_ARRAY){
    	op->vt = 0;
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
    	op->vt = 1;
        op->info.tempNo = tempNum;
        tempNum += 1;
        return op;
    }
    return op;
}



