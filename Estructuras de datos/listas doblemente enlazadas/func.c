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
        nuevo->siguiente = lista->inicio;
        
        if (lista->inicio != NULL)
        {
            lista->inicio->anterior = nuevo;

        }
        
        lista->inicio = nuevo;

        if (lista->numeroNodos == 0)
        {
            lista->fin = nuevo;
        }

    }

    else
    {
        Nodo *actual = lista->inicio;

        for (int i = 0 ; i < posicion - 1 ; i++)
        {
            actual = actual->siguiente;
        }

        nuevo->siguiente = actual->siguiente;
        nuevo->anterior = actual;
        actual->siguiente = nuevo;

        if (nuevo->siguiente != NULL)
        {
            nuevo->siguiente->anterior = nuevo;
        }

        if (posicion == lista->numeroNodos)
        {
            lista->fin = nuevo;
        }

    }

    lista->numeroNodos++;
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