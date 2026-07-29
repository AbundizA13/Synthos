#ifndef SYNTHOS_MESSAGES_H
#define SYNTHOS_MESSAGES_H

#include "neonexus.h"
#include "syncolors.h"

using namespace Color;
using namespace std;

namespace Mensaje{
    //CAMBIAR NOMBRE OUTPUT.CPP -> MESSAGES.CPP Y SOLUCIONAR LO DE INLINE
    const string pedir_expresion = input_principal+"[INPUT] "+input_secundario+"Dame una expresión para ser reconocida: "+R;

    const string variables_noEncontradas = hl_positivo1+"\nNo se hallaron variables en la expresión.\n\n"+R;
    inline string variables_encontradas(int n){
        return hl_positivo1+"\nSe detectaron "+to_string(n)+" variables en la expresión.\n\n"+R;
    } 

    inline string tokens_reconocidos(size_t n){
        return hl_positivo2+"Tokens reconocidos ("+to_string(n)+"):\n"+R;
    }
    inline string token_individual(int i, const string& contenido){
        return hl_positivo0+"["+to_string(i)+"]: "+hl_positivo1+contenido+"\n";
    }

    const string esperando_enter = hl_positivo2+"\n\nENTER "+R+"para continuar.";
    const string preguntar_evaluacion = hl_positivo2+"\n\n¿Desea evaluar la expresión ingresada?\n[1] Sí\t[0] No\n"+R;
}

#endif