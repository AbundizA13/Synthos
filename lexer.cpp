#include <string>
#include <iostream>
#include <ctype.h>
#include "neonexus.H"

using namespace std;


Lexer::Lexer(string texto){
    this->expresion = texto;
    this->indice = 0;
};
void Lexer::avanzar(){indice++;};
char Lexer::carActual(){
    return expresion[indice];
}
bool Lexer::indiceDentroRango(){
    return indice < expresion.size();
}
void Lexer::tokenizarNumero(){
    string numero;
    while(indiceDentroRango() && isdigit(carActual())){
        numero += carActual();
        avanzar();
    }

    token t = {tipo_token::NUM, numero};
    this->tokens.push_back(t);
}
void Lexer::tokenizarVariable(){
    string variable;
    while(indiceDentroRango() && isalpha(carActual())){
        variable += carActual();
        avanzar();
    }

    token t = {tipo_token::VAR, variable};
    this->tokens.push_back(t);
}
bool Lexer::esOperador(){
    char actual = carActual();
    return actual == '+' || actual == '-' || actual == '*' || actual == '/';
}
void Lexer::tokenizarSuma(){
    string operador(1,carActual());

    token t = {tipo_token::SUM,operador};
    this->tokens.push_back(t);
    avanzar();
}
void Lexer::tokenizarResta(){
    string operador(1,carActual());

    token t = {tipo_token::RES,operador};
    this->tokens.push_back(t);
    avanzar();
}
void Lexer::tokenizarMult(){
    string operador(1,carActual());

    token t = {tipo_token::MULT,operador};
    this->tokens.push_back(t);
    avanzar();
}
void Lexer::tokenizarDiv(){
    string operador(1,carActual());
    
    token t = {tipo_token::DIV,operador};
    this->tokens.push_back(t);
    avanzar();
}
void Lexer::tokenizarOperador(){
    switch(carActual()){
        case '+':
            tokenizarSuma();
            break;
        case '-':
            tokenizarResta();
            break;
        case '*':
            tokenizarMult();
            break;
        case '/':
            tokenizarDiv();
            break;
    }
}
bool Lexer::esParentesis(){
    char actual = carActual();
    return actual == '(' || actual == ')';
}
void Lexer::tokenizarParentesis(){
    string parentesis(1,carActual());

    
    token t;
    t.contenido = parentesis;
    switch(carActual()){
        case '(':
            t.tipo = tipo_token::L_PAR;
            break;
        case ')':
            t.tipo = tipo_token::R_PAR;
            break;
    }
    this->tokens.push_back(t);
    avanzar();
}
vector<Token> Lexer::tokenizar(){
    while(indiceDentroRango()){
        char actual = carActual();

        if(isdigit(actual)){
            tokenizarNumero(); //cada método para tokenizar avanza consume y avanza indice
        }else if(isalpha(actual)){
            tokenizarVariable();
        }else if(isspace(actual)){
            avanzar();
        }else if(esOperador()){
            tokenizarOperador();
        }else if(esParentesis()){
            tokenizarParentesis();
        }else{
            cout<< Color::highlight_negativo<<"\n[ERROR] Se intentó tokenizar un carácter desconocido \""<<actual<<"\".\n";
            avanzar();
        }

    }
    return this->tokens;
};