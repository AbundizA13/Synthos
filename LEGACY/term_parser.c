#include "term_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int getExpression(char expresion[30], termino* terms_temp){ //Regresa el puntero realizado
    /*char *p = expresion;
    while(*p !='\n'){  
        if
    }*/


    int bool_exp = 0; 
    int term_tot = 0, i = 0,j = 0, k = 0;
    char *p = expresion;
    for(;*p != '\0';p++) { //Por cada caracter en la expresión...
        if(*p != '\n'){
            if(((*p != '+') && (*p != '-')) || (term_tot==0 && i==0)){ //Si no es un signo, o si es el primer caracter...
                if(*p == '^'){
                    bool_exp = 1;
                    terms_temp[term_tot].full_term[i++] = *p; //Guarda el caracter en el termino completo.
                }else{
                    terms_temp[term_tot].full_term[i++] = *p; //Guarda el caracter en el termino completo.
                    bool_exp = 0;
                }
            }else{ //Si es un signo y no es el primer caracter...
                if(bool_exp){ //Si es signo de un número del exponente.
                    terms_temp[term_tot].full_term[i++] = *p; //Guarda el caracter en el termino completo.
                }else{ //Si es un signo que no es del exponente ni es el primer carácter de la expresión.
                    terms_temp[term_tot].full_term[i] = '\0';
                    term_tot++; //Cambiamos de termino,
                    i = 0;
                    terms_temp[term_tot].full_term[i++] = *p; //Y lo agregamos al nuevo.
                }
            }

        }
    }
    terms_temp[term_tot].full_term[i] = '\0';
    //Todos los términos han sido agrupados.
    //Asignación de propiedades de cada término.
    for(j=0;j<term_tot+1;j++){ //Por cada término...
        bool_exp = 0;
        terms_temp[j].coeficiente = 1;
        terms_temp[j].grado = 1;
        terms_temp[j].variable = 0;
        terms_temp[j].signo = 1;
        for(p = terms_temp[j].full_term;*p != '\0';p++){ //Lee cada caracter del término completo.
            //Si es el primer carácter del termino y es un signo...
            if(p == &terms_temp[j].full_term[0] && (*p == '-' || *p == '+')){
                if(*p == '-'){
                    terms_temp[j].signo = 0;
                }else{
                    terms_temp[j].signo = 1;
                }
            }else{ //Si era un número o variable...
                if(isdigit(*p)){ //Si era número...
                    char chrtint[10];
                    //Ciclo que guarda el coeficiente en coef.
                    k = 0;
                    while(isdigit(*p)){
                        chrtint[k++] = *p;
                        p++;
                    }
                    chrtint[k] = '\0';
                    sscanf(chrtint, "%d", &terms_temp[j].coeficiente);
                    if(!(isdigit(*p))){
                        p--;
                    }
                }else{ //Empiezan las variables y exponentes.
                    if(isalpha(*p)){
                        terms_temp[j].variable = *p;
                    }else if(*p == '^'){    
                        char chrtint[10];
                        p++;
                        k = 0;
                        if(*p == '-'){
                            bool_exp = 1;
                            p++;
                        }while(isdigit(*p)){
                            chrtint[k++] = *p;
                            p++;
                        }
                        chrtint[k] = '\0';
                        sscanf(chrtint, "%d", &terms_temp[j].grado);
                        if(bool_exp){
                            terms_temp[j].grado *= -1;
                            bool_exp = 0;
                        }
                    }
                }
            }
        }
    }
    return j;
}
