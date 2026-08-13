#ifndef SYNTHOS_NEXUS_H
#define SYNTHOS_NEXUS_H

//#include "commands.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <optional>
using namespace std;

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
    FUNC,
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
        void tokenizarAlfanumerico();
        void tokenizarNumero();
        void tokenizarVariable(string variable);
        void tokenizarOperador();
        void tokenizarParentesis();
        unordered_map<string, function<double(double)>> funciones;

    public:
        Lexer(const string& texto);
        vector<token> tokenizar();
        void avanzar();
        char carActual(); //Obtiene el carácter actual en base al índice
        bool indiceDentroRango();
        bool esOperador();
        bool esParentesis();
    };

struct Variable{ //Dentro de un mapa que ya contiene el string de la variable
    //string var;
    double valor;
    bool constante;
    Variable(double val, bool constante)
        : valor(val), constante(constante){}
};
/*
struct Nodo{
    Nodo* der;
    Nodo* izq;
    Nodo* padre;
    token token;

    Nodo(Token t, Nodo* a, Nodo* b)
        : token(t), izq(a), der(b), padre(nullptr){}
};
*/
struct ContextoEvaluator{
    unordered_map<string, Variable>& variables;        
    unordered_map<string, function<double(double)>> funciones;

    ContextoEvaluator(unordered_map<string, Variable>& variables, unordered_map<string, function<double(double)>> funciones)
        : variables(variables), funciones(funciones){}
};

class Nodo;


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
        void liberarAST(Nodo* nodo);
    public:
        Nodo* raiz;
        Parser(vector<token> tokens);
        ~Parser(); //DESTRUCTOR
        Nodo* parseExpression();
        void imprimirAST(Nodo* nodo);
        
};

struct Expresion{
    string original;
    Nodo* raiz;
    unordered_map<string, Variable> variables;
};

class Evaluator{
    private:
        size_t indice;
        vector<token> tokens;
        bool esOperador(token t);
        Nodo* raiz;
    public:
        Evaluator(vector<token> tokens);
        Evaluator(const Expresion& expresion);
        unordered_map<string, Variable> variables;
        unordered_map<string, function<double(double)>> funciones;
        void escanearVariables();
        void asignarValorVariables();
        optional<double> evaluarAST(Nodo* nodo, ContextoEvaluator& contexto);

};

class Session{ //Se encarga de almacenar varios AST, mapa de va
    private:
        void eliminar_AST(Nodo* nodo);
    public:
        unordered_map<string, Expresion> expresiones;
        void agregarExpr(const string& nombre, const Expresion& expresion);
        ~Session();
};


//FUNCIONES INDEPENDIENTES

/*OUTPUT*/
void imprimirLogo();
void esperarENTER();
int preguntarEvaluacion();



#endif