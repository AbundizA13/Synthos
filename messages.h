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
    const string adv_ignorando_caracteres = "\n"+tag_advertencia+"Ignorando caracteres adicionales después del valor capturado.\n\n"+R;
    const string err_valor_invalido = "\n"+tag_error+"Por favor introducir un valor decimal válido.\n\n"+R;
    const string err_valor_muyAlto = "\n"+tag_error+"El valor introducido es demasiado alto.\n\n"+R;
    const string err_nodo_inexistente = tag_error+"Se intentó procesar un nodo inexistente.\n"+R;
    const string err_variable_no_en_mapa = tag_errorInterno+"No se encontró la variable actual en el mapa de valores.\n"+R;
    const string err_operador_desconocido = tag_errorInterno+"Se intentó evaluar un operador desconocido.\n"+R;
    /*LEXER*/
    string tokens_reconocidos(size_t n);
    string token_individual(int i, const string& contenido);
    const string adv_decimal_duplicado = "\n"+tag_advertencia+"Se detectaron +1 puntos decimales en una constante.\n"+R;
    string err_token_desconocido(const char& actual); 
    /*PARSER*/
    const string impresion_AST = hl_positivo2+"\nImpresión de AST:\n"+R;
    const string err_parentesis_abierto = tag_error+"Sintaxis incorrecta, se esperaba \")\".\n"+R;
    const string err_token_desconocido_parser = tag_errorInterno+"Token desconocido en función \"parseFactor();\".\n"+R;
    const string impresion_token_desconocido = hl_negativo1+"ERR";
    /*INPUT*/
    const string pedir_expresion = tag_input+"Dame una expresión para ser reconocida: "+R;
    const string esperando_enter = hl_positivo2+"\n\nENTER "+R+"para continuar.";
    const string preguntar_evaluacion = hl_positivo2+"\n\n¿Desea evaluar la expresión ingresada?\n[1] Sí\t[0] No\n"+R;
    string pedir_valor_variable(const string& nombre);
    /*MENU*/
    const string pedir_comando = hl_positivo2+"\nIntroducir comando para continuar ('help' para lista de comados): "+R;

    const string thankyou = hl_positivo2+"\n\nGracias por apoyar a este proyecto :)"+R;
}   

#endif