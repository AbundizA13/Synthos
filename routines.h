#ifndef SYNTHOS_ROUTINES_H
#define SYNTHOS_ROUTINES_H

#include "commands.h"
#include "neonexus.h"

Expresion rutinaExpresion(const Command_Invocation& invocacion);
void rutinaEvaluarAST(const Expresion& expresion);
void requerirExpresion(unordered_map<string, Expresion>& expresiones, Expresion& actual);


#endif