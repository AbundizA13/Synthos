#include "neonexus.h"
#include "messages.h"
#include "nodes.h"
#include <iostream>
#include <cmath>

using namespace std;

double Nodo_Numero::evaluar(ContextoEvaluator& contexto){
    cout << "[DEBUG] Nodo_Numero: " << token.contenido << endl;
    return stod(token.contenido);
}

double Nodo_Variable::evaluar(ContextoEvaluator& contexto){
    cout << "[DEBUG] Nodo_Variable: " << token.contenido << endl;
    string variable = token.contenido;
    auto& variables = contexto.variables;
    auto iterador = variables.find(variable);
    if(iterador != variables.end()){
        Variable var = iterador->second;
        cout << "[DEBUG] Variable encontrada: " << variable << " = " << var.valor << endl;
        return var.valor;
    }
    cout<<Mensaje::err_variable_no_en_mapa;
    return 0.0;
}

double Nodo_Funcion::evaluar(ContextoEvaluator& contexto){
    cout << "[DEBUG] Nodo_Funcion: " << token.contenido << endl;
    if(der == nullptr){
        cout<<Mensaje::err_funcion_sin_argumento;
        return 0.0;
    }
    double argumento = der->evaluar(contexto);
    auto funciones = contexto.funciones;
    return funciones[token.contenido](argumento);
}

double Nodo_Operador::evaluar(ContextoEvaluator& contexto){
    cout << "[DEBUG] Nodo_Operador: " << token.contenido << " (tipo " << token.tipo << ")" << endl;
    if(izq != nullptr) {
        cout << "[DEBUG] Evaluando operador izquierdo..." << endl;
        valor_izquierdo = izq->evaluar(contexto);
    }
    if(der != nullptr) {
        cout << "[DEBUG] Evaluando operador derecho..." << endl;
        valor_derecho = der->evaluar(contexto);
    }
    cout << "[DEBUG] Valores: " << valor_izquierdo << " op " << valor_derecho << endl;
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
    cout << "[DEBUG] Operador desconocido!" << endl;
    return 0.0;
}

double Nodo_Operador_Unario::evaluar(ContextoEvaluator& contexto){
    cout << "[DEBUG] Nodo_Operador_Unario: " << token.contenido << endl;
    if(der != nullptr) {
        cout << "[DEBUG] Evaluando argumento unario..." << endl;
        valor = der->evaluar(contexto);
    }
    cout << "[DEBUG] Valor unario: -" << valor << endl;
    return -valor;
}