#include "header.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int llena(Queue cola) { return (cola.length > 0 && cola.numeroElementos == cola.length); }

int vacia(Queue cola) { return (cola.numeroElementos == 0); }

Elemento* alojarElemento(Cancion *elemento)
{
    Elemento *nuevo = malloc(sizeof(Elemento));
    nuevo->anterior = NULL;
    nuevo->cancion = elemento;
    nuevo->siguiente = NULL;

    return nuevo;
}

//void enqueue(Queue* cola, int datoAInsertar); // poner
//Elemento* dequeue(Queue* colan); // quitar

void insertarPosicion(Queue* cola, Cancion* datoAInsertar, int posicion)
{
    if (posicion < 0 || posicion > cola->numeroElementos)
    {
        printf("ERROR:posNoValida\n");
        return;

    }else if(llena(*cola)){
        printf("Queue overflow\n");
        return;
    }

    Elemento *nuevo = alojarElemento(datoAInsertar);

    if (posicion == 0)
    {
        if (cola->numeroElementos == 0)
        {
            // pending
        }
    }

    else
    {
        /* code */
    }
    

    cola->numeroElementos++;

    return;
}

void eliminarPosicion(Queue* cola, int posicion)
{
    if (posicion < 0 || posicion >= cola->numeroElementos) {
        printf("ERROR: Posicion no valida\n");
        return;
    }

    Elemento* eliminar = NULL;

    if (posicion == 0) 
    {
        eliminar = cola->inicio;
        cola->inicio = cola->inicio->siguiente;

        if (cola->inicio == NULL) 
        {
            cola->final = NULL;

        } else {

            cola->inicio->anterior = NULL;
        }
    } 
    else {
        Elemento* actual = cola->inicio;

        for (int i = 0; i < posicion - 1; i++) 
        {
            actual = actual->siguiente;
        }

        eliminar = actual->siguiente;
        actual->siguiente = eliminar->siguiente;

        if (eliminar->siguiente == NULL) 
        {
            cola->final = actual;

        } else {

            eliminar->siguiente->anterior = actual;
        }
    }

    free(eliminar);
    cola->numeroElementos--;

}

void desplegarReproduccion(Queue* cola)
{
    if (vacia(*cola))
    {
        printf(" Ninguna <<-- Ninguna -->> Ninguna");
        return;
    }

    if (cola->actual->anterior != NULL)
    {
        printf("%s <<--", cola->actual->anterior->cancion->nombre);
    }

    else
    {
        printf("Ninguna <<--");
    }

    printf(" %s ", cola->actual->cancion->nombre);

    if (cola->actual->siguiente != NULL)
    {
        printf("-->> %s", cola->actual->siguiente->cancion->nombre);
    }
    else
    {
        printf("-->> Ninguna");
    }

    //printf("\n");
    return;

}

Queue initQueue(int length)
{
    Queue nueva;

    nueva.inicio = NULL;
    nueva.final = NULL;
    nueva.actual = NULL;
    nueva.length = length;
    nueva.numeroElementos = 0;
    nueva.posicionActual = 0;

    return nueva;
}

int printStaticQueue()
{
    int i, seleccion;
    for (i = 0 ; i < 15 ; i++)
    {
        printf("%d) %s by: %s\n", i, listaPredefinina[i].nombre, listaPredefinina[i].autor);
    }

    printf("¿Que cancion quieres agregar?\n> ");
    scanf("\n%d", &seleccion);

    return seleccion;
}

void printQueue(Queue* cola)
{
    if (vacia(*cola))
    {
        printf("Cola vacia.\n");
        return;
    }

   Elemento *actual = cola->final;
   int n;

   while (actual != NULL)
   {
        printf("%d) %s - %s \n", n, actual->cancion->nombre, actual->cancion->autor);
        actual = actual->anterior;
        n++;
   }
    printf("\n");

    return;
}