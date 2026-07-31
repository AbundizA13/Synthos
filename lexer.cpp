#include <string>
#include <iostream>
#include <ctype.h>
#include "neonexus.h"
#include "syncolors.h"
#include "messages.h"
#include "math_functions.h"

using namespace std;


Lexer::Lexer(const string& texto)
    : expresion(texto), indice(0), funciones(obtenerFuncionesMatematicas())
    {}

void Lexer::avanzar(){indice++;};
char Lexer::carActual(){
    if(!indiceDentroRango()) return '\0';
    return expresion[indice];
}
bool Lexer::indiceDentroRango(){
    return indice < expresion.size();
}
void Lexer::tokenizarNumero(){
    string numero;
    bool esDecimal = false;

    while(indiceDentroRango()){
        if(isdigit(carActual())){
            numero += carActual();
        }else if(carActual() == '.'){
            if(!(esDecimal)){ //No se ha detectado un punto en la constante
                numero += carActual();
                esDecimal = true;
            }else{ //La constante ya tenía un punto decimal procesado
                cout<<Mensaje::adv_decimal_duplicado;
            }
        }else{
            break;
        }
        avanzar();
    }

    token t = {tipo_token::NUM, numero};
    this->tokens.push_back(t);
}

void Lexer::tokenizarAlfanumerico(){
    string letras;
    while(indiceDentroRango() && isalpha(carActual())){
        letras += carActual();
        avanzar();
    }

    /*CAMBIAR VARIABLE O FUNC A IDENTIFICADOR Y DEJAR QUE EL PARSER AJUSTE*/
    if(funciones.find(letras) != funciones.end()){ //Es una función
        token t = {tipo_token::FUNC,letras};
        tokens.push_back(t);
    }else tokenizarVariable(letras);
}
void Lexer::tokenizarVariable(string variable){ //Separar en dos funciones
    token t = {tipo_token::VAR,variable};
    this->tokens.push_back(t);
}
bool Lexer::esOperador(){
    char actual = carActual();
    return actual == '+' || actual == '-' || actual == '*' || actual == '/' || actual == '^';
}
void Lexer::tokenizarOperador(){
    string operador(1,carActual());
    token t;
    switch(carActual()){
        case '+':
            t = {SUM,operador};
            break;
        case '-':
            t = {RES,operador};
            break;
        case '*':
            t = {MULT,operador};
            break;
        case '/':
            t = {DIV,operador};
            break;
        case '^':
            t = {EXP,operador};
    }
    tokens.push_back(t);
    avanzar();
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
            tokenizarAlfanumerico();
        }else if(isspace(actual)){
            avanzar();
        }else if(esOperador()){
            tokenizarOperador();
        }else if(esParentesis()){
            tokenizarParentesis();
        }else{
            cout<<Mensaje::err_token_desconocido(actual);
            avanzar();
        }
    }
    return this->tokens;
};