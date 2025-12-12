#include "nexus.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const char* getTokenType(token_type type){
    switch(type){
        case EOF: return "EOF";
        case NUM: return "NUM";
        case VAR: return "VAR";
        case EXP: return "EXP";
        case SUM: return "SUM";
        case RES: return "RES";
        case MULT: return "MULT";
        case DIV: return "DIV";
        case R_PAR: return "R_PAR";
        case L_PAR: return "L_PAR";
        case DOT: return "DOT";
        default: return "?";
    }
}

int getExpressionTokens(char expresion[30], token* tokens_temp){
    char *p = expresion;
    int token_counter = 0; //Contador del espacio en lista de tokens.
    while(*p != '\0' && *p != '\n'){
        if(*p == '.'){
            tokens_temp[token_counter].content[0] = *p;
            tokens_temp[token_counter].content[1] = '\0';
            tokens_temp[token_counter++].tipo = DOT;
            p++;
            continue;
        }else if(isdigit(*p)){
            char* start = p;
            while(isdigit(*p)){
                p++;
            }
            int lenght = p - start;
            strncpy(tokens_temp[token_counter].content,start,lenght);
            tokens_temp[token_counter].content[lenght] = '\0';
            tokens_temp[token_counter++].tipo = NUM;
            continue;
        }else if(isalpha(*p)){
            tokens_temp[token_counter].content[0] = *p;
            tokens_temp[token_counter].content[1] = '\0';
            tokens_temp[token_counter++].tipo = VAR;
            p++;
            continue;
        }else if(isspace(*p)){
            p++;
            continue;
        }else if(*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '^'){
            if(*p == '+'){
                tokens_temp[token_counter].content[0] = *p;
                tokens_temp[token_counter].content[1] = '\0';
                tokens_temp[token_counter++].tipo = SUM;
            }else if(*p == '-'){
                tokens_temp[token_counter].content[0] = *p;
                tokens_temp[token_counter].content[1] = '\0';
                tokens_temp[token_counter++].tipo = RES;
            }else if(*p == '*'){
                tokens_temp[token_counter].content[0] = *p;
                tokens_temp[token_counter].content[1] = '\0';
                tokens_temp[token_counter++].tipo = MULT;
            }else if(*p == '/'){
                tokens_temp[token_counter].content[0] = *p;
                tokens_temp[token_counter].content[1] = '\0';
                tokens_temp[token_counter++].tipo = DIV;
            }else{
                tokens_temp[token_counter].content[0] = *p;
                tokens_temp[token_counter].content[1] = '\0';
                tokens_temp[token_counter++].tipo = EXP;
            }
            p++;
        }else if(*p == '('){
                tokens_temp[token_counter].content[0] = *p;
                tokens_temp[token_counter].content[1] = '\0';
                tokens_temp[token_counter++].tipo = L_PAR;
                p++;
        }else if(*p == ')'){
                tokens_temp[token_counter].content[0] = *p;
                tokens_temp[token_counter].content[1] = '\0';
                tokens_temp[token_counter++].tipo = R_PAR;
                p++;
            
        }else{
            p++;
        }
    }
    tokens_temp[token_counter].tipo = EOF;
    return token_counter;
    
    
}