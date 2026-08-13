#include <windows.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <optional>

#include "neonexus.h"
#include "syncolors.h"
#include "messages.h"
#include "commands.h"
#include "routines.h"

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
        auto& expresionesRef = session.expresiones;
        if(!expresionesRef.empty()){
            cout << Mensaje::expresiones_agregadas(expresionesRef.size());
        }
        //Struct Command Invocation contiene información para la ejecución del próximo paso
        Command_Invocation invocacion = RUTINA_MENU(); 
        /* RUTINA_MENU es una función aislada que ejecuta
        el proceso completo para requerir el comando al usuario */

        //Cada case es un proceso distinto 
        rutinasPrincipales rutina = invocacion.rutina;
        if(rutina == rutinasPrincipales::expresion){
            Expresion nueva = rutinaExpresion(invocacion);
            /*
            if(invocacion.argumentos.empty()){
                nueva = rutinaExpresion(invocacion);
            }else{
                nueva = rutinaExpresionExpress(invocacion);
            }*/
            cout<<Mensaje::pedir_nombre_expr;
            string nombre;
            getline(cin, nombre);
            session.agregarExpr(nombre, nueva);
            esperarENTER();
    
            system("cls");
            imprimirLogo();
        }else if(rutina == rutinasPrincipales::salir){
            ejecutando = false;
        }else if(rutina == rutinasPrincipales::evaluar){
            //Hacer alguna validación en caso de no tener expresiones.
            if(expresionesRef.empty()){
                cout<<Mensaje::sin_expresiones;
                continue;
            }
            Expresion actual;
            
            auto& argumentosRef = invocacion.argumentos;
            
            if(!invocacion.argumentos.empty()){
                auto expresionActual = encontrarExpresion(argumentosRef[0], expresionesRef);
                if(!expresionActual.has_value()){
                    requerirExpresion(expresionesRef, actual);
                }else{
                    actual = expresionActual.value();
                }
            }else{
                requerirExpresion(expresionesRef, actual);
            }


            
            if(actual.raiz == nullptr) continue; //Devuelve al principio del menu
            rutinaEvaluarAST(actual); /*SE DEBE CONOCER LA FUNCION A EVALUAR DEL MAPA DE SESSION ()*/
            
            esperarENTER();
            system("cls");
            imprimirLogo();
        }else if(rutina == rutinasPrincipales::ayuda){
            cout << Mensaje::despliegue_comandos;
            for(auto comando : Mensaje::lista_comandos){
                cout << comando<<"\n";
            }

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






