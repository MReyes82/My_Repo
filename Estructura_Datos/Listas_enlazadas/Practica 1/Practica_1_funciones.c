#include "practica_1_header.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
        printf("Año: %d\n", actual->nodoInformacion->year);
        printf("Modelo: %s\n", actual->nodoInformacion->modelo);
        printf("Cilindros: %d\n", actual->nodoInformacion->cilindrosMotor);

        actual = actual->siguiente;

        if (actual != NULL)
        printf("------------------\n");
    }
    
    return;
}

Nodo *inicializarNodo(int year, char *modelo, int engine)
{
    Nodo *nuevoNodo = malloc(sizeof(Nodo));
    nuevoNodo->nodoInformacion = malloc(sizeof(Auto));

    nuevoNodo->nodoInformacion->year = year;
    strcpy(nuevoNodo->nodoInformacion->modelo, modelo);
    nuevoNodo->nodoInformacion->cilindrosMotor = engine;

    return nuevoNodo;
}

void insertarNodoEnLista(Nodo **inicioDeLista, int year, char *modelo, int engine)
{
    // si la lista esta vacia no es necesario recorrer nada
    if (*inicioDeLista == NULL)
    {
        *inicioDeLista = inicializarNodo(year, modelo, engine);
        return;
    }

    // nodo auxiliar para encontrar el ultimo nodo
    Nodo *actual = *inicioDeLista;

    // nodo que se insertara
    Nodo *nuevo = inicializarNodo(year, modelo, engine);

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
        free(actual->nodoInformacion);
        free(actual);
        actual = siguiente;
    }

    return;
}

void ordenarListaPorYear(Nodo **inicio_lista, char orden)
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
            Auto *autoActual = auxiliar->nodoInformacion;
            Auto *autoSiguiente = auxiliar->siguiente->nodoInformacion;

            // si se decide ordenar de forma ascedente
            if (orden == '>' && autoActual->year > autoSiguiente->year)
            {
                // Intercambiar los nodos
                auxiliar->nodoInformacion = autoSiguiente;
                auxiliar->siguiente->nodoInformacion = autoActual;
                cambiados = true;
            }

            // si se decide ordenar de forma descendente
            if (orden == '<' && autoActual->year < autoSiguiente->year)
            {
                auxiliar->nodoInformacion = autoSiguiente;
                auxiliar->siguiente->nodoInformacion = autoActual;
                cambiados = true;
            }

            auxiliar = auxiliar->siguiente;
        }

        ultimo = auxiliar;

    } while (cambiados);

    return;
}

void ordenarListaPorCilindros(Nodo **inicio_lista, char orden)
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
            Auto *autoActual = auxiliar->nodoInformacion;
            Auto *autoSiguiente = auxiliar->siguiente->nodoInformacion;

            // si se decide ordenar de forma ascedente
            if (orden == '>' && autoActual->cilindrosMotor > autoSiguiente->cilindrosMotor)
            {
                auxiliar->nodoInformacion = autoSiguiente;
                auxiliar->siguiente->nodoInformacion = autoActual;
                cambiados = true;
            }
            
            // si se decide ordenar de forma descendente
            if (orden == '<' && autoActual->cilindrosMotor < autoSiguiente->cilindrosMotor)
            {
                auxiliar->nodoInformacion = autoSiguiente;
                auxiliar->siguiente->nodoInformacion = autoActual;
                cambiados = true;
            }

            auxiliar = auxiliar->siguiente;
        }

        ultimo = auxiliar;

    } while (cambiados);

    return;
}
