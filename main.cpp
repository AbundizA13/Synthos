#include "neonexus.h"
#include "syncolors.h"
#include "messages.h"
#include "commands.h"
#include "routines.h"
//#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <cmath>

using namespace std;

int main(){
    SetConsoleOutputCP(CP_UTF8);    
    SetConsoleCP(CP_UTF8);

    system("cls");

    imprimirLogo();

    bool ejecutando = true;
    Session session;
    
    
    
    
    //RUTINA PRINCIPAL MENU Y PETICIÓN DE RUTINA SECUNDARIA
    while(ejecutando){
        //Struct Command Invocation contiene información para la ejecución del próximo paso
        Command_Invocation invocacion = RUTINA_MENU(); 
        /* RUTINA_MENU es una función aislada que ejecuta
        el proceso completo para requerir el comando al usuario */

        //Cada case es un proceso distinto 
        rutinasPrincipales rutina = invocacion.rutina;
        if(rutina == rutinasPrincipales::expresion){
            Expresion nueva = rutinaExpresion(invocacion);
            string nombre;
            session.agregarExpr(nombre, nueva);
        }else if(rutina == rutinasPrincipales::salir){
            ejecutando = false;
        }else if(rutina == rutinasPrincipales::evaluar){
            //rutinaEvaluarAST(); /*SE DEBE CONOCER LA FUNCION A EVALUAR DEL MAPA DE SESSION ()*/
        }
            /*    break;

            case rutinasPrincipales::simplificar:

                break;

            case rutinasPrincipales::ayuda:
            */

            /*Sin default porque no habrá más casos*/
        
    }
    //debug_imprimirValorVariables(variables);
        /* MENSAJE DESPEDIDA */
    cout<<Mensaje::thankyou;
    esperarENTER();
    return 0;
}






