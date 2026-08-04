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
        Comando comando;
    public:
        CommandManager(const string& comando);
        Comando tokenizarComando();
        //Command_Invocation parsearComando();
};

class CommandParser{
    private:
        /*Funciones recursivas de gramática comando*/
    public:
        CommandParser(const Comando& comando);
};

#endif