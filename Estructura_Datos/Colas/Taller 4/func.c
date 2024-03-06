#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#define NOLIMIT 0

int llena(Queue cola)
{   
    /* 
    esta llena si la longitud es mayor a 0 y el numero de elementos 
    es igual a la longitud, esto ya que si la longitud no es mayor
    a 0, quiere decir que no tiene limite la cola
    */
    return (cola.length > 0 && cola.numeroElementos == cola.length);
}

int vacia(Queue cola)
{
    return (cola.numeroElementos == 0);
}

Elemento* alojarElemento(int dato)//, int indice)
{
    Elemento *nuevo = malloc(sizeof(Elemento));
    nuevo->anterior = NULL;
    nuevo->dato = dato;
    nuevo->siguiente = NULL;
    //nuevo->indice = indice;

    return nuevo;
}

void enqueue(Queue* cola, int datoAInsertar)
{
    if (llena(*cola))
    {
        printf("Queue overflow\n");
        return;
    }

    Elemento *nuevo = alojarElemento(datoAInsertar);

    if (vacia(*cola)) // si es el primer elemento
    {
        cola->inicio = nuevo;
        cola->final = nuevo;
    }
    else
    {
        nuevo->siguiente = cola->inicio;
        cola->inicio->anterior = nuevo;
        cola->inicio = nuevo;
    }

    cola->numeroElementos++;
}

Elemento* dequeue(Queue* cola)
{
    if (vacia(*cola))
    {
        printf("Queue underflow\n");
        return NULL;
    }

    Elemento *elementoOutput = cola->final;

    // si el elemento borrado es el unico en la cola
    if (cola->numeroElementos == 1)
    {
        cola->inicio = NULL;
        cola->final = NULL;
    }

    else
    {
        cola->final = elementoOutput->anterior;
        cola->final->siguiente = NULL;
    }

    cola->numeroElementos--;

    return elementoOutput;
}   

void insertarPosicion(Queue* cola, int datoAInsertar, int posicion)
{
    if (posicion < 0 || posicion > cola->numeroElementos)
    {
        printf("ERROR:posNoValidaa\n");
        return;

    }else if(!llena(*cola)){
        printf("Queue overflow\n");
        return;
    }

    Elemento *nuevo = alojarElemento(datoAInsertar);//, posicion);

    if (posicion == 0)
    {
        nuevo->siguiente = cola->inicio;

        if (cola->inicio != NULL)
        {
            cola->inicio->anterior = nuevo;
        }

        cola->inicio = nuevo;

        if (cola->numeroElementos == 0)
        {
            cola->final = nuevo;
        }
    }

    else
    {
        Elemento *actual = cola->inicio;

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

        if (posicion == cola->numeroElementos)
        {
            cola->final = nuevo;
        }
    }

    cola->numeroElementos++;

    return;
}

/*
void printQueue(Queue *cola)
{
    Elemento *actual = cola->inicio;

    if (actual == NULL);
    {
        printf("\nCola vacia.\n");
        //return;
    }

    while (actual != NULL)
    {
        printf("\n");

        if (actual->anterior == NULL)
        {
            printf("null\t\t<-Anterior ||");

        } else{ 
            printf("{%d} <- Anterior || ", actual->anterior->dato);
        }

        printf("Dato: [%d] || ", actual->dato);

        if (actual->siguiente == NULL)
        {
            printf("Siguiente -> null");

        } else{
            print("Siguiente -> {%d}", actual->siguiente->dato);
        }

        actual = actual->siguiente;
    }

    return;
}
*/
void printQueue(Queue* cola)
{
    if (vacia(*cola))
    {
        printf("Queue underflow\n");
        return;
    }

    Elemento *actual = cola->inicio;

    while (actual != NULL)
    {
        printf("| %d |\n", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");

    return;
}

Queue initQueue(int length)
{
    Queue nuevo;

    nuevo.inicio = NULL;
    nuevo.final = NULL;
    nuevo.numeroElementos = 0;
    nuevo.length = length;

    return nuevo;
}