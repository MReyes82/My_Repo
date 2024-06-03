#pragma once
//#include <stdlib.h>

typedef struct Nodo
{
    int dato;
    struct Nodo *siguiente;

} Nodo;

// prototipos
void imprimirNodos(Nodo *inicioDeLista);
Nodo *inicializarNodo(int dato);
void insertarNodoEnLista(Nodo **inicioDeLista, int dato);
void liberarMemoriaNodos(Nodo **inicio_lista);
void ordenarListaAscendente(Nodo **inicio_lista);
// ejercicios practica examen 1
void eliminarNodoEnLista(Nodo **inicioDeLista, int datoAEliminar);


