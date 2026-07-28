#ifndef SYNTHOS_NEXUS_H
#define SYNTHOS_NEXUS_H

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#define R Color::texto_base
#define M Color::menu_marco
#define P Color::menu_principal
#define S Color::menu_secundario

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
    const string hl_positivo0 = "\x1b[38;5;65m";
    const string hl_positivo1 = "\x1b[38;5;108m";
    const string hl_positivo2 = "\x1b[38;5;71m";
    const string hl_negativo1 = "\x1b[38;5;174m";
    const string AST_par = "\x1b[38;5;96m";
    const string AST_prim = "\x1b[38;5;139m";
    const string AST_op = "\x1b[38;5;182m";
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
        Lexer(const string& texto);
        vector<token> tokenizar();
        void avanzar();
        char carActual(); //Obtiene el carácter actual en base al índice
        bool indiceDentroRango();
        bool esOperador();
        bool esParentesis();
        
        void tokenizarNumero();
        void tokenizarVariable();
        void tokenizarOperador();
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
        bool actualEsTokenOperador();
        Nodo* parseTerm();
        Nodo* parsePower();
        Nodo* parseFactor();
        Nodo* trinodo(Nodo* a, Nodo* b, token op); //Parsea tres tokens en una estructura trinodo
        void unirHijos(Nodo* padre);
    public:
        Nodo* raiz;
        Parser(vector<token> tokens);
        Nodo* parseExpression();
        void imprimirAST(Nodo* nodo);
        
};

struct Variable{ //Dentro de un mapa que ya contiene el string de la variable
    //string var;
    double valor;
    bool constante;
    Variable(double val, bool constante)
        : valor(val), constante(constante){}
};

class Evaluator{
    private:
        size_t indice;
        vector<token> tokens;
        bool esOperador(token t);
    public:
        Evaluator(vector<token> tokens);
        unordered_map<string, Variable> variables;
        void escanearVariables();
        void asignarValorVariables(unordered_map<string,Variable>& variables);
        double evaluarAST(Nodo* raiz, unordered_map<string,Variable>& variables);

};

//FUNCIONES INDEPENDIENTES

/*OUTPUT*/
void imprimirLogo();
void esperarENTER();
int preguntarEvaluacion();


#endif