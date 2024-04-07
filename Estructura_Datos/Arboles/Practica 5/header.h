#pragma once

typedef struct Nodo
{
    int valor;
    struct Nodo* izquierda;
    struct Nodo* derecha;

} Nodo;

Nodo* crearNodo(int valor);
void imprimirArbol(Nodo* nodo, int nivel);
Nodo* borrarArbol(Nodo** nodo);
int numElementos(Nodo* nodo);
int calcularAltura(Nodo* arbol);
int compararArboles(Nodo* arbolA, Nodo* arbolB);
int calcularNivel(Nodo* raiz, int valorBusqueda, int nivelActual);
void insertarNodo(Nodo** raizArbol, int valorInsert);
void insertarNodosBalanceados(Nodo** raiz, int* valores, int inicio, int fin);
void llenarArbolBalanceado(Nodo** raiz, int* valores, int n);
int compararEnteros(const void* a, const void* b);