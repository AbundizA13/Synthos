#ifndef SYNTHOS_NEXUS_H
#define SYNTHOS_NEXUS_H

#include <string>
#include <vector>
#include <unordered_map>
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