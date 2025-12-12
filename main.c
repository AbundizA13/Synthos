#include "nexus.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    token tokens[20];
    int totaltokens;
    char input[30];
    printf("Dame una expresión para ser reconocida: "); fgets(input, 30, stdin);
    char *p = input;
    totaltokens = getExpressionTokens(input,tokens);
    printf("Se detectó %d token(s) en '",totaltokens);
    for(p;*p!='\0';p++){
        if(*p!='\n'){
            printf("%c",*p);
        }
    }
    printf("'.\n");
    token* pt = tokens;
    for(int i=0;i<totaltokens;i++){
        char* ptv = pt->content;
        printf("\tToken #%d:\nValor:'",i+1);
        for(ptv;*ptv!='\0';ptv++){
            printf("%c",*ptv);
        }
        printf("' | Tipo: %s \n",getTokenType(pt->tipo));
        pt++;
    }
    //Lista de Tokens hecha.
    printf("Generando árbol de tokens...\n");
    token* dblPtr = tokens;
    Token_Node* root = parseE(&dblPtr);
    if(root != NULL){
        printTree(root);
    }
    freeTree(root);
    printf("\n\tGracias por usar Synthos :p.");
    return 0;
    
}