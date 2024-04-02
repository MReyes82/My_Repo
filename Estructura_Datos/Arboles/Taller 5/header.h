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
int contarElementos(Nodo* nodo);
int calcularAltura(Nodo* arbol);
int compararArboles(Nodo* arbolA, Nodo* arbolB);