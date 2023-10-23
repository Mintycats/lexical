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


