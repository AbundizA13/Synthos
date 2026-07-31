#ifndef SYNTHOS_COMMANDS_H
#define SYNTHOS_COMMANDS_H

#include <string>
#include <vector>

using namespace std;

enum rutinasPrincipales{
    expresion,
    evaluar,
    simplificar,
    ayuda,
    salir
};

struct Comando{
    string principal;
    vector<string> argumentos;
    size_t args;
};

struct Parser_Comando{
    rutinasPrincipales tipo; //Rutina principal del comando
    vector<string> argumentos;
    vector<string> configuraciones;
};

class CommandManager{
    private:
        string texto;
        Comando comando;
    public:
        CommandManager(const string& comando);
        Comando tokenizarComando();
        Parser_Comando parsearComando();
};

#endif