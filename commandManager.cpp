#include "commands.h"
#include "messages.h"
#include <string>
#include <sstream>
#include <unordered_map>
#include <iostream>

using namespace std;

const unordered_map<string, rutinasPrincipales> mapaRutinas = {
    {"salir", salir},
    {"expresion", expresion},
    {"evaluar", evaluar},
    {"simplificar", simplificar},
    {"ayuda", ayuda}
};

CommandManager::CommandManager(const string& comando)
    : texto(comando){}

Comando CommandManager::tokenizarComando(){
    Comando nuevoComando;
    stringstream ss(texto);

    string palabra;

    size_t args = 0;

    while(ss >> palabra){
        if(args > 0){ //Argumento detectado
            nuevoComando.tokens.push_back(palabra);
        }else{ //Comando principal detectado
            nuevoComando.principal = palabra;
        }
        args++;
    }
    nuevoComando.args = args;
    return nuevoComando;
}

CommandParser::CommandParser(const Comando& comando)
    : comando(comando), indice_argumentos(0){}

CommandResult CommandParser::parseRoutine(){
    Command_Invocation invocacion;
    
    string rutina_cruda = comando.principal;
    if(rutina_cruda.empty()){
        //AGREGAR MENSAJE DE ERROR.
        cout<<Mensaje::err_rutina_vacia;
        resultado.exito = false;
        return resultado;
    }
    
    auto iterador = mapaRutinas.find(rutina_cruda);
        if(iterador == mapaRutinas.end()){
            cout<<Mensaje::err_rutina_desconocida(rutina_cruda);
            resultado.exito = false;
            return resultado;

        }
        /*Rutina capturada correctamente*/
    rutinasPrincipales rutina = iterador->second;
    invocacion.rutina = rutina;

    resultado.invocacion = invocacion;
    parseArguments();

    return resultado; //Después de no encontrar ningun error
}

CommandResult CommandParser::parseArguments(){
    vector<string> tokens = comando.tokens;
    while(indice_argumentos < tokens.size()){
        if(!(tokenEsFlag(tokens[indice_argumentos]))){ //Mientras los tokens no sean flags, tratalas como argumentos.

            continue;
        }
        /*Termina parseo de argumentos y comienzan las flags*/
        
    };
}

bool CommandParser::tokenEsFlag(const string& token){
    if(token.size() > 2 && token[0] == '-' && token[1] == '-') return true;
    return false;
}