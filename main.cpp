#include "neonexus.h"
//#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <string>

#define R Color::texto_base
#define M Color::menu_marco
#define P Color::menu_principal
#define S Color::menu_secundario

using namespace std;

void imprimirLogo();

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    system("cls");

    imprimirLogo();
    cout <<Color::input_principal<<"\n[INPUT] "
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
    evaluator.escanearVariables();

        /* IMPRESIÓN DE TOKENS*/
    for(int i=0;i<tokens.size();i++){
        cout<< "(T_#"<<i<<"): "<<tokens[i].contenido<<"\n";
    }

        /* PARSER */
    Parser parser(tokens); //Construcción de clase 'Parser'
    parser.parseExpression();
    Nodo* raiz = parser.raiz;
        /* IMPRIMIR AST */
    if(raiz != nullptr){
        cout<<Color::hl_positivo1<<"\nImpresión de AST:\n";
        parser.imprimirAST(raiz);
    }


        /* MENSAJE DESPEDIDA */
    cout<<Color::hl_positivo2<<"\n\nGracias por utilizar Synthos :)";
    esperarENTER();


    return 0;
}




void esperarENTER(){ //Agregar cin.ignore() antes de la función, en caso de tener '\n' en el buffer
    cout <<Color::hl_positivo2<<"\n\nENTER "
    <<R<<"para continuar.";

    cin.get();
}

void imprimirLogo(){
    cout << "\t\t" << M << "__________________________________________________________________________\n";
    cout << "\t\t|" << S << "   ______  __      __  __    __  ________  __    __   ______    ______   " << M << "|\n";
    cout << "\t\t|" << S << "  /      \\|  \\    /  \\|  \\  |  \\|        \\|  \\  |  \\ /      \\  /      \\  " << M << "|\n";
    cout << "\t\t|" << S << " |  " << P << "$$$$$$" << S << "\\\\" << P << "$$" << S << "\\  /  " << P << "$$" << S << "| " << P << "$$" << S << "\\ | " << P << "$$ " << S << "\\" << P << "$$$$$$$$" << S << "| " << P << "$$  " << S << "| " << P << "$$" << S << "|  " << P << "$$$$$$" << S << "\\|  " << P << "$$$$$$" << S << "\\ " << M << "|\n";
    cout << "\t\t|" << S << " | " << P << "$$" << S << "___\\" << P << "$$ " << S << "\\" << P << "$$" << S << "\\/  " << P << "$$ " << S << "| " << P << "$$$" << S << "\\| " << P << "$$   " << S << "| " << P << "$$   " << S << "| " << P << "$$" << S << "__| " << P << "$$" << S << "| " << P << "$$  " << S << "| " << P << "$$" << S << "| " << P << "$$" << S << "___\\" << P << "$$ " << M << "|\t" << P << "ALGEBRAIC\n";
    cout << "\t\t" << M << "|" << S << "  \\" << P << "$$    " << S << "\\   \\" << P << "$$  $$  " << S << "| " << P << "$$$$" << S << "\\ " << P << "$$" << S << "   | " << P << "$$" << S << "   | " << P << "$$    $$" << S << "| " << P << "$$  " << S << "| " << P << "$$ " << S << "\\" << P << "$$    " << S << "\\  " << M << "|\t  " << P << "PARSER\n";
    cout << "\t\t" << M << "|" << S << "  _\\" << P << "$$$$$$" << S << "\\   \\" << P << "$$$$   " << S << "| " << P << "$$" << S << "\\" << P << "$$ $$" << S << "   | " << P << "$$" << S << "   | " << P << "$$$$$$$$" << S << "| " << P << "$$  " << S << "| " << P << "$$ " << S << "_\\" << P << "$$$$$$" << S << "\\ " << M << "|\n";
    cout << "\t\t|" << S << " |  \\__| " << P << "$$   " << S << "| " << P << "$$    " << S << "| " << P << "$$ " << S << "\\" << P << "$$$$   " << S << "| " << P << "$$   " << S << "| " << P << "$$  " << S << "| " << P << "$$" << S << "| " << P << "$$" << S << "__/ " << P << "$$" << S << "|  \\__| " << P << "$$ " << M << "|\n";
    cout << "\t\t|" << S << "  \\" << P << "$$    $$   " << S << "| " << P << "$$    " << S << "| " << P << "$$  " << S << "\\" << P << "$$$   " << S << "| " << P << "$$   " << S << "| " << P << "$$  " << S << "| " << P << "$$ " << S << "\\" << P << "$$    $$ " << S << "\\" << P << "$$    $$ " << M << "|  " << S << "DEV: Andrés Abundiz\n";
    cout << "\t\t" << M << "|" << S << "   \\" << P << "$$$$$$     " << S << "\\" << P << "$$     " << S << "\\" << P << "$$   " << S << "\\" << P << "$$    " << S << "\\" << P << "$$    " << S << "\\" << P << "$$   " << S << "\\" << P << "$$  " << S << "\\" << P << "$$$$$$   " << S << "\\" << P << "$$$$$$  " << M << "|\n";
    cout << "\t\t|" << M << "_________________________________________________________________________|\n";
}