#include "neonexus.h"
#include <vector>

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
        default: return a;
        }
    }
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
}
Nodo* Parser::parsePower(){

}
Nodo* Parser::parseFactor(){

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