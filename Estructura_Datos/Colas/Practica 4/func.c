#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define null NULL

void desplegarReproduccion(Cola* colaReproduccion)
{
    if (colaReproduccion->actual == null)
    {
        printf("Ninguna <<-- Ninguna -->> Ninguna\n");
        return;
    }

    if (colaReproduccion->actual->anterior != null)
    {
        printf("%s - %s <<-- ", colaReproduccion->actual->anterior->cancion->nombre, colaReproduccion->actual->anterior->cancion->autor);

    }else{

        printf("Ninguna <<-- ");
    }

    printf("%s - %s -->> ", colaReproduccion->actual->cancion->nombre, colaReproduccion->actual->cancion->autor);

    if (colaReproduccion->actual->siguiente != null)
    {
        printf("%s - %s\n", colaReproduccion->actual->siguiente->cancion->nombre, colaReproduccion->actual->siguiente->cancion->autor);

    }else{

        printf("Ninguna\n");
    }

    return;
}

void dequeue(Cola *cola, int posicion)
{
    if (cola->cantidadElementos == 0)
    {
        printf("ERROR:underflow\n");
        return;
    }

    if (posicion < 0 || posicion > cola->cantidadElementos)
    {
        printf("\nERROR:unvalidPOS\n");
        return;
    }

    //printf("%d\n", posicion);
    Elemento* elementoEliminado = null;
    Cancion* cancionOut = null;

    if (posicion == 0)
    {
        elementoEliminado = cola->inicio;
        printf("llega aqui1\n");
        cancionOut = elementoEliminado->cancion;
        printf("llega aqui2\n");
        cola->inicio = cola->inicio->siguiente;
        printf("llega aqui3\n");
        cola->inicio->anterior = cola->final; // aqui tira segmentation fault
        printf("llega aqui4\n");
        cola->final->siguiente = cola->inicio;
        printf("Se completa bloque 1\n");
    }
    else if (posicion == cola->cantidadElementos - 1)
    {
        elementoEliminado = cola->final;
        cancionOut = elementoEliminado->cancion;
        cola->final = cola->final->anterior;
        cola->final->siguiente = cola->inicio;
        cola->inicio->anterior = cola->final;
    }
    else
    {
        Elemento* actual = cola->inicio;
        for (int i = 0 ; i < posicion ; i++) { actual = actual->siguiente; }
        
        elementoEliminado = actual;
        cancionOut = elementoEliminado->cancion;
        actual->anterior->siguiente = actual->siguiente;
        actual->siguiente->anterior = actual->anterior;
    }

    free(elementoEliminado);
    cola->cantidadElementos--;

    if (cola->cantidadElementos == 0)
    {
        cola->actual = null;
        printf("Se completa bloque 2\n");

    }else{
        
        cola->actual = cola->inicio;
    }
    
    printf("\nCancion eliminada: %s\n", cancionOut->nombre);

    return;
}

void enqueue(Cola* cola, Cancion* cancion, int posicion)
{
    if (cola->maxTam > 0 && cola->cantidadElementos == cola->maxTam)
    {
        printf("\nERROR:overflow\n");
        return;
    }

    if (posicion < 0 || posicion > cola->cantidadElementos)
    {
        printf("\nERROR:unvalidPOS\n");
        return;
    }

    Elemento* nuevoElemento = alojarElemento(cancion);

    if (cola->cantidadElementos == 0)
    {
        cola->inicio = nuevoElemento;
        cola->final = nuevoElemento;
        nuevoElemento->siguiente = nuevoElemento;
        nuevoElemento->anterior = nuevoElemento;
    }
    else
    {
        if (posicion == 0)
        {
            nuevoElemento->siguiente = cola->inicio;
            nuevoElemento->anterior = cola->final;
            cola->inicio->anterior = nuevoElemento;
            cola->final->siguiente = nuevoElemento;
            cola->inicio = nuevoElemento;
        }
        else if (posicion == cola->cantidadElementos)
        {
            nuevoElemento->siguiente = cola->inicio;
            nuevoElemento->anterior = cola->final;
            cola->final->siguiente = nuevoElemento;
            cola->inicio->anterior = nuevoElemento;
            cola->final = nuevoElemento;
        }
        else
        {
            Elemento* actual = cola->inicio;
            for (int i = 0 ; i < posicion - 1 ; i++) { actual = actual->siguiente; }

            nuevoElemento->siguiente = actual->siguiente;
            nuevoElemento->anterior = actual;
            actual->siguiente->anterior = nuevoElemento;
            actual->siguiente = nuevoElemento;
        }
    }

    cola->cantidadElementos++;
    cola->actual = cola->inicio;

    return;
}

void inicializarCola(Cola* cola)
{
    cola->inicio = null;
    cola->final = null;
    cola->actual = null;
    cola->maxTam = 0;
    cola->cantidadElementos = 0;
    cola->estaEnBucle = true;
    cola->estaEnPrimIter = true;

    return;
}

Elemento* alojarElemento(Cancion* cancion)
{
    Elemento* nuevo = malloc(sizeof(Elemento));

    nuevo->cancion = cancion;
    nuevo->siguiente = null;
    nuevo->anterior = null;

    return nuevo;
}

void mostrarColaReproduccion(Cola* cola)
{
    if (cola->cantidadElementos == 0)
    {
        return;
    }

    Elemento* actual = cola->inicio;

    int n = 0;
    printf("\n");

    while (n < cola->cantidadElementos)
    {
        printf("%d)%s - %s\n", n, actual->cancion->nombre, actual->cancion->autor);
        n++;

        actual = actual->siguiente;
    }

    return;
}

int mostrarPlaylist(void)
{
    int seleccion;
    printf("\nCanciones disponibles: \n");
    for (int i = 0 ; i < 15 ; i++)
    {
        printf("%d) %s - %s\n", i, playlistOriginal[i].nombre, playlistOriginal[i].autor);
    }

    printf("Elige una cancion\n> ");
    scanf("\n%d", &seleccion);

    return seleccion;
}

void toggleBucle(Cola* cola, int activar)
{
    // si la cola esta vacia, salimos para evitar segmentation fault
    if (cola->cantidadElementos == 0) { return; }

    if (activar)
    {
        cola->inicio->anterior = cola->final;
        cola->final->siguiente = cola->inicio;
        cola->estaEnBucle = true;
        //printf("\nBUCLE ACTIVADO\n"); debug
    }
    else
    {
        cola->inicio->anterior = null;
        cola->final->siguiente = null;
        cola->estaEnBucle = false;
        //printf("\nBUCLE DESACTIVADO\n"); debug
    }
}

bool estaEnModoCircular(Cola* cola)
{
    bool output = cola->inicio->anterior == cola->final && cola->final->siguiente == cola->inicio;

    return (output && cola->cantidadElementos > 0);
}