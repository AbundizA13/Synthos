#include "neonexus.h"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace Color;

/*AGREGAR REFERENCIAS A VARIABLES EN VEZ DE COPIAS*/

Evaluator::Evaluator(vector<token> tokens):
    tokens(std::move(tokens)), indice(0), variables()
    {}
    //this->tokens = tokens;
    //this->indice = 0;
    

void Evaluator::escanearVariables(){
    if(tokens.empty()){cout<<hl_negativo1<<"Error léxico"; return;}

    while(indice < tokens.size()){
        const token& actual = tokens[indice];
        if(actual.tipo == VAR){
            string variable = actual.contenido;
            variables.emplace(variable, Variable(0.0, true)); //Agrega variable solo si no existe ya
        }
        indice++;
    }
    return;
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
            cout<<texto_base<<"Dame valor para la variable '"<<nombre<<"': ";
            getline(cin,entrada);
            try{
                size_t posConversion = 0; //Posición en la que acabó la conversión
                valor = stod(entrada, &posConversion);

                if(posConversion != entrada.length()){
                    cout<<hl_positivo0<<"\n\nIgnorando caracteres adicionales después del valor capturado.\n\n";
                }
            }catch(const invalid_argument& e){
                cout<<hl_negativo1<<"\n\nERROR, por favor introducir un valor decimal válido.\n\n";
                continue;
            }catch(const out_of_range& e){
                cout<<hl_negativo1<<"\n\nERROR, el valor introducido es demasiado alto.\n\n";
                continue;
            }
            break;
        }

        contenido.valor = valor;
    }
}