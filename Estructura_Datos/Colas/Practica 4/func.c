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

Cancion* dequeue(Cola *cola, int posicion)
{
    if (cola->cantidadElementos == 0)
    {
        printf("ERROR:underflow\n");
        return null;
    }

    if (posicion < 0 || posicion > cola->cantidadElementos)
    {
        printf("\nERROR:unvalidPOS\n");
        return null;
    }

    Elemento* elementoEliminado = null;
    Cancion* cancionOut = null;

    if (posicion == 0)
    {
        elementoEliminado = cola->inicio;
        cancionOut = elementoEliminado->cancion;
        cola->inicio = cola->inicio->siguiente;
        cola->inicio->anterior = cola->final;
        cola->final->siguiente = cola->inicio;
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
        //printf("Se elimina.\n");
    }

    free(elementoEliminado);
    cola->cantidadElementos--;

    if (cola->cantidadElementos == 0)
    {
        cola->actual = null;

    }else{
        
        cola->actual = cola->inicio;
    }

    //bool aux = _estaEnBucle_(cola);

    //if (!(estaEnBucle && aux)) { toggleBucle(cola); }
    
    return cancionOut;
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
            for (int i = 0 ; i < posicion - 1; i++) { actual = actual->siguiente; }

            nuevoElemento->siguiente = actual->siguiente;
            nuevoElemento->anterior = actual;
            actual->siguiente->anterior = nuevoElemento;
            actual->siguiente = nuevoElemento;
        }
    }

    cola->cantidadElementos++;
    cola->actual = cola->inicio;

    //bool aux = _estaEnBucle_(cola);

    //if (!(estaEnBucle && cola->cantidadElementos > 0 && aux)) { toggleBucle(cola); }

    return;
}

void inicializarCola(Cola* cola, int tam)
{
    cola->inicio = null;
    cola->final = null;
    cola->actual = null;

    cola->maxTam = tam;
    cola->cantidadElementos = 0;

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
        printf("%d) %s - %s\n", n, actual->cancion->nombre, actual->cancion->autor);
        n++;

        actual = actual->siguiente;
    }

    return;
}

int mostrarPlaylist(void)
{
    int seleccion;
    printf("\nCanciones disponibles: \n");
    for (int i = 0 ; i < MAX_SIZE ; i++)
    {
        printf("%d) %s - %s\n", i, playlistOriginal[i].nombre, playlistOriginal[i].autor);
    }

    printf("Elige una cancion\n> ");
    scanf("\n%d", &seleccion);

    return seleccion;
}

void toggleBucle(Cola* cola)
{
    if (cola->inicio->anterior == cola->final && cola->final->siguiente == cola->inicio)
    {
        cola->inicio->anterior = null;
        cola->final->siguiente = null;
        printf("\nBUCLE DESACTIVADO\n");
    }
    else
    {
        cola->inicio->anterior = cola->final;
        cola->final->siguiente = cola->inicio;
        printf("\nBUCLE ACTIVADO\n");
    }

    return;
}

bool _estaEnBucle_(Cola* cola)
{
    // regresa 1 si esta en bucle
    // 0 si no
    return (cola->inicio->anterior == cola->final && cola->final->siguiente == cola->inicio);
}