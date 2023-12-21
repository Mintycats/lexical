#include "sema.h"

int checkTypeNode(struct TypeNode* type1, struct TypeNode* type2){
    if (DEBUG_FLAG)
        printf("start check type\n");
    if (type1 == NULL && type2 == NULL){//null
        if (DEBUG_FLAG){
            printf("DEBUG: type1 == NULL and type2 == NULL\n");
        }
        return 1;
    }

    if (type1 == NULL || type2 == NULL){
        if (DEBUG_FLAG){
            printf("someone is NULL\n");
        }
        return 0;
    }

    if (DEBUG_FLAG){
        
    }
    
    if (type1->type == FUNCTION){
        if (DEBUG_FLAG)
            printf("in check: type1 is function\n");
        type1 = type1->info.function->type;
    }
    if (type2->type == FUNCTION){
        if (DEBUG_FLAG)
            printf("in check: type2 is function\n");
        type2 = type2->info.function->type;
    }

    if (type1->type != type2->type){
        if (DEBUG_FLAG){
            printf("DEBUG: type1 and type2 are different\n");
        }
        return 0;
    }
    if (type1->type == VARIABLE){//variable
        if (type1->info.variable == type2->info.variable){
            if (DEBUG_FLAG){
                printf("DEBUG: both type1 and type2 are variable %d\n", type1->info.variable);
            }
            return 1;
        }
        if (DEBUG_FLAG){
            printf("DEBUG: error type1 is variable but type2 is %d\n", type2->type);
        }
        return 0;
    }
    if (type1->type == ARRAY){//array
        return checkTypeNode(type1->info.array.type, type2->info.array.type);
    }
    if (type1->type == STRUCTURE){//structure
        return !strcmp(type1->info.structure->name, type2->info.structure->name);
    }
}

int checkParam(struct FieldList* fl1, struct FieldList* fl2){
    if (DEBUG_FLAG)
        printf("start checkParam\n");
    while (fl1 != NULL && fl2 != NULL){
        if (checkTypeNode(fl1->type, fl2->type) == 0){
            if (DEBUG_FLAG){
                printf("DEBUG: param type are diff\n");
            }
            return 0;
        }
        fl1 = fl1->next;
        fl2 = fl2->next;
    }
    if (fl1 == NULL && fl2 == NULL){//null
        if (DEBUG_FLAG){
            printf("DEBUG: two param are equal\n");
        }
        return 1;
    }
    if (DEBUG_FLAG){
        printf("DEBUG: num of param are diff\n");
    }
    return 0;
}

int checkMoreParam(struct FieldList* fl1, struct FieldList* fl2){
    if (DEBUG_FLAG)
        printf("start checkMoreParam\n");
    while (fl1 != NULL && fl2 != NULL){
        if (checkTypeNode(fl1->type, fl2->type) == 0 || strcmp(fl1->name, fl2->name) == 1){
            if (DEBUG_FLAG){
                printf("DEBUG: param type are diff\n");
            }
            return 0;
        }
        fl1 = fl1->next;
        fl2 = fl2->next;
    }
    if (fl1 == NULL && fl2 == NULL){//null
        if (DEBUG_FLAG){
            printf("DEBUG: two param are equal\n");
        }
        return 1;
    }
    if (DEBUG_FLAG){
        printf("DEBUG: num of param are diff\n");
    }
    return 0;
}

int checkSema(struct Node* node){
    if (DEBUG_FLAG)
        printf("DEBUG: sema start\n");

    initSema();

    ExtDefList(node->leftchild);
    
    finalCheckFunc();
}

void finalCheckFunc(){
    for (int i = 0; i < HASH_NUM; i++){
        struct HashNode* hashNode = funcTable[i];
        while (hashNode != NULL){
            semaError("18", hashNode->type->info.function->lineno, "Undefined function");
            hashNode = hashNode->next;
        }
    }
}

void initSema(){
    //init hashTable
    for (int i = 0; i < HASH_NUM; i++){
        hashTable[i] = NULL;
        funcTable[i] = NULL;
    }
    
    struct Function* fun = (struct Function*)malloc(sizeof(struct Function));
    strcpy(fun->name, "write");
    fun->type = NULL;
    fun->param = NULL;
    struct TypeNode* tp = (struct TypeNode*)malloc(sizeof(struct TypeNode));
    tp->type = VARIABLE;
    tp->info.variable = 1;
    
    struct FieldList* fl = (struct FieldList*)malloc(sizeof(struct FieldList));
    strcpy(fl->name, "asdfghjklzxcvbnm");
    fl->type = tp;
    fl->next = NULL;
    fun->param = fl;
    
    struct TypeNode* typeNode = (struct TypeNode*)malloc(sizeof(struct TypeNode));
    typeNode->type = FUNCTION;
    typeNode->info.function = fun;
    insertHashNode("write", typeNode);
    
    fun = (struct Function*)malloc(sizeof(struct Function));
    strcpy(fun->name, "read");
    fun->type = NULL;
    fun->param = NULL;
    typeNode = (struct TypeNode*)malloc(sizeof(struct TypeNode));
    typeNode->type = FUNCTION;
    typeNode->info.function = fun;
    insertHashNode("read", typeNode);
}

void ExtDefList(struct Node* node){
    if (DEBUG_FLAG)
        printf("DEBUG: ExtDefList start\n");
    if (node == NULL){
        if (DEBUG_FLAG){
            printf("DEBUG: NULL in ExtDefList\n");
        }
        return;
    }
    while (node != NULL){
        if (DEBUG_FLAG)
            printf("DEBUG: in while\n");
        ExtDef(node->leftchild);
        node = node->leftchild->rightbrother;
    }
}

void ExtDef(struct Node* node){
    if (DEBUG_FLAG)
        printf("DEBUG: enter ExtDef\n");

    if (node == NULL){
        if (DEBUG_FLAG){
            printf("DEBUG: NULL in ExtDef\n");
        }
        return ;
    }
    struct TypeNode* typeNode = Specifier(node->leftchild);
    if (DEBUG_FLAG)
        printf("Speci done\n");
    
    if (strcmp(node->leftchild->rightbrother->name, "ExtDecList") == 0){//Specifier ExtDecList SEMI
        ExtDecList(node->leftchild->rightbrother, typeNode);
        return;
    }
    if (strcmp(node->leftchild->rightbrother->name, "SEMI") == 0){//Specifier SEMI
        
    }
    if (strcmp(node->leftchild->rightbrother->name, "FunDec") == 0 && strcmp(node->leftchild->rightbrother->rightbrother->name, "CompSt") == 0){//Specifier FunDec CompSt
        if (DEBUG_FLAG){
            printf("DEBUG: FunDec CompSt\n");
            printf("tpNode.info.vari %d\n", typeNode->info.variable);
        }
        typeNode->assignType = RIGHT;
        struct Function* fun = FunDec(node->leftchild->rightbrother, typeNode, 0);
        if (fun == NULL){
            if (DEBUG_FLAG)
                printf("in ExtDef: fun is NULL\n");
            //CompSt(node->leftchild->rightbrother->rightbrother, typeNode);
            return;
        }
        struct HashNode* decFunc = funcFind(fun->name);
        if (decFunc != NULL){
            if (DEBUG_FLAG){
                printf("\n\n\nthis func declared before\n");
            }
            if (checkMoreParam(decFunc->type->info.function->param, fun->param) == 0){//param error
                semaError("19", decFunc->type->info.function->lineno, " Inconsistent declaration of function");
                //insert hashnode
                struct FieldList* tmpFl = fun->param;
                while (tmpFl != NULL){
                    if (insertHashNode(tmpFl->name, tmpFl->type) == 0){
                        semaError("3", fun->lineno, "Variable has been defined before");
                    }
                    tmpFl = tmpFl->next;
                }
            }
            else if (checkTypeNode(decFunc->type->info.function->type, fun->type) == 0){//ret type error
                semaError("19", decFunc->type->info.function->lineno, " Inconsistent declaration of function");
                //insert hashnode
                struct FieldList* tmpFl = fun->param;
                while (tmpFl != NULL){
                    if (insertHashNode(tmpFl->name, tmpFl->type) == 0){
                        semaError("3", fun->lineno, "Variable has been defined before");
                    }
                    tmpFl = tmpFl->next;
                }
            }
            else{//no error
                //insert hashnode
                struct FieldList* tmpFl = fun->param;
                while (tmpFl != NULL){
                    if (insertHashNode(tmpFl->name, tmpFl->type) == 0){
                        semaError("3", fun->lineno, "Variable has been defined before");
                    }
                    tmpFl = tmpFl->next;
                }
            }
        }
        else{//decFunc == NULL
            //insert hashnode
            struct FieldList* tmpFl = fun->param;
            while (tmpFl != NULL){
                if (insertHashNode(tmpFl->name, tmpFl->type) == 0){
                    semaError("3", fun->lineno, "Variable has been defined before");
                }
                tmpFl = tmpFl->next;
            }
        }


        struct TypeNode* funTypeNode = (struct TypeNode*)malloc(sizeof(struct TypeNode));
        funTypeNode->type = FUNCTION;
        funTypeNode->info.function = fun;
        insertHashNode(fun->name, funTypeNode);
        CompSt(node->leftchild->rightbrother->rightbrother, typeNode);
        removeFunc(fun->name);
        return;
    }
    if (strcmp(node->leftchild->rightbrother->name, "FunDec") == 0 && strcmp(node->leftchild->rightbrother->rightbrother->name, "SEMI") == 0){//Specifier FunDec SEMI
        typeNode->assignType = RIGHT;
        struct Function* fun = FunDec(node->leftchild->rightbrother, typeNode, 1);
        if (fun == NULL){
            if (DEBUG_FLAG)
                printf("in ExtDef: fun declare is null\n");
            return;
        }
        struct TypeNode* funTypeNode = (struct TypeNode*)malloc(sizeof(struct TypeNode));
        funTypeNode->type = FUNCTION;
        funTypeNode->info.function = fun;
        struct HashNode* frontFunc = hashFind(fun->name);
        if (frontFunc == NULL){
            insertFuncNode(fun->name, funTypeNode);
        }
        else{
            if (checkMoreParam(frontFunc->type->info.function->param, fun->param) == 0){//param error
                semaError("19", fun->lineno, " Inconsistent declaration of function");
            }
            else if (checkTypeNode(frontFunc->type->info.function->type, fun->type) == 0){//ret type error
                semaError("19", fun->lineno, " Inconsistent declaration of function");
            }
        }
        if (DEBUG_FLAG){
            printf("ExtDef: func declare done\n");
        }
        return;
    }
}

struct TypeNode* Specifier(struct Node* speci){
    if (DEBUG_FLAG)
        printf("DEBUG: enter Specifier\n");

    if (speci == NULL)
        return NULL;
    
    struct Node* child = speci->leftchild;

    if (DEBUG_FLAG){
        printf("childname %s\n", child->name);
        printf("strval %s\n", child->strval);
    }
    if (strcmp(child->name, "TYPE") == 0 && strcmp(child->strval, "int") == 0){
        if (DEBUG_FLAG)
            printf("DEBUG: Speci int\n");
        struct TypeNode* typeNode = (struct TypeNode*)malloc(sizeof(struct TypeNode));
        if (DEBUG_FLAG)
            printf("malloc done\n");
        typeNode->type = VARIABLE;
        typeNode->info.variable = 1;
        return typeNode;
    }
    if (strcmp(child->name, "TYPE") == 0 && strcmp(child->strval, "float") == 0){
        struct TypeNode* typeNode = (struct TypeNode*)malloc(sizeof(struct TypeNode));
        typeNode->type = VARIABLE;
        typeNode->info.variable = 2;
        return typeNode;
    }
    
    return StructSpecifier(child);
}

void CompSt(struct Node* node, struct TypeNode* typeNode){
    if (DEBUG_FLAG)
        printf("DEBUG: enter CompSt\n");

    if (node == NULL || typeNode == NULL){
        if (DEBUG_FLAG){
            printf("DEBUG: node or typeNode in CompSt is NULL\n");
        }
        return ;
    }

    struct Node* child1 = node->leftchild->rightbrother;
    struct Node* child2 = child1->rightbrother;
    
    if (strcmp(child1->name, "DefList") == 0){
        DefList(child1, 0);
        if (child2 != NULL && strcmp(child2->name, "StmtList") == 0){//StmtList
            StmtList(child2, typeNode);
        }
    }
    else if (strcmp(child1->name, "StmtList") == 0){
        StmtList(child1, typeNode);
    }
    else{// {}
        if (DEBUG_FLAG){
            printf("DEBUG: an empty block\n");
        }
    }
    if (DEBUG_FLAG)
        printf("CompSt done\n");
}

struct FieldList* VarList(struct Node* node){
   struct FieldList* fl = NULL;
   struct FieldList* tail = NULL;
   while (node != NULL){
       if (tail == NULL){
            fl = ParamDec(node->leftchild);
            tail = fl;
            while (tail->next != NULL)
                tail = tail->next;
            if (node->leftchild->rightbrother == NULL)
                node = NULL;
            else
                node = node->leftchild->rightbrother->rightbrother;
       }
       else{
            tail->next = ParamDec(node->leftchild);
            while (tail->next != NULL)
                tail = tail->next;
            if (node->leftchild->rightbrother == NULL)
                node = NULL;
            else
                node = node->leftchild->rightbrother->rightbrother;
       }
   }
   return fl;
}

struct FieldList* ParamDec(struct Node* node){
    struct Node* child = node->leftchild;
    struct TypeNode* typeNode = Specifier(child);
    if (typeNode->type == VARIABLE){
        return VarDec(child->rightbrother, typeNode, 2);
    }
    return VarDec(child->rightbrother, typeNode, 2);
}

void StmtList(struct Node* node, struct TypeNode* typeNode){
    if (node == NULL)
        return ;
    while (node != NULL){
        Stmt(node->leftchild, typeNode);
        node = node->leftchild->rightbrother;
    }
}

struct FieldList* DefList(struct Node* node, int isStruct){
    if (DEBUG_FLAG)
        printf("deflist start\n");

    if (node == NULL)
        return NULL;
    struct FieldList* fl = NULL;
    struct FieldList* tail = NULL;
    while (node != NULL){
        if (tail == NULL){
            fl = Def(node->leftchild, isStruct);
            tail = fl;
            while (tail->next != NULL)
                tail = tail->next;
            node = node->leftchild->rightbrother;
        }
        else{
            tail->next = Def(node->leftchild, isStruct);
            while (tail->next != NULL)
                tail = tail->next;
            node = node->leftchild->rightbrother;
        }
    }/*
    fl = Def(node->leftchild, isStruct);
    fl->next = DefList(node->leftchild->rightbrother, isStruct);*/
    if (DEBUG_FLAG)
        printf("DefList done\n");
    return fl;
}

struct FieldList* Def(struct Node* node, int isStruct){
    if (DEBUG_FLAG){
        printf("start Def\n");
        //printf("node %d\n", node);
    }
    struct Node* child = node->leftchild;
    struct TypeNode* typeNode = Specifier(child);
    if (DEBUG_FLAG)
        printf("in def: Def done\n");
    return DecList(child->rightbrother, typeNode, isStruct);
}


struct FieldList* DecList(struct Node* node, struct TypeNode* typeNode, int isStruct){
    if (DEBUG_FLAG)
        printf("\n\nDecList start\n");

    if (node == NULL)
        return NULL;
    struct FieldList* fl = NULL;
    struct FieldList* tailPointer = NULL;
    while (node != NULL){
        if (tailPointer == NULL){
            fl = Dec(node->leftchild, typeNode, isStruct);
            tailPointer = fl;
            if (DEBUG_FLAG)
                printf("\n\nname %s\n\n", fl->name);
            while (tailPointer->next != NULL)
                tailPointer = tailPointer->next;
            if (node->leftchild->rightbrother == NULL)
                node = NULL;
            else
                node = node->leftchild->rightbrother->rightbrother;
        }
        else{
            tailPointer->next = Dec(node->leftchild, typeNode, isStruct);
            while (tailPointer->next != NULL)
                tailPointer = tailPointer->next;
            if (node->leftchild->rightbrother == NULL)
                node = NULL;
            else
                node = node->leftchild->rightbrother->rightbrother;
        }
    }

    if (DEBUG_FLAG){
        struct FieldList* tmpfl = fl;
        while (tmpfl != NULL){
            printf("\n\ntmpfl: %s\n", tmpfl->name);
            tmpfl = tmpfl->next;
        }
        printf("end DecList\n");
    }
    return fl;
}

void Stmt(struct Node* node, struct TypeNode* typeNode){
    if (node == NULL){
        if (DEBUG_FLAG){
            printf("DEBUG: node or typeNode in Stmt is NULL\n");
        }
        return ;
    }
    
    struct Node* child = node->leftchild;

    if (DEBUG_FLAG)
        printf("Stmt child->%s\n", child->name);

    if (strcmp(child->name, "Exp") == 0){//Exp SEMI
        Exp(child);
    }
    if (strcmp(child->name, "CompSt") == 0){//CompSt
        CompSt(child, typeNode);
    }
    if (strcmp(child->name, "IF") == 0){//
        Exp(child->rightbrother->rightbrother);
        Stmt(child->rightbrother->rightbrother->rightbrother->rightbrother, typeNode);
        if (child->rightbrother->rightbrother->rightbrother->rightbrother->rightbrother != NULL){//ELSE Stmt
            Stmt(child->rightbrother->rightbrother->rightbrother->rightbrother->rightbrother->rightbrother, typeNode);
        }
    }
    if (strcmp(child->name, "WHILE") == 0){//WHILE LP Exp RP Stmt
        Exp(child->rightbrother->rightbrother);
        Stmt(child->rightbrother->rightbrother->rightbrother->rightbrother, typeNode);
    }
    if (strcmp(child->name, "RETURN") == 0){
        struct TypeNode* typeExp = Exp(child->rightbrother);
        if (DEBUG_FLAG){
            printf("exptype->%d\n", typeExp->type);
            printf("typeNode->%d\n", typeNode->type);
            printf("exptype.info->vari = %d\n", typeExp->info.variable);
            printf("typeNode.info->vari = %d\n", typeNode->info.variable);
        }
        if (checkTypeNode(typeNode, typeExp) == 0){
            semaError("8", child->lineno, "return error type");
        }
    }
}


void ExtDecList(struct Node* node, struct TypeNode* typeNode){
    if (node == NULL)
        return;
    while (node != NULL){
        VarDec(node->leftchild, typeNode, 0);
        if (node->leftchild->rightbrother == NULL)
            node = NULL;
        else
            node = node->leftchild->rightbrother->rightbrother;
        
    }
}

struct FieldList* VarDec(struct Node* node, struct TypeNode* typeNode, int isStruct){
    if (DEBUG_FLAG)
        printf("enter VarDec\n");

    if (node == NULL || typeNode == NULL)
        return NULL;

    struct Node* child = node->leftchild;

    if (DEBUG_FLAG)
        printf("child->%s\n", child->name);

    if (strcmp(child->name, "ID") == 0 && (checkExist(child->strval) == 0)){//ID is not exist
        struct FieldList* fl = (struct FieldList*)malloc(sizeof(struct FieldList));
        strcpy(fl->name, child->strval);
        fl->type = typeNode;
        fl->next = NULL;
        if (DEBUG_FLAG){
            //printf("vardec %d\n", typeNode);
        }
        if (isStruct != 2){
            insertHashNode(child->strval, typeNode);
        }
        return fl;
    }
    else if (strcmp(child->name, "VarDec") == 0 && (checkExist(child->strval) == 0)){
        struct TypeNode* typeArr = (struct TypeNode*)malloc(sizeof(struct TypeNode));
        typeArr->type = ARRAY;
        typeArr->info.array.size = child->rightbrother->rightbrother->intval;
        typeArr->info.array.type = typeNode;
        struct FieldList* fl = VarDec(child, typeArr, 0);
        return fl;
    }
    else if (strcmp(child->name, "ID") == 0 && (checkExist(child->strval) == 1) && (isStruct == 0 || isStruct == 2)){//ID is Existed
        if (isStruct != 2)
            semaError("3", child->lineno, "Variable has been defined before");
        struct FieldList* fl = (struct FieldList*)malloc(sizeof(struct FieldList));
        strcpy(fl->name, child->strval);
        fl->type = typeNode;
        fl->next = NULL;
        return fl;
    }
    else if (strcmp(child->name, "ID") == 0 && checkExist(child->strval) == 1 && isStruct == 1){
        semaError("15", child->lineno, "struct vari dup");
        struct FieldList* fl = (struct FieldList*)malloc(sizeof(struct FieldList));
        strcpy(fl->name, child->strval);
        fl->type = typeNode;
        fl->next = NULL;
        return fl;
    }
}



struct TypeNode* StructSpecifier(struct Node* node){
   struct Node* child = node->leftchild;
   if (strcmp(child->rightbrother->name, "OptTag") == 0 && child->rightbrother->leftchild != NULL && checkExist(child->rightbrother->leftchild->strval) == 1){
        semaError("16", child->lineno, "struct name is exist");
        return NULL;
   }
    

   if (strcmp(child->rightbrother->name, "OptTag") == 0){
       if (child->rightbrother->leftchild != NULL && checkExist(child->rightbrother->leftchild->strval) == 0){
           if (DEBUG_FLAG)
               printf("ready to insert struct\n");
            struct TypeNode* typeStru = (struct TypeNode*)malloc(sizeof(struct TypeNode));
            typeStru->type = STRUCTURE;
            struct Structure* st = (struct Structure*)malloc(sizeof(struct Structure));
            strcpy(st->name, child->rightbrother->leftchild->strval);
            typeStru->assignType = BOTH;
            st->domain = DefList(child->rightbrother->rightbrother->rightbrother, 1);
            if (DEBUG_FLAG){

            }
            typeStru->info.structure = st;
            insertHashNode(st->name, typeStru);
            return typeStru;
       }/*
       else if (child->rightbrother->leftchild == NULL){
            struct TypeNode* typeStru = (struct TypeNode*)malloc(sizeof(struct TypeNode));
            typeStru->type = STRUCTURE;
            struct Structure* st = (struct Structure*)malloc(sizeof(struct Structure));
            strcpy(st->name, "NULL");
            typeStru->assignType = BOTH;
            st->domain = DefList(child->rightbrother->rightbrother->rightbrother, 1);
            typeStru->info.structure = st;
            if (DEBUG_FLAG)
                printf("\n\n structspeci %d\n\n", typeStru);
            return typeStru;
       }*/
   }
   else if (strcmp(child->rightbrother->name, "LC") == 0){//STRUCT LC DefList RC
       if (DEBUG_FLAG){
            printf("\n\nno name struct\n\n");
       }
        struct TypeNode* typeStru = (struct TypeNode*)malloc(sizeof(struct TypeNode));
        typeStru->type = STRUCTURE;
        struct Structure* st = (struct Structure*)malloc(sizeof(struct Structure));
        strcpy(st->name, "NULL");
        typeStru->assignType = BOTH;
        st->domain = DefList(child->rightbrother->rightbrother, 1);
        typeStru->info.structure = st;/*
        if (DEBUG_FLAG)
            printf("\n\n structspeci %d\n\n", typeStru);*/
        return typeStru;
    }
   else if (strcmp(child->rightbrother->name, "Tag") == 0){
        struct HashNode* hashNode = hashFind(child->rightbrother->leftchild->strval);
        if (hashNode == NULL){
            semaError("17", child->lineno, "undefined struct");
            return NULL;
        }
        return hashNode->type;
   }
}

struct Function* FunDec(struct Node* node, struct TypeNode* typeNode, int isDeclare){
    if (DEBUG_FLAG)
        printf("DEBUG: enter FunDec\n");

    struct Node* child = node->leftchild;//ID

    if (DEBUG_FLAG)
        printf("fundec start\n");
    
          
        if (isDeclare == 0 && checkExist(child->strval) == 1){
            semaError("4", child->lineno, "Function has been defined before");
            return NULL;
        }
        struct Function* func = (struct Function*)malloc(sizeof(struct Function));
        strcpy(func->name, child->strval);
        func->lineno = child->lineno;
        func->type = typeNode;
        if (strcmp(child->rightbrother->rightbrother->name, "VarList") == 0){
            if (DEBUG_FLAG)
                printf("FunDec to VarList\n");
            struct FieldList* fl = VarList(child->rightbrother->rightbrother);
            func->param = fl;
        }
        else if (strcmp(child->rightbrother->rightbrother->name, "RP") == 0){
            func->param = NULL;
        }
        return func;
    
    
}

void semaError(char* type, int lineno, char* msg){
    return;
    if (isNewError(lineno))
        fprintf(stdout, "Error type %s at Line %d: %s\n", type, lineno, msg);
}

struct FieldList* Args(struct Node* node){
    struct FieldList* fl = NULL;
    struct FieldList* tail = NULL;
    struct TypeNode* typeNode = NULL;
    if (DEBUG_FLAG)
        printf("enter args\n");

    if (node == NULL)
        return NULL;

    while (node != NULL){
        if (tail == NULL){
            typeNode = Exp(node->leftchild);
            fl = (struct FieldList*)malloc(sizeof(struct FieldList));
            fl->type = typeNode;
            fl->next = NULL;
            tail = fl;
            if (node->leftchild->rightbrother == NULL)
                node = NULL;
            else
                node = node->leftchild->rightbrother->rightbrother;
        }
        else{
            typeNode = Exp(node->leftchild);
            tail->next = (struct FieldList*)malloc(sizeof(struct FieldList));
            tail->next->type = typeNode;
            tail->next->next = NULL;
            tail = tail->next;
            if (node->leftchild->rightbrother == NULL)
                node = NULL;
            else
                node = node->leftchild->rightbrother->rightbrother;
        }
    }

    if (DEBUG_FLAG)
        printf("end Args\n");
    return fl;
}

struct TypeNode* Exp(struct Node* node){
    if (DEBUG_FLAG)
        printf("enter exp\n");

    struct Node* child = node->leftchild;

    if (DEBUG_FLAG)
        printf("child->name %s\n", child->name);

    if (strcmp(child->name, "INT") == 0){
        if (DEBUG_FLAG)
            printf("int exp\n");
        struct TypeNode* typeNode = (struct TypeNode*)malloc(sizeof(struct TypeNode));
        typeNode->type = VARIABLE;
        typeNode->info.variable = 1;
        typeNode->assignType = RIGHT;
        return typeNode;
    }
    if (strcmp(child->name, "FLOAT") == 0){
        if (DEBUG_FLAG)
            printf("float exp\n");
        struct TypeNode* typeNode = (struct TypeNode*)malloc(sizeof(struct TypeNode));
        typeNode->type = VARIABLE;
        typeNode->info.variable = 2;
        typeNode->assignType = RIGHT;
        return typeNode;
    }

    if (strcmp(child->name, "LP") == 0){
        if (DEBUG_FLAG)
            printf("lp exp rp\n");
        return Exp(child->rightbrother);
    }

    if (strcmp(child->name, "ID") == 0){
        if (child->rightbrother == NULL){//IDtypeNode->info.function->type;

            if (checkExist(child->strval) == 0){
                semaError("1", child->lineno, "Undefine variable");
                return NULL;//
            }
            else{
                struct HashNode* hashNode = hashFind(child->strval);
                if (hashNode == NULL){
                    return NULL;
                }
                struct TypeNode* typeNode = hashNode->type;
                if (DEBUG_FLAG){
                    //printf("id %d\n", typeNode);
                }
                return typeNode;
            }
        }
        else if (strcmp(child->rightbrother->rightbrother->name, "Args") == 0){//ID LP Args RP
            if (DEBUG_FLAG)
                printf("ID LP Args RP\n");

            struct HashNode* hashNode = hashFind(child->strval);
            if (hashNode == NULL){
                semaError("2", child->lineno, "Undefine function");
                return NULL;
            }
            struct TypeNode* typeNode = hashNode->type;
            struct FieldList* fl = Args(child->rightbrother->rightbrother);
            if (DEBUG_FLAG){
                printf("Exp to checkParam\n");
                //printf("fl->%d\n", fl);
                //printf("typeNode->info.function %d\n", typeNode->info.function);
            }
            if (typeNode->type != FUNCTION){
                semaError("11", child->lineno, "id is not func");
                return NULL;
            }
            if (checkParam(fl, typeNode->info.function->param) == 0){
                semaError("9", child->lineno, "function param error");
                return NULL;
            }
            if (DEBUG_FLAG){
                printf("\n\nend ID LP RP\n");
            }
            return typeNode->info.function->type;
            
        }
        else if (strcmp(child->rightbrother->rightbrother->name, "RP") == 0){
            struct HashNode* hashNode = hashFind(child->strval);
            if (hashNode == NULL){
                semaError("2", child->lineno, "Undefine function");
                return NULL;
            }
            struct TypeNode* typeNode = hashNode->type;
            if (typeNode->info.function->param != NULL){
                semaError("9", child->lineno, "function param error");
                return NULL;
            }
            if (typeNode->type != FUNCTION){
                semaError("11", child->lineno, "id is not func");
                return NULL;
            }
            if (DEBUG_FLAG){
                printf("lp exp rp\n");
            }
            return typeNode->info.function->type;

        }
    }
    if (strcmp(child->name, "Exp") == 0 && (strcmp(child->rightbrother->name, "ASSIGNOP") == 0)){
        if (DEBUG_FLAG)
            printf("\n\nExp assign\n");

        struct TypeNode* leftType = Exp(child);
        struct TypeNode* rightType = Exp(child->rightbrother->rightbrother);

        if (leftType == NULL){
            if (DEBUG_FLAG)
                printf("exp assign right NULL\n");
            return NULL;
        }

        if (rightType == NULL){
            return leftType;
        }
        

        if (checkTypeNode(leftType, rightType) == 0){
            semaError("5", child->lineno, "invalid assignment");
            return NULL;
        }
        if (leftType->assignType == RIGHT){
            semaError("6", child->lineno, "right type in left");
            return NULL;
        }
        return leftType;//
    }
    if (strcmp(child->name, "MINUS") == 0){//MINUS Exp
        struct TypeNode* typeNode = Exp(child->rightbrother);
        if (typeNode->type != VARIABLE){
            semaError("7", child->lineno, "MINUS Exp error");
            return NULL;
        }
        return typeNode;
    }
    if (strcmp(child->name, "Exp") == 0 && (strcmp(child->rightbrother->name, "AND") == 0 || strcmp(child->rightbrother->name, "OR") == 0 || strcmp(child->rightbrother->name, "RELOP") == 0 || strcmp(child->rightbrother->name, "PLUS") == 0 || strcmp(child->rightbrother->name, "MINUS") == 0 || strcmp(child->rightbrother->name, "STAR") == 0 || strcmp(child->rightbrother->name, "DIV") == 0)){
        if (DEBUG_FLAG)
            printf("exp op exp\n");

        struct TypeNode* leftType = Exp(child);
        struct TypeNode* rightType = Exp(child->rightbrother->rightbrother);
        if (leftType == NULL || rightType == NULL){
            if (DEBUG_FLAG)
                printf("L or R NULL\n");
            return NULL;
        }

        if (checkTypeNode(leftType, rightType) == 0){
            semaError("7", child->lineno, "tuple error");
            return NULL;
        }
        return leftType;
    }
    if (strcmp(child->rightbrother->name, "LB") == 0){
        if (DEBUG_FLAG){
            printf("LB RB\n");
        }
        struct TypeNode* typeArr = Exp(child);
        struct TypeNode* typeIndex = Exp(child->rightbrother->rightbrother);
        if (DEBUG_FLAG){
            //printf("is NULL %d\n", typeArr->info.array.type);
            printf("end LB RB\n");
            //printf("index %d\n", typeIndex);
        }
        if (typeArr->type != ARRAY){
            semaError("10", child->lineno, "array error");
            return NULL;
        }
        if (typeIndex->type != VARIABLE || typeIndex->info.variable != 1){
            semaError("12", child->lineno, "index must be int");
            return NULL;
        }
        if (DEBUG_FLAG){
            printf("end \n");
        }
        return typeArr->info.array.type;
    }
    if (strcmp(child->name, "Exp") == 0 && strcmp(child->rightbrother->name, "DOT") == 0){
        if (DEBUG_FLAG){
            printf("dot exp\n");
        }

        struct TypeNode* leftType = Exp(child);
        if (DEBUG_FLAG){
            printf("dot left done\n");
            if (leftType == NULL){
                printf("dot left NULL\n");
            }
            //printf("left type %d\n", leftType);
        }
        if (leftType == NULL){
            return NULL;
        }

        if (leftType->type != STRUCTURE){
            semaError("13", child->lineno, "dot error");
            return NULL;
        }
        if (DEBUG_FLAG){
            printf("\ndot alive\n");
            printf("right name %s\n", child->rightbrother->rightbrother->strval);
        }

        struct TypeNode* typeRight = findFieldList(leftType->info.structure->domain, child->rightbrother->rightbrother->strval);
        if (typeRight == NULL){
            semaError("14", child->lineno, "domain doesn't exist");
            return NULL;
        }
        return typeRight;
    }
}

struct TypeNode* findFieldList(struct FieldList* fl, char* name){
    if (DEBUG_FLAG){
        printf("enter findfieldlist\n");
    }
    if (fl == NULL){
        if (DEBUG_FLAG)
            printf("fl is NULL\n");
        return NULL;
    }
    while (fl != NULL){
        if (DEBUG_FLAG){
            printf("\nalive\n");
            printf("%s----%s\n", fl->name, name);
        }
        if (strcmp(fl->name, name) == 0){
            return fl->type;
        }
        fl = fl->next;
    }


    return NULL;
}

struct FieldList* Dec(struct Node* node, struct TypeNode* typeNode, int isStruct){
    if (DEBUG_FLAG)
        printf("start Dec\n");
    struct Node* child = node->leftchild;
    if (isStruct == 1 && child->rightbrother != NULL){
        semaError("15", child->lineno, "variable in struct can not be assigned");
        return VarDec(child, typeNode, isStruct);
    }
    if (DEBUG_FLAG)
        printf("child-> %s\n", child->name);

    if (child->rightbrother == NULL){//VarDec
        if (DEBUG_FLAG)
            printf("in dec to VarDec\n");
        return VarDec(child, typeNode, isStruct);
    }
    else{//VarDec ASSIGNOP Exp
        struct TypeNode* typeExp = Exp(child->rightbrother->rightbrother);
        if (typeExp == NULL)
            return VarDec(child, typeNode, isStruct);
        if (checkTypeNode(typeNode, typeExp) == 0){
            semaError("5", child->lineno, "invalid assignment");
            return NULL;
        }
        return VarDec(child, typeNode, isStruct);
    }
}
