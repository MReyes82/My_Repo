#pragma once
#include <stdbool.h>

#define null NULL

typedef struct Nodo
{
    char valor;
    short int index;
    struct Nodo* izquierda;
    struct Nodo* derecha;

} Nodo;

typedef struct nodoST
{
    char valor;
    struct nodoST* siguiente;
} NodoST;


typedef struct Stack
{
    NodoST* cima;
    int cantidadNodos;
    int maxTam;

} Stack;

Nodo* crearNodo(char valor, int index);
void insertarNodo(Nodo** raiz, char valor, int index);
void imprimirArbol(Nodo* raiz, int nivel);
void borrarArbol(Nodo** raiz);
void imprimirCharNodo(char caracterDelNodo);
void recorridoEnOrden(Nodo* raiz);
// util
void printSpaces(int n);
NodoST* pop(Stack* st);
void push(Stack* st, char valor);
NodoST* initNodo(char valor);
Stack initStack(int maxTam);

void vaciarStack(Stack* st);
bool esValida(char* expresion);
bool esOperador(char ch);

/*
* ( X + Y / A + B * C ^ D )
*   0 1 2 3 4 5 6 7 8 9 10
*
*   orden necesario:
*   5 1 7 0 3 2 4 6 9 8 10
*/
