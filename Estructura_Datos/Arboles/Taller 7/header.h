#pragma once

#define null NULL

typedef struct Nodo
{
    struct Nodo* izquierda;
    char valor; // un solo byte para el arbol de expresion
    struct Nodo* derecha;

} Nodo;

Nodo* crearNodo(char valor);
void imprimirArbol(Nodo* nodo, int nivel);
Nodo* borrarArbol(Nodo** nodo);
Nodo* insertarNodo(Nodo* raiz, char valor);
int esOperador(char valor);
void recorridoPreOrden(Nodo* raiz);
void recorridoEnOrden(Nodo* raiz);
void recorridoPostOrden(Nodo* raiz);
void printNL(void);