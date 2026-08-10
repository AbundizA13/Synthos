#include "commands.h"
#include "messages.h"
#include "neonexus.h"
#include <iostream> 

using namespace std;

Expresion rutinaExpresion(const Command_Invocation& invocacion){    
    //Procesar expresión como AST y retornar estructura Expresión lista
    Expresion actual;

    cout << Mensaje::pedir_expresion;
    string expresion;
    getline(cin, expresion);
        actual.original = expresion;

    Lexer lexer(expresion); //Clase lexer con input como parámetro
    vector<token> tokens; //Vector de tokens
    tokens = lexer.tokenizar(); //Lexer devuelve vector de tokens relleno.

    Evaluator evaluator(tokens); //Clase evaluator recibe tokens
    unordered_map<string, Variable> variables;
    variables = evaluator.escanearVariables(); //Variables guardadas en evaluator.variables (cambiar a )
    if(variables.empty()){
        cout << Mensaje::variables_encontradas;
    }else{
        cout << Mensaje::variables_encontradas(variables.size());
    }
    actual.variables = variables; //Variables guardadas en expresión a devolver

    size_t tamanoTokens = tokens.size();
    cout<<Mensaje::tokens_reconocidos(tamanoTokens);
    for(int i=0;i<tamanoTokens;i++){
        cout<<Mensaje::token_individual(i,tokens[i].contenido);
    }

    Parser parser(tokens); //Recibe lista de tokens;
    parser.parseExpression();
    Nodo* raiz = parser.raiz;
    actual.raiz = raiz;

    if(raiz != nullptr){
            cout<<Mensaje::impresion_AST;
            parser.imprimirAST(raiz);
    }

    //Se asume que "raiz" no es nullptr, arreglar esto si aparece otro comportamiento.  
    return actual;
}