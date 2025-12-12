#ifndef nexus
#define nexus

typedef enum token_type{    
    EOF,   //Tipos de Token
    NUM, 
    VAR,
    EXP,
    SUM,
    RES,
    MULT,
    DIV,
    R_PAR,
    L_PAR,
    DOT
} token_type;
/*
typedef enum{
    mult
} node_type;
*/

typedef struct{         //Token
    token_type tipo;
    char content[10];
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

int getExpressionTokens(char expresion[30], token* tokens_temp); //Obtener Tokens a partir de un input de tipo string.
const char* getTokenType(token_type type); //Devuelve un string con la abreviatura del tipo de token introducido.
void freeTree(Token_Node* node);
int isPrimary(token token);
void nextToken(token **tokens);
void bindChildren(Token_Node* father);
Token_Node* parseF(token** tokens);
Token_Node* parseT(token** tokens);
Token_Node* parseE(token** tokens);
void printTree(Token_Node* node);

#endif