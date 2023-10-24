#include<stdio.h>
extern int yyparse(void);
extern void yyrestart(FILE* input_file);
extern int hasError;
extern struct Node* Root;
extern struct Node* debugger;
extern struct Node* debugger2;
extern void PrintTree(struct Node* rootnode, int spaceNum);
extern void TearsDown(struct Node* rootnode);
int main(int argc, char** argv){
    if (argc > 1){
	    FILE* f = fopen(argv[1], "r");
        if (!f){
            perror(argv[1]);
            return 1;
        }
        yyrestart(f);
        yyparse();
        if (!hasError){
            //printf("[main]:\n");
            //PrintTree(debugger, 0);
            //PrintTree(Root, 0);
            checkSema(Root);
        }
        TearsDown(Root);
        return 0;
    }
}
