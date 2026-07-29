#ifndef SYNTHOS_MESSAGES_H
#define SYNTHOS_MESSAGES_H

#include "neonexus.h"
#include "syncolors.h"

using namespace Color;
using namespace std;

namespace Mensaje{
    /*TAGS*/
    const string tag_input = input_principal+"\n[INPUT] "+input_secundario;
    const string tag_error = hl_negativo1+"\n[ERROR] "+hl_negativo0;
    const string tag_errorInterno = hl_negativo1+"\n[ERROR INTERNO] "+hl_negativo0;
    const string tag_advertencia = hl_advertencia1+"\n[ADVERTENCIA] "+hl_advertencia0;
    

    /*EVALUATOR*/
    const string variables_noEncontradas = hl_positivo1+"\nNo se hallaron variables en la expresión.\n\n"+R;
    string variables_encontradas(int n);
    const string impresion_resultado = hl_positivo2+"\n\nResultado: "+hl_positivo0;
    const string error_tokensNulos = tag_errorInterno+"No se detectaron tokens en Evaluator.\n"+R;
    const string ignorando_caracteres = "\n"+tag_advertencia+"Ignorando caracteres adicionales después del valor capturado.\n\n"+R;
    const string valor_invalido = "\n"+tag_error+"Por favor introducir un valor decimal válido.\n\n"+R;
    const string valor_muyAlto = "\n"+tag_error+"El valor introducido es demasiado alto.\n\n"+R;
    const string nodo_inexistente = tag_error+"Se intentó procesar un nodo inexistente.\n"+R;
    const string variable_no_en_mapa = tag_errorInterno+"No se encontró la variable actual en el mapa de valores.\n"+R;
    const string operador_desconocido = tag_errorInterno+"Se intentó evaluar un operador desconocido.\n"+R;
    /*LEXER*/
    string tokens_reconocidos(size_t n);
    string token_individual(int i, const string& contenido);
    /*PARSER*/
    const string impresion_AST = hl_positivo2+"\nImpresión de AST:\n"+R;
    /*INPUT*/
    const string pedir_expresion = tag_input+"Dame una expresión para ser reconocida: "+R;
    const string esperando_enter = hl_positivo2+"\n\nENTER "+R+"para continuar.";
    const string preguntar_evaluacion = hl_positivo2+"\n\n¿Desea evaluar la expresión ingresada?\n[1] Sí\t[0] No\n"+R;
    string pedir_valor_variable(const string& nombre);

    const string thankyou = hl_positivo2+"\n\nGracias por apoyar a este proyecto :)"+R;
}   

#endif