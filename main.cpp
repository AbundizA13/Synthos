#include "neonexus.h"
//#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string>



using namespace std;

void imprimirLogo();

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    system("cls");

    imprimirLogo();
    cout <<Color::input_principal<<"\n[INPUT] "
    //<<Color::input_secundario<<"Give me an expression to be processed: "<<R;
    <<Color::input_secundario<<"Dame una expresión para ser reconocida: "<<R;
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
        cout << Color::hl_positivo1<<"\nNo se hallaron variables en la expresión.\n\n";
    }else{
        cout << Color::hl_positivo1<<"\nSe detectaron "<<variables.size()<<" variables en la expresión.\n\n";
    }


        /* IMPRESIÓN DE TOKENS*/
    size_t tamanoTokens = tokens.size();
    cout<<Color::hl_positivo2<<"Tokens reconocidos ("<<tamanoTokens<<"):\n";
    for(int i=0;i<tamanoTokens;i++){
        cout<<Color::hl_positivo0<< "["<<i<<"]: "<<Color::hl_positivo1<<tokens[i].contenido<<"\n";
    }

        /* PARSER */
    Parser parser(tokens); //Construcción de clase 'Parser'
    parser.parseExpression();
    Nodo* raiz = parser.raiz;
        /* IMPRIMIR AST */
    if(raiz != nullptr){
        cout<<Color::hl_positivo2<<"\nImpresión de AST:\n";
        parser.imprimirAST(raiz);
    }
    int opcion = preguntarEvaluacion();
    double resultado = 0.0;
    
    if(opcion){ //SÍ se desea evaluar
        evaluator.asignarValorVariables(variables);

        resultado = evaluator.evaluarAST(raiz,variables);
        cout<<Color::hl_positivo2<<"\n\nResultado: "<<Color::hl_positivo0<<resultado<<".\n";
    }
    //debug_imprimirValorVariables(variables);

        /* MENSAJE DESPEDIDA */
    cout<<Color::hl_positivo2<<"\n\nGracias por apoyar a este proyecto :)";
    esperarENTER();


    return 0;
}






