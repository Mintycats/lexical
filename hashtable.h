#ifndef DEBUG_FLAG
#define DEBUG_FLAG 0
#endif

#ifndef HASH_NUM
#define HASH_NUM 1024
#endif

#ifndef NAME_LEN
#define NAME_LEN 32
#endif

//declare struct type
struct TypeNode;

struct FieldList{
    char name[NAME_LEN];
    struct TypeNode type;
    struct FieldList* next;
}

struct Structure{
    char name[NAME_LEN];
    struct FieldList domain;
};

struct Function{
    char name[NAME_LEN];
    int lineno;
    struct TypeNode type;
    struct FieldList param;
};

struct TypeNode{
    enum {
        VARIABLE,
        ARRAY,
        STRUCTURE,
        FUNCTION
    } type;
    union {
        int variable;// int1 float2
        struct {
            int size;
            struct TypeNode* type;
        } array;
        struct Structure structure;
        struct Function function;
    } info;
    enum {
        LEFT,
        RIGHT,
        BOTH
    } assignType;
};


struct HashNode{
    char nodeName[NAME_LEN];
    struct TypeNode type;
    struct HashNode* next;
};

//declare global
struct HashNode* hashTable[HASH_NUM];

//declare function
int hashNumOf(char*); //calculate Hashing num

struct HashNode* hashFind(char*);//find node in table

int checkExist(char*);//1 exist 0 not

int insertHashNode(char*,struct TypeNode); //create hashNode and insert it

//implement function
int hashNumOf(char* str){
    int len = strlen(str);
    int hashNum = 0;
    for (int i = 0; i < len; i++){// hashNum*33
        hashNum = (hashNum << 5) + hashNum + (int)str[i];
        hashNum = (hashNum & 0x7FFFFFFF) % HASH_NUM;
    }
    if (DEBUG_FLAG){
        printf("DEBUG: hashNum of %s is %d\n", str, hashNum);
    }
    return hashNum;
}

struct HashNode* hashFind(char* key){//return node by name or null if not find
    int hashNum = hashNumOf(key);
    for (struct HashNode* tmpNode = hashTable[hashNum]; tmpNode != NULL; tmpNode = tmpNode->next){
        if (strcmp(tmpNode->nodeName, key) == 0){//find it
            if (DEBUG_FLAG){
                printf("DEBUG: find hashNode named %s\n", key);
            }
            return tmpNode;
        }
    }
    if (DEBUG_FLAG){
        printf("DEBUG: not find hashNode named %s\n", key);
    }
    return NULL;
}

int checkExist(char* key){
    if (hashFind(key) == NULL){
        return 0;
    }
    return 1;
}

int insertHashNode(char* name,struct TypeNode type){
    if (checkExist(name) == 1){
        if (DEBUG_FLAG){
            printf("DEBUG: %s already exist, insert fail\n", name);
        }
        return 0;
    }
    hashNum = hashNumOf(name);
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    strcpy(newNode->nodeName, name);
    newNode->type = type;
    newNode->next = NULL;
    struct HashNode* tmpNode = hashTable[hashNum];
    if (tmpnode == NULL){
        hashTable[hashNum] = newNode;
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


