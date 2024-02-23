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
            printf("%p <- Anterior || ", (void *) actual->anterior);
        }
        else{
            printf("null\t\t<-Anterior || ");
        }

        printf("Direccion: %p - ", (void *) actual);
        printf("Dato: %d || ", actual->dato);

        if (actual->siguiente != NULL)
        {
            printf("Siguiente -> %p", (void *) actual->siguiente);
        }
        else{
            printf("Siguiente -> null");
        }

        actual = actual->siguiente;
    }
    
    return;
}

void inicializarNodo(Nodo **nodo, int dato, int indice)
{
    (*nodo) = malloc(sizeof(Nodo));
    (*nodo)->anterior = NULL;
    (*nodo)->dato = dato;
    (*nodo)->siguiente = NULL;
    (*nodo)->indice = indice;

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
    inicializarNodo(&nuevo, dato, posicion);

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

    Nodo *temp = lista->inicio;
    // actualizamos los indices
    int indice = 0;
    while (temp != NULL)
    {
        temp->indice = indice++;
        temp = temp->siguiente;
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

void eliminarNodoPosicion(ListaDobEnlace *lista, int posicion)
{
    if (lista == NULL)
    {
        printf("Lista vacia.\n");
        return;
    }

    if (posicion < 0 || posicion >= lista->numeroNodos)
    {
        printf("ERROR: posicion no valida.\n");
        return;
    }

    Nodo *actual = lista->inicio; // variable para iterar

    while (actual != NULL)
    {
        if (actual->indice == posicion && actual->indice == 0)
        {// si el nodo a eliminar tiene un nodo anterior
            lista->inicio = actual->siguiente;

            if (lista->inicio != NULL)
            {
                lista->inicio->anterior = NULL;
            }

            free(actual);
            break;
            
        }

        if (actual->indice == posicion && actual->siguiente != NULL)
        {
            actual->siguiente->anterior = actual->anterior;
            if (actual->anterior != NULL)
            {
                actual->anterior->siguiente = actual->siguiente;
            }
            free(actual);
            break;
        }

        if (actual->indice == posicion && actual->anterior != NULL)
        {
            actual->anterior->siguiente = actual->siguiente;
            if (actual->siguiente == NULL)
            {
                lista->fin = actual->anterior;
            }
            free(actual);
            break;
        }

        actual = actual->siguiente;
    }
    
    Nodo *temp = lista->inicio;
    int indice = 0;
    while (temp != NULL)
    {
        temp->indice = indice++;
        temp = temp->siguiente;
    }
    lista->numeroNodos--;

    return;
}

void transferirNodoALista(ListaDobEnlace *fuente, ListaDobEnlace *destino, int posicion)
{
    if (fuente == NULL || destino == NULL)
    {
        printf("ERROR: Lista no inicializada.\n");
        return;
    }

    if (posicion < 0 || posicion > destino->numeroNodos)
    {
        printf("ERROR: Posicion en lista destino no valida.\n");
        return;
    }

    if (fuente->numeroNodos == 0)
    {
        printf("Lista fuente vacia.\n");
        return;
    }

    Nodo *actualFuente = fuente->fin;

    while (actualFuente != NULL)
    {
        Nodo *nuevo;
        inicializarNodo(&nuevo, actualFuente->dato, posicion);

        if (posicion == 0)
        {
            nuevo->siguiente = destino->inicio;

            if (destino->inicio != NULL)
            {
                destino->inicio->anterior = nuevo;
            }

            destino->inicio = nuevo;

            if (destino->numeroNodos == 0)
            {
                destino->fin = nuevo;
            }

        }else{
            Nodo *actualDestino = destino->inicio;

            for (int i = 0 ; i < posicion - 1 ; i++)
            {
                actualDestino = actualDestino->siguiente;
            }

            nuevo->siguiente = actualDestino->siguiente;
            nuevo->anterior = actualDestino;
            actualDestino->siguiente = nuevo;

            if (nuevo->siguiente != NULL)
            {
                nuevo->siguiente->anterior = nuevo;
            }

            if (posicion == destino->numeroNodos)
            {
                destino->fin = nuevo;
            }
        }

        fuente->numeroNodos--;
        destino->numeroNodos++;
        actualFuente = actualFuente->anterior;

    }
    
    liberarMemoriaLista(fuente);
    fuente->inicio = NULL;
    fuente->fin = NULL;
    fuente->numeroNodos = 0;

    return;
}