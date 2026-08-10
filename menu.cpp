#include "neonexus.h"
#include "commands.h"
#include "messages.h"
#include <iostream>

Command_Invocation RUTINA_MENU(){ //Impresión de logo Synthos y petición de rutina/comando al usuario.
    string comando;
    while(true){

        cout << Mensaje::pedir_comando;
        getline(cin, comando);

        CommandResult resultado;
        CommandManager cmdManager(comando);
        Comando nuevoComando = cmdManager.tokenizarComando();
        CommandParser parser(nuevoComando);
        resultado = parser.parseRoutine();

        if(!resultado.exito){
            //Mensaje de error ya desplegado en la función correspondiente
            continue;
        }
        Command_Invocation invocacion = resultado.invocacion;
        return invocacion;
    }
    
}