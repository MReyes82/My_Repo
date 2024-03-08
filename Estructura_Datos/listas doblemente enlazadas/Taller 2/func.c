#include "header.h"
#include <stdlib.h>
#include <stdio.h>

void recorrerNodos(ListaDobEnlace *lista)
{
    Nodo *actual = lista->inicio;

    if (actual == NULL)
    {
        printf("\nLista vacia.\n");
    }

    while (actual != NULL)
    {
        printf("\n");
        if (actual->anterior != NULL)
        {
            printf("%p <- Anterior || ", actual->anterior);
        }
        else{
            printf("null <- Anterior || ");
        }

        printf("Direccion: %p - ", actual);
        printf("Dato: %d || ", actual->dato);

        if (actual->siguiente != NULL)
        {
            printf("Siguiente -> %p", actual->siguiente);
        }
        else{
            printf("Siguiente -> null");
        }

        actual = actual->siguiente;
    }
    
    return;
}

void inicializarNodo(Nodo **nodo, int dato)
{
    (*nodo) = malloc(sizeof(Nodo));
    (*nodo)->anterior = NULL;
    (*nodo)->dato = dato;
    (*nodo)->siguiente = NULL;

    return;
}

void insertarNodoPosicion(ListaDobEnlace *lista, int dato, int posicion)
{
    if (posicion < 0 || posicion > lista->numeroNodos)
    {
        printf("ERROR: Posicion no valida.\n");
        return;
    }

    Nodo *nuevo;
    inicializarNodo(&nuevo, dato);

    // insertar al inicio 
    if (posicion == 0)
    {
        // Establece el siguiente del nuevo nodo como el inicio de la lista
        nuevo->siguiente = lista->inicio;
        
        // Si la lista no está vacía, establece el anterior del inicio como el nuevo nodo
        if (lista->inicio != NULL)
        {
            lista->inicio->anterior = nuevo;

        }
        
        // Establece el inicio de la lista como el nuevo nodo
        lista->inicio = nuevo;

        // Si la lista estaba vacía, también establece el fin como el nuevo nodo
        if (lista->numeroNodos == 0)
        {
            lista->fin = nuevo;
        }

    }
    // Insertar en una posición específica
    else
    {
        // Inicializa un puntero actual que apunta al inicio de la lista
        Nodo *actual = lista->inicio;

        // Avanza hasta la posición anterior a la posición deseada
        for (int i = 0 ; i < posicion - 1 ; i++)
        {
            actual = actual->siguiente;
        }

        // Establece los punteros del nuevo nodo y del nodo actual para insertar el nuevo nodo
        nuevo->siguiente = actual->siguiente;
        nuevo->anterior = actual;
        actual->siguiente = nuevo;

        // Si el nuevo nodo tiene un siguiente, establece el anterior de ese siguiente como el nuevo nodo
        if (nuevo->siguiente != NULL)
        {
            nuevo->siguiente->anterior = nuevo;
        }

        // Si la posición es la última, actualiza el fin de la lista al nuevo nodo
        if (posicion == lista->numeroNodos)
        {
            lista->fin = nuevo;
        }

    }

    lista->numeroNodos++;
    return;
}

void liberarMemoriaLista(ListaDobEnlace *lista)
{
    Nodo *actual = lista->inicio;
    Nodo *siguiente = NULL;

    while (actual != NULL)
    {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    lista->inicio = NULL;
    lista->fin = NULL;
    lista->numeroNodos = 0;

    return;
}