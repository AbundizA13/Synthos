#ifndef SYNTHOS_NEXUS_H
#define SYNTHOS_NEXUS_H

#include <string>
#include <vector>
using namespace std;

namespace Color{

    const string texto_base = "\x1b[39m";

    //MENSAJE PRINCIPAL DE REQUERIMIENTO DE INPUT
    const string input_principal = "\x1b[38;5;44m"; //[INPUT]
    const string input_secundario = "\x1b[38;5;222m"; //Descripción
    //IMPRESIÓN DE LOGO
    const string menu_marco = "\x1b[38;5;24m"; //Color de marco del logo
    const string menu_principal = "\x1b[38;5;222m"; //Color principal del logo
    const string menu_secundario = "\x1b[38;5;109m"; //Color secundario del logo
    //IMPRESIÓN DE MENSAJES
    const string hl_positivo1 = "\x1b[38;5;108m";
    const string hl_positivo2 = "\x1b[38;5;71m";
    const string hl_negativo1 = "\x1b[38;5;174m";
    const string AST_par = "\x1b[38;5;66m";
    const string AST_prim = "\x1b[38;5;159m";
    const string AST_op = "\x1b[38;5;35m";
}

typedef enum tipo_token{
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
} tipoToken;

typedef struct token{
    tipoToken tipo;
    string contenido;
} Token;

class Lexer{
    private:
        string expresion;
        size_t indice;
        vector<Token> tokens;

    public:
        Lexer(string texto);
        vector<token> tokenizar();
        void avanzar();
        char carActual(); //Obtiene el carácter actual en base al índice
        bool indiceDentroRango();
        bool esOperador();
        bool esParentesis();
        
        void tokenizarNumero();
        void tokenizarVariable();
        void tokenizarOperador();
            void tokenizarSuma();
            void tokenizarResta();
            void tokenizarMult();
            void tokenizarDiv();
            void tokenizarExp();
        void tokenizarParentesis();
    };

struct Nodo{
    Nodo* der;
    Nodo* izq;
    Nodo* padre;
    token token;

    Nodo(Token t, Nodo* a, Nodo* b)
        : token(t), izq(a), der(b), padre(nullptr){}
};

class Parser{
    private:
        vector<token> tokens;
        int indice;
        void avanzar();
        bool actualEsTokenPrimario();
        Nodo* parseTerm();
        Nodo* parsePower();
        Nodo* parseFactor();
        Nodo* trinodo(Nodo* a, Nodo* b, token op); //Parsea tres tokens en una estructura trinodo
        bool actualEsTokenOperador();
        void unirHijos(Nodo* padre);
    public:
        Nodo* raiz;
        Parser(vector<token> tokens);
        Nodo* parseExpression();
        void imprimirAST(Nodo* nodo);
        
};

void esperarENTER();

#endif