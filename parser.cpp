#include "neonexus.h"
#include <vector>
#include <iostream>

using namespace Color;

Parser::Parser(vector<token> tokens){
    this->tokens = tokens;
}


Nodo* Parser::parseExpression(){
    Nodo* a = parseTerm();
    if(a == nullptr) return nullptr;
    int vector_size = tokens.size();
    while(indice < vector_size){
        token op = tokens[indice];
        switch (op.tipo){
        case SUM:
        case RES:{
            avanzar();
            Nodo* b = parseTerm();
            if(b == nullptr) return nullptr;
            Nodo* c = trinodo(a,b,op);
            a = c;
            break;
        }
        default: 
            this->raiz = a;
            return a;
        }
    }
    this->raiz = a;
    return a;
}
Nodo* Parser::parseTerm(){
    Nodo* a = parsePower();
    if(a == nullptr) return nullptr;
    while(indice < tokens.size()){
        if(actualEsTokenPrimario() || tokens[indice].tipo == L_PAR){ //MULTIPLICACIÓN IMPLICITA enc.
            Nodo* b = parsePower(); //Consume PARENTESIS ENTERO o TOKEN PRIMARIO y los multiplica
            if(b == nullptr) return nullptr;
            a = trinodo(a,b,{MULT});
        }else{
            token op = tokens[indice];
            switch (op.tipo){
            case MULT:
            case DIV:{
                avanzar();
                Nodo* b = parsePower();
                if(b == nullptr) return nullptr;
                a = trinodo(a,b,op);
                break;
            }
            default: return a;
            }
        }
    }
    return a;
}
Nodo* Parser::parsePower(){
    Nodo* a = parseFactor();
    if(a == nullptr) return nullptr;
    if(indice >= tokens.size()) return a;
    token op = tokens[indice];
    if(op.tipo == EXP){
        avanzar();
        Nodo* b = parseFactor();
        if(b == nullptr) return nullptr;
        a = trinodo(a,b,op);
    }
    return a;
}
Nodo* Parser::parseFactor(){
    if(indice >= tokens.size()) return nullptr;
    token actual = tokens[indice];
    if(actualEsTokenPrimario()){ //Tokens primarios sin hijos.
        Nodo* nuevoNodo = new Nodo(actual,nullptr,nullptr);
        avanzar();
        return nuevoNodo;
    }else if(actual.tipo == RES){ //RESTA UNARIA
        avanzar();
        Nodo* primario = parseFactor();
        if(primario == nullptr) return nullptr;
        Nodo* negacion = new Nodo(actual,nullptr,primario);
        unirHijos(negacion);
        return negacion;
    }else if(actual.tipo == SUM){ //SUMA UNARIA ignorada.
        avanzar();
        return parseFactor();
    }else if(actual.tipo == L_PAR){
        avanzar();
        Nodo* a = parseExpression();
        if(a == nullptr) return nullptr;
        if(tokens[indice].tipo == R_PAR){
            avanzar();
            return a;
        }else{
            cout<<Color::hl_negativo1<<"Error de sintaxis, Se esperaba ')'.";
            return nullptr;
        }
    }else{
        cout<<Color::hl_negativo1<<"Token desconocido en función 'parseF();'";
        return nullptr;
    }
}
bool esTokenPrimario(token t){
    if(t.tipo == NUM || t.tipo == VAR){ return true;
    }else return false;
}

void Parser::imprimirAST(Nodo* nodo){
    if(nodo == nullptr){
        cout<<AST_par<<"("<<hl_negativo1<<"ERR"<<AST_par<<")";
        return;
    }
    if(esTokenPrimario(nodo->token)){
        cout<<AST_prim<<nodo->token.contenido;
        return;
    }
    if(nodo->izq == nullptr && nodo->der != nullptr){
        if(nodo->token.tipo == RES){
            cout<<AST_par<<"("<<AST_op<<"-";
            imprimirAST(nodo->der);
            cout<<AST_par<<")";
            return;
        }
    }
    //Si es operador, imprimirá (izq OP der).
    cout<<AST_par<<"(";
    imprimirAST(nodo->izq);
    switch(nodo->token.tipo){
        case SUM:
            cout<<AST_op<<" + ";
            break;
        case RES:
            cout<<AST_op<<" - ";
            break;
        case MULT:
            cout<<AST_op<<" * ";
            break;
        case DIV:
            cout<<AST_op<<" / ";
            break;
        case EXP:
            cout<<AST_op<<" ^ ";
            break;
        default:
            cout<<AST_op<<" ? ";
    }
    imprimirAST(nodo->der);
    cout<<AST_par<<")";
    return;
}

Nodo* Parser::trinodo(Nodo* a, Nodo* b, token op){
    /*Simplemente une los nodos a y b (operandos) 
        con el nodo operador y retorna el nuevo nodo 'a'*/
    Nodo* c = new Nodo(op, a, b);
    unirHijos(c);
    return c;
}

void Parser::unirHijos(Nodo* padre){
    if(padre->izq != nullptr){
        padre->izq->padre = padre;
    }
    if(padre->der != nullptr){
        padre->der->padre = padre;
    }
}

bool Parser::actualEsTokenPrimario(){
    if(indice >= tokens.size()) return false;
    token t = tokens[indice];
    if(t.tipo == NUM || t.tipo == VAR){ return true;
    }else return false;
}

bool Parser::actualEsTokenOperador(){
    token t = tokens[indice];
    if(t.tipo == SUM || t.tipo == RES || t.tipo == MULT || t.tipo == DIV || t.tipo == EXP){
        return true;
    }else return false;
}

void Parser::avanzar(){
    this->indice += 1;
}