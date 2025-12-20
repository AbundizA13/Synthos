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
    if(tList == NULL) return;
    for(int i=0;i<total;i++){ //Por cada uno de los tokens:
        if(tList[i].content != NULL){
            free(tList[i].content);
            tList[i].content = NULL;
        }
    }
    free(tList);
}
int reallocCharPtr(char** ptr, int len, int* cap, int totalTokens, token* tList){ //A =
    (void)totalTokens;
    (void)tList; 
    if(len+1>=*cap){
        *cap = *cap == 0 ? 2 : *cap * 2;
        char* tmp = realloc(*ptr,(unsigned int)*cap);
        if(!tmp){
            perror("realloc char");
            return 0; //
        }
        *ptr = tmp;
    }
    return 1;
}
//Función que añade el token al puntero solo si el puntero a token tiene suficiente capacidad
void storeToken(token t, int* strCap, int strLen, token** tList){
    if(strLen+1>=*strCap){
        *strCap = *strCap == 0 ? 2 : *strCap * 2;
        token* tmp = realloc(*tList,(unsigned int)(*strCap*sizeof(token)));
        if(!tmp){
            perror("realloc token");
        }else{
            *tList = tmp;
            (*tList)[strLen] = t;
        }
    }else{
        (*tList)[strLen] = t;
    }
}

int getExpressionTokens(char expresion[30], token** tokens_temp){
    char *p = expresion;
    int tListLen = 0, tListCap = 0; //Contador del espacio en lista de tokens.
    while(*p != '\0' && *p != '\n'){
        if(isdigit((unsigned char)*p)){
            token tmp;
            tmp.content = NULL;
            int len=0, cap=0;
            while(isdigit((unsigned char)*p)){
                if(!(reallocCharPtr(&tmp.content, len,&cap,tListLen,*tokens_temp))) return -1;
                tmp.content[len++] = *p;
                p++;
            }
            tmp.content[len] = '\0';
            tmp.tipo = NUM;
            storeToken(tmp,&tListCap,tListLen++,tokens_temp);
            continue;
        }else if(isalpha((unsigned char)*p)){
            token tmp;
            tmp.content = malloc(2);
            if(!tmp.content){
                perror("malloc var");
                if(*tokens_temp != NULL) freeTokens(*tokens_temp,tListLen);
                return -1;
            }
            //tmp.content = NULL;
            //realloc(tmp.content, sizeof(char)*2);
            tmp.content[0] = *p;
            tmp.content[1] = '\0';
            tmp.tipo = VAR;
            storeToken(tmp,&tListCap,tListLen++,tokens_temp);
            p++;
            continue;
            /*
            tokens_temp[tListLen].content = NULL;
            tokens_temp[tListLen].content = realloc(tokens_temp[tListLen].content,2);
            tokens_temp[tListLen].content[0] = *p;
            tokens_temp[tListLen].content[1] = '\0';
            tokens_temp[tListLen++].tipo = VAR;
            p++;
            continue;*/
        }else if(isspace((unsigned char)*p)){
            p++;
            continue;
        }else if(*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '^'){
            if(*p == '+'){
                storeToken(createOpToken('+'),&tListCap,tListLen++,tokens_temp);
            }else if(*p == '-'){
                storeToken(createOpToken('-'),&tListCap,tListLen++,tokens_temp);
            }else if(*p == '*'){
                storeToken(createOpToken('*'),&tListCap,tListLen++,tokens_temp);
            }else if(*p == '/'){
                storeToken(createOpToken('/'),&tListCap,tListLen++,tokens_temp);
            }else{
                storeToken(createOpToken('^'),&tListCap,tListLen++,tokens_temp);
            }
            p++;
        }else if(*p == '('){
                storeToken(createOpToken('('),&tListCap,tListLen++,tokens_temp);
                p++;
        }else if(*p == ')'){
                storeToken(createOpToken(')'),&tListCap,tListLen++,tokens_temp);
                p++;
            
        }else{
            p++;
        }
    }
    storeToken(createOpToken('\0'),&tListCap,tListLen,tokens_temp);
    //*tokens_temp[tListLen].tipo = TOK_EOF;
    return tListLen;
    
    
}