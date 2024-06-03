#pragma once

#define null NULL

typedef struct Nodo
{
    struct Nodo* izquierda;
    char valor; // un solo byte para el arbol de expresion
    int indice;
    struct Nodo* derecha;

} Nodo;

Nodo* crearNodo(char valor, int indice);
void imprimirArbol(Nodo* nodo, int nivel);
Nodo* construirArbol(const char* expresion);
Nodo* borrarArbol(Nodo** nodo);
int esOperador(char valor);
void recorridoEnOrden(Nodo* raiz);
void obtenerIndices(Nodo* raiz, int* contador, int** arrayIndices);
void printArray(int* arr, int len);
void printNL(void);