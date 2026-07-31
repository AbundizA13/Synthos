#ifndef SYNTHOS_COLORS_H
#define SYNTHOS_COLORS_H

#include <string>

#define R Color::texto_base
#define M Color::menu_marco
#define P Color::menu_principal
#define S Color::menu_secundario

using namespace std;

namespace Color{

    const string texto_base = "\x1b[38;5;194m";
    const string texto_secundario = "\x1b[38;5;114m";

    //MENSAJE PRINCIPAL DE REQUERIMIENTO DE INPUT
    const string input_principal = "\x1b[38;5;44m"; //[INPUT]
    const string input_secundario = "\x1b[38;5;222m"; //Descripción
    //IMPRESIÓN DE LOGO
    const string menu_marco = "\x1b[38;5;24m"; //Color de marco del logo
    const string menu_principal = "\x1b[38;5;222m"; //Color principal del logo
    const string menu_secundario = "\x1b[38;5;109m"; //Color secundario del logo
    //IMPRESIÓN DE MENSAJES
    const string hl_positivo0 = "\x1b[38;5;65m";
    const string hl_positivo1 = "\x1b[38;5;108m";
    const string hl_positivo2 = "\x1b[38;5;71m";
    const string hl_negativo0 = "\x1b[38;5;138m";
    const string hl_negativo1 = "\x1b[38;5;174m";
    const string hl_advertencia0 = "\x1b[38;5;144m";
    const string hl_advertencia1 = "\x1b[38;5;186m";
    const string AST_par = "\x1b[38;5;96m";
    const string AST_prim = "\x1b[38;5;133m";
    const string AST_op = "\x1b[38;5;182m";
    const string AST_func = "\x1b[38;5;217m";
}


#endif