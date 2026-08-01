#include "neonexus.h"
#include "syncolors.h"
#include "messages.h"
//#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <cmath>



using namespace std;

void imprimirLogo();

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    system("cls");

    //RUTINA PRINCIPAL MENU Y PETICIÓN DE RUTINA SECUNDARIA
    RUTINA_MENU();

    cout << Mensaje::pedir_expresion;
    string expresion;
    getline(cin, expresion);

    /*
    cout << '\n' << expresion;
    esperarENTER();*/

        /* LEXER */
    Lexer lexer(expresion); //Construcción de clase 'Lexer', con el input como parámetro
    vector<token> tokens; //Contenedor de tokens para el lexer
    tokens = lexer.tokenizar(); //lexer.tokenizar() rellena el contenedor de tokens
    
        /* EVALUATOR */
    Evaluator evaluator(tokens);
    evaluator.escanearVariables(); //Variables guardadas en evaluator.variables
    unordered_map<string, Variable> variables = evaluator.variables;
    if(variables.empty()){
        cout << Mensaje::variables_noEncontradas;
    }else{
        cout << Mensaje::variables_encontradas(variables.size());
    }


        /* IMPRESIÓN DE TOKENS*/
    size_t tamanoTokens = tokens.size();
    cout<<Mensaje::tokens_reconocidos(tamanoTokens);
    for(int i=0;i<tamanoTokens;i++){
        cout<<Mensaje::token_individual(i,tokens[i].contenido);
    }

        /* PARSER */
    Parser parser(tokens); //Construcción de clase 'Parser'
    parser.parseExpression();
    Nodo* raiz = parser.raiz;
        /* IMPRIMIR AST */
    if(raiz != nullptr){
        cout<<Mensaje::impresion_AST;
        parser.imprimirAST(raiz);
    }
    int opcion = preguntarEvaluacion();
    double resultado = 0.0;
    
    if(opcion){ //SÍ se desea evaluar
        evaluator.asignarValorVariables(variables);

        resultado = evaluator.evaluarAST(raiz,variables);
        cout<<Mensaje::impresion_resultado;
        
        if(abs(resultado) <= 0.00001 && abs(resultado) > 0){
            if(abs(resultado) < 0.000000000001){
                cout<<resultado<<fixed<<setprecision(17)<<" ("<<resultado<<").\n";
            }else cout<<resultado<<fixed<<setprecision(11)<<" ("<<resultado<<").\n";
        }else{
            cout<<resultado<<".\n";
        }
    }
    //debug_imprimirValorVariables(variables);

        /* MENSAJE DESPEDIDA */
    cout<<Mensaje::thankyou;
    esperarENTER();


    return 0;
}






