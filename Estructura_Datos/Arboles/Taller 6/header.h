#pragma once

#define null NULL

typedef struct Nodo
{
    struct Nodo* izquierda;
    int valor;
    struct Nodo* derecha;

} Nodo;

Nodo* crearNodo(int valor);
void imprimirArbol(Nodo* nodo, int nivel);
Nodo* borrarArbol(Nodo** nodo);
Nodo* insertarNodo(Nodo* raiz, int valor);
void recorridoPreOrden(Nodo* raiz);
void recorridoEnOrden(Nodo* raiz);
void recorridoPostOrden(Nodo* raiz);
void printNL(void);
Nodo* invertirArbol(Nodo* raiz);
Nodo* borrarNodo(Nodo* raiz, int valor);
int compararArboles(Nodo* arbolA, Nodo* arbolB);