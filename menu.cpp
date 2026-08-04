#include "neonexus.h"
#include "commands.h"
#include "messages.h"
#include <iostream>

string RUTINA_MENU(){ //Impresión de logo Synthos y petición de rutina/comando al usuario.
    imprimirLogo();
    cout << Mensaje::pedir_comando;
    string comando;
    getline(cin, comando);

    CommandManager cmdManager(comando);
    Comando nuevoComando = cmdManager.tokenizarComando();
    //Struct comando creado
    
}