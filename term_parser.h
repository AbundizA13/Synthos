#ifndef term_parser
#define term_parser
#include <stdio.h>
#include <ctype.h>

typedef enum{
    COEF,
    VAR,
    EXP,
    SUM,
    RES
} term_type;

typedef struct{
    term_type tipo;
    char content[10];
}token;

typedef struct{     
    char full_term[15]; //Termino completo escrito.
    int grado; //1, 2, 3...
    int coeficiente;
    int signo; //0 = (-) | 1 = (+).
    char variable; //x,y,z o 0 para T.E.
}termino;

int getExpression(char expresion[30], termino* terms_temp, token* tokens_temp);

#endif