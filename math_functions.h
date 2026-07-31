#ifndef SYNTHOS_MATHFUNC_H
#define SYNTHOS_MATHFUNC_H

#include <unordered_map>
#include <functional>
#include <string>

using namespace std;

unordered_map<string, function<double(double)>> obtenerFuncionesMatematicas();
double sec(double x);
double csc(double x);
double cot(double x);

#endif