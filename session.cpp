#include "neonexus.h"
#include "nodes.h"
#include "messages.h"
#include <iostream>

using namespace std;

Session::~Session() = default;

void Session::agregarExpr(const string& nombre, Expresion expresion){
    auto expr = make_unique<Expresion>(std::move(expresion));
    expresiones.emplace(nombre, std::move(expr));
    cout<<Mensaje::debug_sess_expr_agregada(expresion.original, nombre);
}

void Session::loopPrincipal(){
    
}