#include "commands.h"
#include "messages.h"
#include "neonexus.h"
#include <iostream> 
#include <iomanip>
#include <cmath>

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

    Evaluator evaluator(tokens); //Clase evaluator recibe tokens y ejecuta escanearVariables()
    unordered_map<string, Variable> variables;
    variables = evaluator.variables; //Variables guardadas en evaluator.variables (cambiar a )
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
    esperarENTER();
    return actual;
}

Expresion& requerirExpresion(unordered_map<string, Expresion>& expresiones){
    /*SE DEBE AJUSTAR STRUCT EXPRESION Y DARLE UN NOMBRE A LAS EXPRESIONES
    PARA PODER PEDIR NOMBRE DE EXPRESIÓN Y NO EL INPUT ENTERO*/
}

double rutinaEvaluarAST(const Expresion& expresion){
    Evaluator evaluator(expresion);
    evaluator.asignarValorVariables();

    double resultado = 0.0;

    resultado = evaluator.evaluarAST(expresion.raiz);
    cout<<Mensaje::impresion_resultado;

    if(abs(resultado) <= 0.00001 && abs(resultado) > 0){
        if(abs(resultado) < 0.000000000001){
            cout<<resultado<<fixed<<setprecision(17)<<" ("<<resultado<<").\n";
        }else cout<<resultado<<fixed<<setprecision(11)<<" ("<<resultado<<").\n";
    }else{
        cout<<resultado<<".\n";
    }
    return; //cold
    esperarENTER();
}
