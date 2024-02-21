#pragma once

typedef struct Nodo
{
    int dato;
    struct Nodo *siguiente;
    struct Nodo *anterior;

} Nodo;

typedef struct ListaDobEnlace
{
    Nodo *inicio;
    Nodo *fin;
    int numeroNodos;

} ListaDobEnlace;

void recorrerNodos(ListaDobEnlace *lista);
void inicializarNodo(Nodo **nodo, int dato);
void insertarNodoPosicion(ListaDobEnlace *lista, int dato, int posicion);
void liberarMemoriaLista(ListaDobEnlace *lista);