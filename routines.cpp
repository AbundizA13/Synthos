#include "commands.h"
#include "messages.h"
#include "neonexus.h"
#include "nodes.h"
#include <iostream> 
#include <iomanip>
#include <cmath>
#include <optional>

using namespace std;



Expresion rutinaExpresion(const Command_Invocation& invocacion){    
    //Procesar expresión como AST y retornar estructura Expresión lista
    Expresion actual;
    string expresion;

    auto argumentos = invocacion.argumentos;
    if(argumentos.empty()){
        cout << Mensaje::pedir_expresion;
        getline(cin, expresion);
    }else{
        expresion = argumentos[0]; //Se toma solo el primer argumento como expresión
    }
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
    Nodo* raiz = parser.raiz.get();
    actual.raiz = std::move(parser.raiz);

    if(raiz != nullptr){
            cout<<Mensaje::impresion_AST;
            parser.imprimirAST(raiz);
    }

    //Se asume que "raiz" no es nullptr, arreglar esto si aparece otro comportamiento.  
    //esperarENTER();
    return actual;
}

void requerirExpresion(unordered_map<string, unique_ptr<Expresion>>& expresiones, Expresion*& actual){
    /*SE DEBE AJUSTAR STRUCT EXPRESION Y DARLE UN NOMBRE A LAS EXPRESIONES
    PARA PODER PEDIR NOMBRE DE EXPRESIÓN Y NO EL INPUT ENTERO*/

    size_t num_expresiones = expresiones.size();
    cout<<Mensaje::expresiones_agregadas(num_expresiones);
    string nombre;
    while(true){
        cout<<Mensaje::buscar_expresion;
        getline(cin, nombre);
        if(nombre.empty()){
            actual = nullptr;
            cout<<Mensaje::saliendo;
            return;
        }
        
        //Verificar si la expresión está en el mapa de expresiones
        auto* encontrada = encontrarExpresion(nombre, expresiones);
        if(encontrada == nullptr){
            continue;
        }
        actual = encontrada;
        return;
    }
}

Expresion* encontrarExpresion(const string& nombre, unordered_map<string, unique_ptr<Expresion>>& expresiones){
    auto iterador = expresiones.find(nombre);
    if(iterador == expresiones.end()){
        cout<<Mensaje::expresion_no_encontrada;
        return nullptr; //Seguir intentando
    }
        cout<<Mensaje::expresion_encontrada;
        return iterador->second.get();
}

void rutinaEvaluarAST(const Expresion& expresion){
    Evaluator evaluator(expresion);
    evaluator.asignarValorVariables();

    //double resultado = 0.0;
    ContextoEvaluator contexto(evaluator.variables, evaluator.funciones);
    auto res = evaluator.evaluarAST(expresion.raiz.get(), contexto);
    if(!res.has_value()){
        cout<<Mensaje::err_evaluarAST;
        return;
    }
    cout<<Mensaje::impresion_resultado;
    double resultado = res.value();

    if(abs(resultado) <= 0.00001 && abs(resultado) > 0){
        if(abs(resultado) < 0.000000000001){
            cout<<resultado<<fixed<<setprecision(17)<<" ("<<resultado<<").\n";
        }else cout<<resultado<<fixed<<setprecision(11)<<" ("<<resultado<<").\n";
    }else{
        cout<<resultado<<".\n";
    }
    return;
}

