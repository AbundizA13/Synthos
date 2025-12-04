#include "term_parser.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    termino terms[5];   
    token tokens[20];
    int totalterms;
    char input[30];
    printf("Dame una expresión para ser reconocida: "); fgets(input, 30, stdin);
    totalterms = getExpression(input, terms, tokens);
    printf("Se obtuvieron %d terminos.\n",totalterms);
    for(int i=0;i<totalterms;i++){
        printf("\t--|Termino #%d|--\n   | Signo: %d\tCoeficiente: %d.\n   | Variable: %c\tGrado: %d.\n",i+1,terms[i].signo,terms[i].coeficiente,terms[i].variable,terms[i].grado);
    }
}