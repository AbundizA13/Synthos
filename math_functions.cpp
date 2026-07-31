#include "math_functions.h"
#include <cmath>


unordered_map<string, function<double(double)>> obtenerFuncionesMatematicas(){
    return {
        {"sin", [](double x){return std::sin(x);}},
        {"cos", [](double x){return std::cos(x);}},
        {"tan", [](double x){return std::tan(x);}},
        {"sec", sec},
        {"csc", csc},
        {"cot", cot},
        {"sqrt", [](double x){return std::sqrt(x);}},
        {"log", [](double x){return std::log10(x);}},
        {"ln", [](double x){return std::log(x);}},
        {"exp", [](double x){return std::exp(x);}},
        {"abs", [](double x){return std::abs(x);}},
        {"floor", [](double x){return std::floor(x);}},
        {"ceil", [](double x){return std::ceil(x);}},
        {"round", [](double x){return std::round(x);}},
        
    };
}


double sec(double x){
    return 1.0/std::cos(x);
}

double csc(double x){
    return 1.0/std::sin(x);
}

double cot(double x){
    return std::cos(x)/std::sin(x);
}