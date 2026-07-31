#include "neonexus.h"
#include "syncolors.h"
#include "messages.h"
#include <vector>
#include <iostream>

/*
-2^2
(-2)^2
-2*3
-2+3
--2
*/

using namespace Color;

Parser::Parser(vector<token> tokens){
    this->tokens = std::move(tokens);
    this->indice = 0;
    this->raiz = nullptr;
}

Parser::~Parser(){ //Destructor que libera el AST completo
    liberarAST(this->raiz);
    this->raiz = nullptr;
}

void Parser::liberarAST(Nodo* nodo){
    if(nodo == nullptr){
        return;
    }
    liberarAST(nodo->izq);
    liberarAST(nodo->der);
    delete nodo;
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
        if((actualEsTokenPrimario() || tokens[indice].tipo == FUNC) || tokens[indice].tipo == L_PAR){ //MULTIPLICACIÓN IMPLICITA enc.
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
        Nodo* primario = parsePower();
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
        if(indice < tokens.size() && tokens[indice].tipo == R_PAR){
            avanzar();
            return a;
        }else{
            cout<<Mensaje::err_parentesis_abierto;
            return nullptr;
        }
    }else if(actual.tipo == FUNC){
        //token función guardado en actual
        avanzar();
        if(tokens[indice].tipo != L_PAR){
            //AGREGAR MENSAJE DE ERROR.
            return nullptr;
        }
        avanzar(); //Parentesis consumido
        Nodo* argumento = parseExpression();
        if(tokens[indice].tipo != R_PAR){
            //AGREGAR MENSAJE DE ERROR.
            return nullptr;
        }
        avanzar();
        Nodo* funcion = new Nodo(actual,nullptr,argumento);
        return funcion;
    }else{
        cout<<Mensaje::err_token_desconocido_parser;
        return nullptr;
    }
}
bool esTokenPrimario(token t){
    if(t.tipo == NUM || t.tipo == VAR){ return true;
    }else return false;
}

void Parser::imprimirAST(Nodo* nodo){
    if(nodo == nullptr){
        cout<<AST_par<<"("<<Mensaje::impresion_token_desconocido<<AST_par<<")";
        return;
    }
    if(esTokenPrimario(nodo->token)){
        cout<<AST_prim<<nodo->token.contenido;
        return;
    }
    if(nodo->izq == nullptr && nodo->der != nullptr){
        token t = nodo->token;
        if(t.tipo == RES){
            cout<<AST_par<<"("<<AST_op<<"-";
            imprimirAST(nodo->der);
            cout<<AST_par<<")";
            return;
        }
        if(t.tipo == FUNC){
            cout<<AST_par<<"("<<AST_func<<t.contenido<<AST_par<<"(";
            imprimirAST(nodo->der);
            cout<<AST_par<<"))";
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
    if(indice >= tokens.size()) return false;
    token t = tokens[indice];
    if(t.tipo == SUM || t.tipo == RES || t.tipo == MULT || t.tipo == DIV || t.tipo == EXP){
        return true;
    }else return false;
}

void Parser::avanzar(){
    this->indice += 1;
}