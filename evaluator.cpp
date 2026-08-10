#include "neonexus.h"
#include "syncolors.h"
#include "messages.h"
#include "math_functions.h"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>

using namespace Color;
using namespace std;

/*AGREGAR REFERENCIAS A VARIABLES EN VEZ DE COPIAS*/

Evaluator::Evaluator(vector<token> tokens):
    tokens(std::move(tokens)), indice(0), funciones(obtenerFuncionesMatematicas())
    {}
    //this->tokens = tokens;
    //this->indice = 0;
    

unordered_map<string, Variable> Evaluator::escanearVariables(){
    if(tokens.empty()){cout<<Mensaje::error_tokensNulos; return;}

    unordered_map<string, Variable> variables;
    while(indice < tokens.size()){
        const token& actual = tokens[indice];
        if(actual.tipo == VAR){
            string variable = actual.contenido;
            variables.emplace(variable, Variable(0.0, true)); //Agrega variable solo si no existe ya
        }
        indice++;
    }
    return variables;
}

void Evaluator::asignarValorVariables(unordered_map<string,Variable>& variables){
    if(variables.empty()){
        return;
    }
    for(auto& var : variables){ //Ciclo que recorre cada elemento del mapa
        const string& nombre = var.first;
        Variable& contenido = var.second;
        double valor;
        string entrada;
        while(1){
            cout<<Mensaje::pedir_valor_variable(nombre);
            getline(cin,entrada);
            try{
                size_t posConversion = 0; //Posición en la que acabó la conversión
                valor = stod(entrada, &posConversion);

                if(posConversion != entrada.length()){
                    cout<<Mensaje::adv_ignorando_caracteres;
                }
            }catch(const invalid_argument& e){
                cout<<Mensaje::err_valor_invalido;
                continue;
            }catch(const out_of_range& e){
                cout<<Mensaje::err_valor_muyAlto;
                continue;
            }
            break;
        }

        contenido.valor = valor;
    }
}

double Evaluator::evaluarAST(Nodo* nodo,unordered_map<string,Variable>& variables){
    if(nodo == nullptr){
        cout<<Mensaje::err_nodo_inexistente;
        return 0.0;
    }
    token t = nodo->token;
    if(t.tipo == NUM){
        return stod(t.contenido);
    }

    if(t.tipo == VAR){
        string variable = t.contenido;

        auto iterador = variables.find(variable);
        if(iterador != variables.end()){ //Se encontró la variable
                Variable var = iterador->second;
                return var.valor;
        }
        cout<<Mensaje::err_variable_no_en_mapa;
        return 0.0;
    }

    if(t.tipo == FUNC){
        if(nodo->der == nullptr){
            //AGREGAR MENSAJE DE ERROR.
            return 0.0;
        }
        double argumento = evaluarAST(nodo->der,variables);
        return funciones[t.contenido](argumento);
    }

    if(esOperador(t)){
        double izquierdo = 0.0, derecho = 0.0;
        if(nodo->izq != nullptr) izquierdo = evaluarAST(nodo->izq, variables);
        if(nodo->der != nullptr) derecho = evaluarAST(nodo->der, variables);
        switch(t.tipo){
            case SUM: 
                cout<<"("<<izquierdo<<" + "<<derecho<<")";
                return izquierdo+derecho;
            case RES:
                if(nodo->izq == nullptr){
                    cout<<"(-"<<derecho<<")";
                    return -derecho;
                }
                cout<<"("<<izquierdo<<" - "<<derecho<<")";
                return izquierdo - derecho;
            case MULT: 
                cout<<"("<<izquierdo<<" * "<<derecho<<")";
                return izquierdo*derecho;
            case DIV: 
                cout<<"("<<izquierdo<<" / "<<derecho<<")";
                return izquierdo/derecho; //AGREGAR VALIDACIONES SEMÁNTICAS (DIVISIÓN ENTRE 0)
            case EXP: 
                cout<<"("<<izquierdo<<" ^ "<<derecho<<")";
                return pow(izquierdo,derecho);
        }
    }
    cout<<Mensaje::err_operador_desconocido;
    return 0.0;
}

bool Evaluator::esOperador(token t){
    tipoToken tipo = t.tipo;
    if(tipo == SUM || tipo == RES || tipo == MULT || tipo == DIV || tipo == EXP){
        return true;
    }else return false;
}