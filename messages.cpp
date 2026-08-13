#include <iostream>
#include "neonexus.h"
#include "syncolors.h"
#include "messages.h"



using namespace std;
using namespace Mensaje;;

void esperarENTER(){ //Agregar cin.ignore() antes de la función, en caso de tener '\n' en el buffer
    cout << Mensaje::esperando_enter;

    cin.get();
}

void imprimirLogo(){
    cout << "\t\t" << M << "__________________________________________________________________________\n";
    cout << "\t\t|" << S << "   ______  __      __  __    __  ________  __    __   ______    ______   " << M << "|\n";
    cout << "\t\t|" << S << "  /      \\|  \\    /  \\|  \\  |  \\|        \\|  \\  |  \\ /      \\  /      \\  " << M << "|\n";
    cout << "\t\t|" << S << " |  " << P << "$$$$$$" << S << "\\\\" << P << "$$" << S << "\\  /  " << P << "$$" << S << "| " << P << "$$" << S << "\\ | " << P << "$$ " << S << "\\" << P << "$$$$$$$$" << S << "| " << P << "$$  " << S << "| " << P << "$$" << S << "|  " << P << "$$$$$$" << S << "\\|  " << P << "$$$$$$" << S << "\\ " << M << "|\n";
    cout << "\t\t|" << S << " | " << P << "$$" << S << "___\\" << P << "$$ " << S << "\\" << P << "$$" << S << "\\/  " << P << "$$ " << S << "| " << P << "$$$" << S << "\\| " << P << "$$   " << S << "| " << P << "$$   " << S << "| " << P << "$$" << S << "__| " << P << "$$" << S << "| " << P << "$$  " << S << "| " << P << "$$" << S << "| " << P << "$$" << S << "___\\" << P << "$$ " << M << "|\t" << P << "ALGEBRAIC\n";
    cout << "\t\t" << M << "|" << S << "  \\" << P << "$$    " << S << "\\   \\" << P << "$$  $$  " << S << "| " << P << "$$$$" << S << "\\ " << P << "$$" << S << "   | " << P << "$$" << S << "   | " << P << "$$    $$" << S << "| " << P << "$$  " << S << "| " << P << "$$ " << S << "\\" << P << "$$    " << S << "\\  " << M << "|\t  " << P << "PARSER\n";
    cout << "\t\t" << M << "|" << S << "  _\\" << P << "$$$$$$" << S << "\\   \\" << P << "$$$$   " << S << "| " << P << "$$" << S << "\\" << P << "$$ $$" << S << "   | " << P << "$$" << S << "   | " << P << "$$$$$$$$" << S << "| " << P << "$$  " << S << "| " << P << "$$ " << S << "_\\" << P << "$$$$$$" << S << "\\ " << M << "|\n";
    cout << "\t\t|" << S << " |  \\__| " << P << "$$   " << S << "| " << P << "$$    " << S << "| " << P << "$$ " << S << "\\" << P << "$$$$   " << S << "| " << P << "$$   " << S << "| " << P << "$$  " << S << "| " << P << "$$" << S << "| " << P << "$$" << S << "__/ " << P << "$$" << S << "|  \\__| " << P << "$$ " << M << "|\n";
    cout << "\t\t|" << S << "  \\" << P << "$$    $$   " << S << "| " << P << "$$    " << S << "| " << P << "$$  " << S << "\\" << P << "$$$   " << S << "| " << P << "$$   " << S << "| " << P << "$$  " << S << "| " << P << "$$ " << S << "\\" << P << "$$    $$ " << S << "\\" << P << "$$    $$ " << M << "|  " << S << "DEV: Andrés Abundiz\n";
    cout << "\t\t" << M << "|" << S << "   \\" << P << "$$$$$$     " << S << "\\" << P << "$$     " << S << "\\" << P << "$$   " << S << "\\" << P << "$$    " << S << "\\" << P << "$$    " << S << "\\" << P << "$$   " << S << "\\" << P << "$$  " << S << "\\" << P << "$$$$$$   " << S << "\\" << P << "$$$$$$  " << M << "|\n";
    cout << "\t\t|" << M << "_________________________________________________________________________|\n";
}

int preguntarEvaluacion(){
    int opcion = -1;
    cout<<Mensaje::preguntar_evaluacion;
    while(opcion < 0 || opcion > 1){
        cin >> opcion;
        cin.ignore();
    }
    return opcion;
}

string Mensaje::variables_encontradas(int n){
    return tag_debug+"Se detectaron "+to_string(n)+" variables en la expresión.\n"+R;
}

string Mensaje::tokens_reconocidos(size_t n){
    return tag_debug+"Tokens reconocidos ("+to_string(n)+"):\n"+R;
}

string Mensaje::token_individual(int i, const string& contenido){
    return hl_positivo0+"["+to_string(i)+"]: "+hl_positivo1+contenido+"\n";
}

string Mensaje::pedir_valor_variable(const string& nombre){
    return texto_base+"Dame valor para la variable '"+nombre+"': "+texto_secundario;
}

string Mensaje::err_token_desconocido(const char& actual){
    return tag_errorInterno+"Se intentó tokenizar un caracter desconocido \""+actual+"\".\n";
}

string Mensaje::err_rutina_desconocida(const string& rutina){
    return tag_error+"Se desconoce la rutina \""+rutina+"\".\nPor favor, introduce un comando válido.\n\n"+R;
}

string Mensaje::expresiones_agregadas(size_t num){
    return tag_debug+"Se detectaron "+std::to_string(num)+" expresion(es).\n"+R;
}

/*
    <"2+x^3" , "A1">
    (A1): 2+x^3
*/
string Mensaje::debug_sess_expr_agregada(const string& expresion, const string& nombre){
    return tag_debug+"Se agregó una expresión a la sesión actual. \n("+nombre+"): "+expresion+"\n"+R;
}

string Mensaje::expresiones_registradas(const size_t expresiones){
    return hl_positivo2+"Se han registrado ("+to_string(expresiones)+") expresion(es).\n";
}


/*
void debug_imprimirValorVariables(unordered_map<string,Variable>& variables){
    for(auto variable : variables){
        cout<<variable.first<<": "<<variable.second.valor;
    }
}*/