#ifndef STDIO
#define STDIO
#include<stdio.h>
#endif
#ifndef ASM
#define ASM
#include "asm.h"
#endif

//#define DEBUG_FLAG 1

extern int yyparse(void);
extern void yyrestart(FILE* input_file);
extern int hasError;
extern struct Node* Root;
extern struct Node* debugger;
extern struct Node* debugger2;
extern void PrintTree(struct Node* rootnode, int spaceNum);
extern void TearsDown(struct Node* rootnode);
extern int hasStruct;
int main(int argc, char** argv){
    FILE* asmFile = NULL;
    FILE* irFile = NULL;
    if (argc > 1){
	    FILE* sampleFile = fopen(argv[1], "r");
        if (!sampleFile){
            perror(argv[1]);
            return 1;
        }
        yyrestart(sampleFile);
        yyparse();
        if (!hasError){
            //printf("[main]:\n");
            //PrintTree(debugger, 0);
            //PrintTree(Root, 0);
            if (DEBUG_FLAG)
                printf("DEBUG: printtree done\n");
            if (hasStruct == 1){
                fprintf(stdout, "Cannot translate: Code contains variables or parameters of structure type.\n");
                return 0;
            }
            checkSema(Root);
	        struct CodeList* clHead = startInterCode(Root);
	        if (argv[2] == NULL){
	    	    asmFile = fopen("output.s", "w");
	        }
	        else{
	    	    asmFile = fopen(argv[2], "w");
	        }
            irFile = fopen("outIr.ir", "w");
            writeIR(clHead, irFile);
            fclose(irFile);
	        makeAsm(clHead, asmFile);
	        fclose(asmFile);
        }
        TearsDown(Root);
        return 0;
    }
}
