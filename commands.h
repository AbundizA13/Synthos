#ifndef SYNTHOS_COMMANDS_H
#define SYNTHOS_COMMANDS_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

enum rutinasPrincipales{
    salir,
    expresion,
    evaluar,
    simplificar,
    ayuda,
};

extern const unordered_map<string, rutinasPrincipales> mapaRutinas;

struct Comando{
    string principal;
    vector<string> tokens;
    size_t args;
};

struct Command_Invocation{
    rutinasPrincipales rutina;
    vector<string> argumentos;
    unordered_map<string, string> flags;
};

class CommandManager{
    private:
        string texto;
    public:
        CommandManager(const string& comando);
        Comando tokenizarComando();
        //Command_Invocation parsearComando();
};

class CommandParser{
    private:
        Comando comando;
        size_t indice_argumentos;
        CommandResult parseRoutine();
        /*Funciones recursivas de gramática comando*/
    public:
        CommandParser(const Comando& comando);
};

struct CommandResult{   
    bool exito = true;
    Command_Invocation invocacion;
};

#endif