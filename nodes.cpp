#include "neonexus.h"
#include "messages.h"
#include "nodes.h"
#include <iostream>
#include <cmath>

using namespace std;

double Nodo_Numero::evaluar(ContextoEvaluator& contexto){
    return stod(token.contenido);
}

double Nodo_Variable::evaluar(ContextoEvaluator& contexto){
    string variable = token.contenido;
    auto& variables = contexto.variables;
    auto iterador = variables.find(variable);
    if(iterador != variables.end()){
        Variable var = iterador->second;
        return var.valor;
    }
    cout<<Mensaje::err_variable_no_en_mapa;
    return 0.0;
}

double Nodo_Funcion::evaluar(ContextoEvaluator& contexto){
    if(der == nullptr){
        cout<<Mensaje::err_funcion_sin_argumento;
        return 0.0;
    }
    double argumento = der->evaluar(contexto);
    auto funciones = contexto.funciones;
    return funciones[token.contenido](argumento);
}

double Nodo_Operador::evaluar(ContextoEvaluator& contexto){
    if(izq != nullptr) {
        valor_izquierdo = izq->evaluar(contexto);
    }
    if(der != nullptr) {
        valor_derecho = der->evaluar(contexto);
    }
    switch(token.tipo){
        case SUM:
            return valor_izquierdo+valor_derecho;
        case RES:
            return valor_izquierdo-valor_derecho;
        case MULT:
            return valor_izquierdo*valor_derecho;
        case DIV:
            return valor_izquierdo/valor_derecho;
        case EXP:
            return pow(valor_izquierdo,valor_derecho);
    }
    return 0.0;
}

double Nodo_Operador_Unario::evaluar(ContextoEvaluator& contexto){
    if(der != nullptr) valor = der->evaluar(contexto);
    return -valor;
}