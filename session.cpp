#include "neonexus.h"
#include "nodes.h"
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

void Session::agregarExpr(const string& nombre, const Expresion& expresion){
    expresiones.emplace(nombre, expresion);
    cout<<Mensaje::debug_sess_expr_agregada(expresion.original, nombre);
}