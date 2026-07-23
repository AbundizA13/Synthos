#include "neonexus.h"
#include <unordered_map>
#include <iostream>
#include <vector>

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