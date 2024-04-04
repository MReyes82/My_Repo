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
        printf("ERROR: underflow\n");
        return;
    }

    if (posicion < 0 || posicion >= cola->cantidadElementos)
    {
        printf("\nERROR: unvalidPOS\n");
        return;
    }

    Elemento* elementoEliminado = null;
    Cancion* cancionOut = null;

    if (posicion == 0)
    {
        elementoEliminado = cola->inicio;
        cancionOut = elementoEliminado->cancion;

        if (cola->cantidadElementos == 1)
        {
            cola->inicio = null;
            cola->final = null;
        }
        else
        {
            cola->inicio = cola->inicio->siguiente;
            cola->inicio->anterior = cola->final;
            cola->final->siguiente = cola->inicio;
        }
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
        for (int i = 0; i < posicion; i++)
        {
            actual = actual->siguiente;
        }

        elementoEliminado = actual;
        cancionOut = elementoEliminado->cancion;

        actual->anterior->siguiente = actual->siguiente;
        actual->siguiente->anterior = actual->anterior;
    }

    cola->cantidadElementos--;

    if (cola->cantidadElementos == 0)
    {
        cola->actual = null;
    }
    else if (cola->actual == elementoEliminado && cola->cantidadElementos != 0)
    {
        if (cola->actual->siguiente != null) 
        {
            //cola->actual = cola->actual->anterior;
            cola->actual = cola->actual->siguiente;

        }else{
            // cola->actual = cola->actual->siguiente; OPCION B: tiene mismo efecto
            cola->actual = cola->inicio;
        }
    }
    else{
        //representativo, cola->actual se queda igual.
        //cola->actual = cola->actual;
    }

    free(elementoEliminado);
    printf("\nCancion eliminada: %s\n", cancionOut->nombre);
    /*
    if (cola->actual == elementoEliminado && cola->cantidadElementos != 0)
    {
        cola->actual = cola->actual->anterior;

        free(elementoEliminado);
        cola->cantidadElementos--;
        //printf("\nCancion eliminada: %s\n", cancionOut->nombre);
        return;
    }

    
    

    if (cola->cantidadElementos == 0)
    {
        cola->actual = null;
    }
    else
    {
        cola->actual = cola->actual;
    }
    */
    
    //printf("Llega a return statement\n");
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

    if (cola->cantidadElementos == 1) { cola->actual = cola->inicio; }

    else{
        //representativo, {cola->actual} se queda igual.
        //cola->actual = cola->actual; 
    } 

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