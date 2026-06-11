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

    const string highlight_positivo = "\x1b[38;5;71m";
    const string highlight_negativo = "\x1b[38;5;174m";
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
} tipoTkn;

typedef struct token{
    tipoTkn tipo;
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
        void tokenizarParentesis();
    };

void esperarENTER();

#endif