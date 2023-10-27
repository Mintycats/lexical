int checkTypeNode(struct TypeNode* type1, struct TypeNode* type2){
    if (type1 == NULL && type2 == NULL){//null
        if (DEBUG_FLAG){
            printf("DEBUG: type1 == NULL and type2 == NULL\n");
        }
        return 1;
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
        return !strcmp(type1->info.structure.name, type2->info.structure.name);
    }
}

int checkParam(struct FieldList* fl1, struct FieldList* fl2){
    while (fl1 != NULL && fl2 != NULL){
        if (checkType(&fl1.type, &fl2.type)){
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

int checkFunc(struct Function* func){
    
}

int checkSema(struct Node* node){
    initSema();

    ExtDefList(Root->leftchild);

}

void initSema(){
    //init hashTable
    for (int i = 0; i < HASH_NUM; i++){
        hashTable[i] = NULL;
    }

}

void ExtDefList(struct Node* node){
    if (node == NULL){
        if (DEBUG_FLAG){
            printf("DEBUG: NULL in ExtDefList\n");
        }
        return ;
    }
    ExtDef(node->leftchild);
    ExtDefList(node->leftchild->rightbrother);
}

void ExtDef(struct Node* node){
    if (node == NULL){
        if (DEBUG_FLAG){
            printf("DEBUG: NULL in ExtDef\n");
        }
        return ;
    }
    int specType = getSpecifier(node->leftchild);
    
    if (strcmp(node->leftchild->rightbrother->name, "ExtDecList") == 0){//Specifier ExtDecList SEMI
        ExtDecList(node->leftchild->rightbrother, specType);
    }
    if (strcmp(node->leftchild->rightbrother->name, "SEMI") == 0){//Specifier SEMI
        Specifier(node->leftchild, specType);
    }
    if (strcmp(node->leftchild->rightbrother->name, "FunDec") == 0){//Specifier FunDec CompSt
       FunDec(node->leftchild->rightbrother);
       Compst(node->leftchild->rightbrother->rightbrother, );
    }
}

int getSpecifier(struct Node* speci){
    if (speci == NULL)
        return 0;

    if (strcmp(speci->leftchild->name, "StructSpecifier") == 0){
        if (DEBUG_FLAG){
            printf("type of specifier is struct\n");
        }
        return 3;//struct
    }

    switch (speci->leftchild->strval){
        case "INT":
            if (DEBUG_FLAG){
                printf("type of specifier is int\n");
            }
            return 1;//int
        case "FLOAT":
            if (DEBUG_FLAG){
                printf("type of specifier is float\n");
            }
            return 2;//float
        default:
            if (DEBUG_FLAG){
                printf("DEBUG: Unknown Specifier\n");
            }
    };
    return 0;
}

void FunDec(struct Node* node){
    
}

void CompSt(struct Node* node, struct TypeNode* typeNode){
    if (node == NULL || typeNode == NULL){
        if (DEBUG_FLAG){
            printf("DEBUG: node or typeNode in CompSt is NULL\n");
        }
        return ;
    }

    struct Node* child1 = node->leftchild->rightbrother;
    struct Node* child2 = child1->rightbrother;
    
    if (strcmp(child1->name, "DefList") == 0){
        DefList();
        if (child2 != NULL && strcmp(child2->name, "StmtList") == 0){//StmtList
            StmtList();
        }
    }
    else if (strcmp(child1->name, "StmtList") == 0){
        StmtList();
    }
    else{// {}
        if (DEBUG_FLAG){
            printf("DEBUG: an empty block\n");
        }
    }
}

void Stmt(struct Node* node, struct TypeNode* typeNode){
    if (node == NULL || typeNode == NULL){
        if (DEBUG_FLAG){
            printf("DEBUG: node or typeNode in Stmt is NULL\n");
        }
        return ;
    }

    
}
