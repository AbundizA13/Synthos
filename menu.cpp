#include "neonexus.h"
#include "commands.h"
#include "messages.h"
#include <iostream>

string RUTINA_MENU(){ //Impresión de logo Synthos y petición de rutina/comando al usuario.
    imprimirLogo();
    string comando;
    while(true){

        cout << Mensaje::pedir_comando;
        getline(cin, comando);

        CommandResult resultado;
        CommandManager cmdManager(comando);
        Comando nuevoComando = cmdManager.tokenizarComando();
    //Struct comando creado
    }
}