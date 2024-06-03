#pragma once
#include <stdlib.h>

typedef struct Auto
{
    int year;
    char modelo[25];
    int cilindrosMotor;

} Auto;

typedef struct Nodo
{
    Auto *nodoInformacion;
    struct Nodo *siguiente;

} Nodo;

void imprimirNodos(Nodo *inicioDeLista);
Nodo *inicializarNodo(int year, char *modelo, int engine);
void insertarNodoEnLista(Nodo **inicioDeLista, int year, char *modelo, int engine);
void liberarMemoriaNodos(Nodo **inicio_lista);
void ordenarListaPorYear(Nodo **inicio_lista, char orden);
void ordenarListaPorCilindros(Nodo **inicio_lista, char orden);