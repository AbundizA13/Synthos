#include "nexus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*1. Funciones recursivas
  1.1. Crea un Token Node en el primer token
  1.2. Funciones prsExpression, prsFactor, prsTerm y prsPrimary
  1.3. Token_Node node = prsExpression() -> donde prsExpression es una función recursiva.
  1.4. Funciones sigTokenType 

  Funcionamiento del Algoritmo Recursivo Constructor de Árboles de Nodos. "ARCAN"
  - Obtiene una lista de tokens.
  - Lee el primer token, y lo procesa con la función recursiva de mayor rango.
  - Baja por la jerarquía de funciones hasta que encuentra la de su tipo de token.

 >>==============================================<<
 ||   ___     ____       ___     ___     __  __  ||
 ||  // \\    || \\     //      // \\    ||\ ||  ||
 ||  ||=||    ||_//    ((       ||=||    ||\\||  ||
 ||  || ||    || \\     \\__    || ||    || \||  ||
 ||                                              ||
 >>==============================================<<
*/
void freeTree(Token_Node* node){
  if(node == NULL) return;
  freeTree(node->right);
  freeTree(node->left);
  free(node);
}

int isPrimary(token token){
  if(token.tipo == NUM || token.tipo == VAR) return 1;
  else return 0;
}
void nextToken(token **tokens){
  (*tokens)++;
}
void bindChildren(Token_Node* father){
  if(father->left != NULL){
    father->left->father = father;
  }
  if(father->right != NULL){
    father->right->father = father;
  }
}
void printTree(Token_Node* node){
  if(node == NULL) return;
  // Si es un nodo primario (NUM o VAR), imprime directamente
  if(isPrimary(node->token)){
    printf("%s",node->token.content);
    return;
  }
  // Si es un operador, imprime: (izq OP der)
  printf("(");
  printTree(node->left);
  // Imprime el operador según su tipo
  switch(node->token.tipo){
    case SUM:
      printf(" + ");
      break;
    case RES:
      printf(" - ");
      break;
    case MULT:
      printf(" * ");
      break;
    case DIV:
      printf(" / ");
      break;
    default:
      printf(" ? ");
  }
  printTree(node->right);
  printf(")");
}

token createOpToken(char operator){
  token t;
  memset(&t,0,sizeof(t));
  //t.content[0] = operator;
  //t.content[1] = '\0';
  t.content = NULL;
  switch(operator){
    case '+':
      t.tipo = SUM;
      break;
    case '-':
      t.tipo = RES;
      break;
    case '*':
      t.tipo = MULT;
      break;
    case '/':
      t.tipo = DIV;
      break;
    case '^':
      t.tipo = EXP;
      break;
    case '(':
      t.tipo = L_PAR;
      break;
    case ')':
      t.tipo = R_PAR;
      break;
    case '\0':
      t.tipo = TOK_EOF;
      break;
  }
  return t;
}

Token_Node* parseF(token** tokens){
  if(isPrimary(**tokens)){
    Token_Node* newNode = malloc(sizeof(Token_Node));
    newNode->father = NULL;
    newNode->token = **tokens;
    newNode->left = NULL;
    newNode->right = NULL;
    nextToken(tokens);
    return newNode;
  }else{
    printf("Unknown token in parseF(); '%s'",getTokenType((**tokens).tipo));
    return NULL;
  }
}

Token_Node* parseT(token** tokens){
  Token_Node* a = parseF(tokens);
  if(a == NULL) return NULL;
  while(1){
    if((**tokens).tipo == MULT){
      token op = **tokens;
      nextToken(tokens);
      Token_Node* b = parseF(tokens);
      if(b == NULL){
        freeTree(a);
        return NULL;
      }
      Token_Node* c = malloc(sizeof(Token_Node));
      if(c == NULL){
        freeTree(a);
        freeTree(b);
        return NULL;
      }
      c->father = NULL;
      c->token = op;
      c->left = a;
      c->right = b;
      bindChildren(c);
      a = c;
    }else if((**tokens).tipo == DIV){
      token op = **tokens;
      nextToken(tokens);
      Token_Node* b = parseF(tokens);
      if(b == NULL){
        freeTree(a);
        return NULL;
      }
      Token_Node* c = malloc(sizeof(Token_Node));
      if(c == NULL){
        freeTree(a);
        freeTree(b);
        return NULL;
      }
      c->father = NULL;
      c->token = op;
      c->left = a;
      c->right = b;
      bindChildren(c);
      a = c;
    }else if(isPrimary(**tokens)){
      Token_Node* b = parseF(tokens);
      if(b == NULL){
        freeTree(a);
        return NULL;
      }
      Token_Node* c = malloc(sizeof(Token_Node));
      if(c == NULL){
        freeTree(a);
        freeTree(b);
        return NULL;
      }
      c->father = NULL;
      c->token = createOpToken('*');
      c->left = a;
      c->right = b;
      bindChildren(c);
      a = c;
    }else return a;
  }
}       // 1 + 5y

Token_Node* parseE(token** tokens){ 
  Token_Node* a = parseT(tokens); //Se consume primer token e índice aumenta
  if(a == NULL) return NULL;
  while((**tokens).tipo != TOK_EOF){  
    if((**tokens).tipo == SUM){ //Mirando si el próximo token es suma 
      token op = **tokens;
      nextToken(tokens);
      Token_Node* b = parseT(tokens);
      if(b == NULL){
        freeTree(a);
        return NULL;
      }
      Token_Node* c = malloc(sizeof(Token_Node));
      if(c == NULL){
        freeTree(a);
        freeTree(b);
        return NULL;
      }
      c->father = NULL;
      c->token = op;
      c->left = a;
      c->right = b;
      bindChildren(c);
      a = c;
    }else if((**tokens).tipo == RES){
      token op = **tokens;
      nextToken(tokens);
      Token_Node* b = parseT(tokens);
      if(b == NULL){
        freeTree(a);
        return NULL;
      }
      Token_Node* c = malloc(sizeof(Token_Node));
      if(c == NULL){
        freeTree(a);
        freeTree(b);
        return NULL;
      }
      c->father = NULL;
      c->token = op;
      c->left = a;
      c->right = b;
      bindChildren(c);
      a = c;
    }else{
      return a;
    }
  }
  return a;
}