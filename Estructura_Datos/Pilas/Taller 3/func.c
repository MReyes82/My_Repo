#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void pop(Stack *fullStack, int *datoAEliminar)
{
    
    if (vacia(fullStack))
    {
        printf("Stack underflow.\n");
        return;
    }

    Nodo *actual = fullStack->top; // asignamos la cima de la pila a un nodo auxiliar
    *datoAEliminar = actual->dato; // asignamos aL apuntador entero el dato que borraremos
    fullStack->top = actual->sig; /* recorremos los nodos asignando el nodo siguiente 
                                   del auxiliar  a la cima de la pila   */ 
    free(actual); // liberamos la memoria del auxiliar (nodo que acabamos de borrra)
    fullStack->length--; // -1 al tamaño de la pila

    return;
}

void push(Stack *fullStack, int datoAIngresar, int numeroNodos)
{
    if (llena(fullStack, numeroNodos))
    {
        printf("Stack overflow.\n");
        return;
    }

    Nodo *nuevo = alojarNodo(datoAIngresar); // alojamos memoria para el nodo que pusheara, 
                                            // con siguiente inicializado en NULL
    nuevo->sig = fullStack->top; // asignamos la cima de la pila al siguiente
    fullStack->top = nuevo; // ahora, asignamos el nuevo nodo a la cima, recorriendo asi a todos los demas nodos
    fullStack->length++;  // + 1 al tamaño de la pial

    return;
}

Nodo *alojarNodo(int dato)
{
    Nodo *nuevo = malloc(sizeof(Nodo));
    nuevo->dato = dato;
    nuevo->sig = NULL;

    return nuevo;
}

void liberarMemoriaPila(Stack *fullStack)
{
    if (vacia(fullStack))
    {
        printf("Pila vacia.\n");
        return;
    }

    Nodo *actual = fullStack->top;
    Nodo *siguiente;

    while (actual != NULL)
    {
        siguiente = actual->sig;
        free(actual);
        actual = siguiente;
    }

    fullStack->top = NULL;
    fullStack->length = 0;

    return;
}

bool vacia(Stack *fullStack)
{   // regresa verdadero si la pila esta vacia
    return (fullStack->top == NULL);
}

bool llena(Stack *fullStack, int numeroNodos)
{   // regresa verdadero si la pila esta llena
    return ((fullStack->length == numeroNodos));
}

int cantidadDeNodos(Stack *fullStack)
{
    int num = 0;
    if (vacia(fullStack))
    {
        printf("Stack underflow\n");
        return num;
    }

    Nodo* actual = fullStack->top;
    while (actual != NULL)
    {
        num++;
        actual = actual->sig;
    }

    return num;
}