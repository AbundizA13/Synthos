#ifndef SYNTHOS_NEXUS_H
#define SYNTHOS_NEXUS_H

typedef enum token_type{    
    TOK_EOF,   //Tipos de Token
    NUM, 
    VAR,
    EXP,
    SUM,
    RES,
    MULT,
    DIV,
    R_PAR,
    L_PAR,
    UNK
} token_type;
/*
typedef enum{
    mult
} node_type;
*/

typedef struct{         //Token
    token_type tipo;
    char* content;
    //char content[10];
} token;

typedef struct Token_Node{          //Nodos de Token
    struct Token_Node* right; //Nodo derecho.
    struct Token_Node* left; //Nodo izquierdo.
    struct Token_Node* father; //Nodo padre
    token token; //Token contenido
} Token_Node;
/*
typedef struct{         //Término
    char full_term[15]; //Termino completo escrito.
    int grado; //1, 2, 3...
    int coeficiente;
    int signo; //0 = (-) | 1 = (+).
    char variable; //x,y,z o 0 para T.E.
} termino;*/

    //FUNCIONES

int getExpressionTokens(char* p, token** tokens_temp); //Obtener Tokens a partir de un input de tipo string.
const char* getTokenType(token_type type); //Devuelve un string con la abreviatura del tipo de token introducido.
void freeTree(Token_Node* node);
int isPrimary(token token);
void nextToken(token **tokens);
void bindChildren(Token_Node* father);
Token_Node* parseF(token** tokens);
Token_Node* parseT(token** tokens);
Token_Node* parseE(token** tokens);
void printTree(Token_Node* node);
void freeTokens(token* tList, int total);
int reallocCharPtr(char** ptr, int len, int* cap, int totalTokens, token* tList);
token createOpToken(char operator);

#endif