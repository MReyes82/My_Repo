#pragma once

typedef struct Nodo
{
    int dato;
    struct Nodo *siguiente;
    struct Nodo *anterior;
    int indice;

} Nodo;

typedef struct ListaDobEnlace
{
    Nodo *inicio;
    Nodo *fin;
    int numeroNodos;

} ListaDobEnlace;

void recorrerNodos(ListaDobEnlace *lista);
void inicializarNodo(Nodo **nodo, int dato, int indice);
void insertarNodoPosicion(ListaDobEnlace *lista, int dato, int posicion);
void liberarMemoriaLista(ListaDobEnlace *lista);
void eliminarNodoPosicion(ListaDobEnlace *lista, int posicion);
void transferirNodoALista(ListaDobEnlace *fuente, ListaDobEnlace *destino, int posicion);