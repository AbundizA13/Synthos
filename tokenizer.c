#include "nexus.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const char* getTokenType(token_type type){
    switch(type){
        case TOK_EOF: return "TOK_EOF";
        case NUM: return "NUM";
        case VAR: return "VAR";
        case EXP: return "EXP";
        case SUM: return "SUM";
        case RES: return "RES";
        case MULT: return "MULT";
        case DIV: return "DIV";
        case R_PAR: return "R_PAR";
        case L_PAR: return "L_PAR";
        case UNK: return "UNK";
        default: return "?";
    }
}
/*
token createToken(){
    token t;
    memset(&t,0,sizeof(t));
    t.tipo = UNK;
    t.content = NULL;
    return t;
}*/
void freeTokens(token* tList, int total){
    for(int i=0;i<total;i++){ //Por cada uno de los tokens:
        if(tList->content != NULL){
            free(tList->content);
            tList++;
        }else   tList++;
    }
}
int reallocCharPtr(char** ptr, int len, int* cap, int totalTokens, token* tList){ //A = 
    if(len+1>=*cap){
        *cap = *cap == 0 ? 2 : *cap * 2;
        char* tmp = realloc(*ptr,(unsigned int)*cap);
        if(!tmp){
            free(tmp);
            perror("realloc");
            return 0; //
        }
        *ptr = tmp;
    }
    return 1;
}

int getExpressionTokens(char expresion[30], token* tokens_temp){
    char *p = expresion;
    int token_counter = 0; //Contador del espacio en lista de tokens.
    while(*p != '\0' && *p != '\n'){
        if(isdigit((unsigned char)*p)){
            //tokens_temp[token_counter].content = NULL;
            int len=0, cap=0;
            while(isdigit((unsigned char)*p)){
                if(!(reallocCharPtr(&(tokens_temp[token_counter].content),len,&cap,token_counter,tokens_temp))) return -1;
                tokens_temp[token_counter].content[len++] = *p;
                p++;
            }
            tokens_temp[token_counter].content[len] = '\0';
            tokens_temp[token_counter].tipo = NUM;
            token_counter++;
            continue;

            /*
            char* start = p;
            while(isdigit(*p)){
                p++;
            }
            int lenght = p - start;
            strncpy(tokens_temp[token_counter].content,start,lenght);
            tokens_temp[token_counter].content[lenght] = '\0';
            tokens_temp[token_counter++].tipo = NUM;
            continue;*/
        }else if(isalpha((unsigned char)*p)){
            tokens_temp[token_counter].content = realloc(tokens_temp[token_counter].content,2);
            tokens_temp[token_counter].content[0] = *p;
            tokens_temp[token_counter].content[1] = '\0';
            tokens_temp[token_counter++].tipo = VAR;
            p++;
            continue;
        }else if(isspace((unsigned char)*p)){
            p++;
            continue;
        }else if(*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '^'){
            if(*p == '+'){
                tokens_temp[token_counter].content = realloc(tokens_temp[token_counter].content,2);
                tokens_temp[token_counter].content[0] = *p;
                tokens_temp[token_counter].content[1] = '\0';
                tokens_temp[token_counter++].tipo = SUM;
                /*
                tokens_temp[token_counter].content[0] = *p;
                tokens_temp[token_counter].content[1] = '\0';
                tokens_temp[token_counter++].tipo = SUM;
                */
            }else if(*p == '-'){
                tokens_temp[token_counter].content = realloc(tokens_temp[token_counter].content,2);
                tokens_temp[token_counter].content[0] = *p;
                tokens_temp[token_counter].content[1] = '\0';
                tokens_temp[token_counter++].tipo = RES;
            }else if(*p == '*'){
                tokens_temp[token_counter].content = realloc(tokens_temp[token_counter].content,2);
                tokens_temp[token_counter].content[0] = *p;
                tokens_temp[token_counter].content[1] = '\0';
                tokens_temp[token_counter++].tipo = MULT;
            }else if(*p == '/'){
                tokens_temp[token_counter].content = realloc(tokens_temp[token_counter].content,2);
                tokens_temp[token_counter].content[0] = *p;
                tokens_temp[token_counter].content[1] = '\0';
                tokens_temp[token_counter++].tipo = DIV;
            }else{
                tokens_temp[token_counter].content = realloc(tokens_temp[token_counter].content,2);
                tokens_temp[token_counter].content[0] = *p;
                tokens_temp[token_counter].content[1] = '\0';
                tokens_temp[token_counter++].tipo = EXP;
            }
            p++;
        }else if(*p == '('){
                tokens_temp[token_counter].content = realloc(tokens_temp[token_counter].content,2);
                tokens_temp[token_counter].content[0] = *p;
                tokens_temp[token_counter].content[1] = '\0';
                tokens_temp[token_counter++].tipo = L_PAR;
                p++;
        }else if(*p == ')'){
                tokens_temp[token_counter].content = realloc(tokens_temp[token_counter].content,2);
                tokens_temp[token_counter].content[0] = *p;
                tokens_temp[token_counter].content[1] = '\0';
                tokens_temp[token_counter++].tipo = R_PAR;
                p++;
            
        }else{
            p++;
        }
    }
    tokens_temp[token_counter].tipo = TOK_EOF;
    return token_counter;
    
    
}