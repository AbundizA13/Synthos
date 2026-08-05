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

void CommandParser::parseArguments(){
    if(comando.tokens.empty()){
        cout << Mensaje::argumentos_vacios;
        return;
    }
    vector<string> tokens = comando.tokens;
    while(indice_argumentos < tokens.size()){
        string tokenActual = tokens[indice_argumentos];
        if(!(tokenEsFlag(tokenActual))){ //Mientras los tokens no sean flags, tratalas como argumentos.
            resultado.invocacion.argumentos.push_back(tokenActual);
            indice_argumentos++;
            continue;
        }
        parseFlags();
        return;
    };
    return;
}

void CommandParser::parseFlags(){
    vector<string> tokens = comando.tokens;
    size_t tamano = tokens.size();
    while(indice_argumentos < tamano){
        //cout << tokens[indice_argumentos] << "\n";
        pair<string, string> flag;
        cout<<"\nCreando par de strings para flag.";
        flag.first = tokens[indice_argumentos];
        if((indice_argumentos+1) < tamano && !tokenEsFlag(tokens[indice_argumentos+1])){
            cout << "\nSe detectó un flag con valor.\n";
            /*Si queda al menos un argumento, y no es flag, se toma como valor del último flag*/
            flag.second = tokens[indice_argumentos+1];
            indice_argumentos += 2;
        }else{
            /*Si era otra flag, o ya no había espacio*/
            cout << "\nSe detectó un flag sin valor.\n";
            flag.second = "true";
            indice_argumentos++;
        }
        cout << "\nGuardando flag <"<<flag.first<<", "<<flag.second<<">.";
        cout << "Indice : ("<<indice_argumentos<<"/"<<tamano<<").\n";
        resultado.invocacion.flags.emplace(flag);
    }
    return;
}

bool CommandParser::tokenEsFlag(const string& token){
    if(token.size() > 2 && token[0] == '-' && token[1] == '-') return true;
    return false;
}