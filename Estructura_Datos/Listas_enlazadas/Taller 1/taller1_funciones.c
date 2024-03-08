#include "taller1_headers.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void imprimirNodos(Nodo *inicioDeLista)
{
    Nodo *actual = inicioDeLista;

    if (actual == NULL)
    {
        printf("Lista vacia.\n");
        return;
    }

    while (actual != NULL)
    {
        printf("Dato: %d", actual->dato);
        actual = actual->siguiente;

        if (actual != NULL)
        printf(" -> ");
    }
    
    return;
}

Nodo *inicializarNodo(int dato)
{
    Nodo *nuevoNodo = malloc(sizeof(Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;

    return nuevoNodo;
}

void insertarNodoEnLista(Nodo **inicioDeLista, int dato)
{
    // si la lista esta vacia no es necesario recorrer nada
    if (*inicioDeLista == NULL)
    {
        *inicioDeLista = inicializarNodo(dato);
        return;
    }

    // nodo auxiliar para encontrar el ultimo nodo
    Nodo *actual = *inicioDeLista;

    // nodo que se insertara
    Nodo *nuevo = inicializarNodo(dato);

    while (actual->siguiente != NULL)
    {
        actual = actual->siguiente;
    }

    actual->siguiente = nuevo;

    return;
}

void liberarMemoriaNodos(Nodo **inicio_lista)
{
    Nodo *actual = *inicio_lista;
    Nodo *siguiente;

    while (actual != NULL)
    {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    return;
}

void ordenarListaAscendente(Nodo **inicio_lista)
{
    // si la lista esta vacia, salimos sin hacer nada
    if (*inicio_lista == NULL)
    return;

    bool cambiados;
    Nodo *auxiliar;
    Nodo *ultimo = NULL;

    do
    {
        cambiados = false;
        auxiliar = *inicio_lista;

        while (auxiliar->siguiente != ultimo)
        {
            if (auxiliar->dato > auxiliar->siguiente->dato)
            {
                int temporal = auxiliar->dato;
                auxiliar->dato = auxiliar->siguiente->dato;
                auxiliar->siguiente->dato = temporal;
                cambiados = true;
            }

            auxiliar = auxiliar->siguiente;

        }
        
        ultimo = auxiliar;

    } while (cambiados);
    
    return;
}

void eliminarNodoEnLista(Nodo **inicioDeLista, int datoAEliminar)
{
    if (*inicioDeLista == NULL)
    {
        printf("La lista esta vacia, no hay nodos para eliminar.");
        return;
    }

    Nodo *actual = *inicioDeLista;
    Nodo *anterior = NULL;

    while (actual != NULL && actual->dato != datoAEliminar)
    {
        // variable para verificar si el nodo a eliminar es el primero de la lista
        anterior = actual; 
        actual = actual->siguiente;
    }

    // si se llevo al final de la lista y no se encontro el dato
    if (actual == NULL)
    {
        printf("No se encontro el dato a eliminar/\n");
        return;
    }

    // si el nodo a eliminar es el primero de la lista=
    if (anterior == NULL)
    {
        *inicioDeLista = actual->siguiente;

    }else{
        anterior->siguiente = actual->siguiente;
        free(actual);
    }

    return;
}