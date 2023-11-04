#ifndef HASING
#define HASING
#include "hashtable.h"
#endif

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

int insertHashNode(char* name,struct TypeNode* type){
    if (checkExist(name) == 1){
        if (DEBUG_FLAG){
            printf("DEBUG: %s already exist, insert fail\n", name);
        }
        return 0;
    }
    int hashNum = hashNumOf(name);
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    strcpy(newNode->nodeName, name);
    newNode->type = type;
    newNode->next = NULL;
    struct HashNode* tmpNode = hashTable[hashNum];
    if (tmpNode == NULL){
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

int insertFuncNode(char* name, struct TypeNode* type){
    if (checkFuncExist(name) == 1){
        if (DEBUG_FLAG){
            printf("DEBUG: %s already exist, insert fail\n", name);
        }
        return 0;
    }
    int hashNum = hashNumOf(name);
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    strcpy(newNode->nodeName, name);
    newNode->type = type;
    newNode->next = NULL;
    struct HashNode* tmpNode = funcTable[hashNum];
    if (tmpNode == NULL){
        funcTable[hashNum] = newNode;
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

int checkFuncExist(char* key){
    if (funcFind(key) == NULL){
        return 0;
    }
    return 1;
}

struct HashNode* funcFind(char* key){//return func by name or null if not find
    int hashNum = hashNumOf(key);
    for (struct HashNode* tmpNode = funcTable[hashNum]; tmpNode != NULL; tmpNode = tmpNode->next){
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

void removeFunc(char* key){
    int hashNum = hashNumOf(key);
    struct HashNode* fatherNode = NULL;
    if (funcTable[hashNum] == NULL)
        return;
    if (strcmp(funcTable[hashNum]->nodeName, key) == 0){
        funcTable[hashNum] = NULL;
    }
    else
        fatherNode = funcTable[hashNum];
    for (struct HashNode* tmpNode = funcTable[hashNum]; tmpNode != NULL; tmpNode = tmpNode->next){
        if (strcmp(tmpNode->nodeName, key) == 0){//find it
            fatherNode->next = tmpNode->next;
            return;
        }
        fatherNode = tmpNode;
    }
}
