#include "neonexus.h"
#include "messages.h"
#include <iostream>

using namespace std;

Session::~Session(){
    for(auto& expresion : expresiones){
        eliminar_AST(expresion.second.raiz);
    }
}

void Session::eliminar_AST(Nodo* nodo){
    if(nodo == nullptr){
        return;
    }
    eliminar_AST(nodo->izq);
    eliminar_AST(nodo->der);
    delete nodo;
}

void Session::agregarExpr(const Expresion& expresion){
    expresiones.emplace(expresion.original, expresion);
    cout<<Mensaje::debug_sess_expr_agregada;
}