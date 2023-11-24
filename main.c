#ifndef STDIO
#define STDIO
#include<stdio.h>
#endif
#ifndef SEMA
#define SEMA
#include "sema.h"
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
int main(int argc, char** argv){
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
            checkSema(Root);
	    struct CodeList* clHead = startInterCode(Root);
	    if (argv[2] == NULL){
	    	irFile = fopen("output", "w");
	    }
	    else{
	    	irFile = fopen(argv[2], "w");
	    }
	    writeIR(clHead, irFile);
	    fclose(irFile);
        }
        TearsDown(Root);
        return 0;
    }
}
