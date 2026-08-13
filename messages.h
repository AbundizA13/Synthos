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
    const string tag_debug = hl_debug1+"\n[DEBUG] "+hl_debug0;
    /*GLOBAL*/
    string expresiones_registradas(const size_t expresiones);
    const string saliendo = hl_positivo1+"\nSaliendo...\n"+R;
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
    const string err_funcion_sin_argumento = tag_error+"No se introdujo el argumento necesario en una función.\n"+R;
    const string err_evaluarAST = tag_errorInterno+"Se detectó un AST vacío.\n\n"+R;
    /*LEXER*/
    string tokens_reconocidos(size_t n);
    string token_individual(int i, const string& contenido);
    const string adv_decimal_duplicado = "\n"+tag_advertencia+"Se detectaron +1 puntos decimales en una constante.\n"+R;
    string err_token_desconocido(const char& actual); 
    /*PARSER*/
    const string impresion_AST = tag_debug+"Impresión de AST:\n"+R;
    const string err_parentesis_abierto = tag_error+"Sintaxis incorrecta, se esperaba \")\".\n"+R;
    const string err_token_desconocido_parser = tag_errorInterno+"Token desconocido en función \"parseFactor();\".\n"+R;
    const string impresion_token_desconocido = hl_negativo1+"ERR";
    /*INPUT*/
    const string sin_expresiones = tag_error+"Favor de introducir una expresión antes de evaluar."+R;
    const string pedir_expresion = tag_input+"\nDame una expresión para ser reconocida: "+R;
    const string pedir_nombre_expr = tag_input+"\nDame el nombre de la expresión introducida: "+R;
    const string buscar_expresion = tag_input+"Dame el nombre de la expresión a buscar (Dejar vacío para salir): "+R;
    const string expresion_no_encontrada = tag_error+"No se encontró la expresión introducida.\nPor favor intentar de nuevo.\n\n"+R;
    const string expresion_encontrada = hl_positivo2+"\nSe encontró la expresión.\n\n"+R;
    const string esperando_enter = hl_positivo2+"\n\nENTER "+R+"para continuar.";
    const string preguntar_evaluacion = hl_positivo2+"\n\n¿Desea evaluar la expresión ingresada?\n[1] Sí\t[0] No\n"+R;
    string pedir_valor_variable(const string& nombre);
    /*MENU*/
    const string pedir_comando = hl_positivo2+"\nIntroducir comando para continuar ('ayuda' para lista de comados): "+R;
    const string err_rutina_vacia = tag_errorInterno+"Rutina vacía al entrar a CommandParser. \nPor favor, introduce un comando válido.\n\n"+R;
    string err_rutina_desconocida(const string& rutina);
    const string despliegue_comandos = hl_positivo1+"\n\nMenú de comandos:\n"+R;
    const vector<string> lista_comandos = {
        hl_positivo2+"'salir' "+hl_positivo0+"cierra el programa y sus procesos."+R,
        hl_positivo2+"'expresion' "+hl_positivo0+"captura una expresión y la guarda en la sesión actual."+R,
        hl_positivo2+"'evaluar' "+hl_positivo0+"evalua una expresión ya capturada en la sesión."+R,
        hl_positivo2+"'ayuda' "+hl_positivo0+"despliega este menú."+R
    };

    /*DEBUG*/
    string expresiones_agregadas(size_t num);
    string debug_sess_expr_agregada(const string& expresion, const string& nombre);
    //const string debug_sess_expr_agregada = tag_debug+"Se agregó una expresión a la sesión actual";
    const string argumentos_vacios = tag_debug+"No se detectaron argumentos en el comando ingresado."+R;

    const string thankyou = hl_positivo2+"\n\nGracias por apoyar a este proyecto :)"+R;
}   

#endif