#include "commands.h"
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

CommandManager::CommandManager(const string& comando)
    : texto(comando){}

Comando CommandManager::tokenizarComando(){
    Comando nuevoComando;
    stringstream ss(texto);

    string palabra;

    size_t args = 0;

    while(ss >> palabra){
        if(args > 0){ //Argumento detectado
            nuevoComando.argumentos.push_back(palabra);
        }else{ //Comando principal detectado
            nuevoComando.principal = palabra;
        }
        args++;
    }
    nuevoComando.args = args;
    return nuevoComando;
}

Command_Invocation CommandManager::parsearComando(){
    
}
