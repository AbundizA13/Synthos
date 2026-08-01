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
    vector<string> argumentos;
    size_t args;
};

typedef struct Parser_Comando{
    rutinasPrincipales tipo; //Rutina principal del comando
    vector<string> argumentos;
    vector<string> configuraciones;

    Parser_Comando(rutinasPrincipales tipo)
        : tipo(tipo){}
}Comando_Parser;

class CommandManager{
    private:
        string texto;
        Comando comando;
    public:
        CommandManager(const string& comando);
        Comando tokenizarComando();
        Comando_Parser parsearComando();
};



#endif