#include "header.h"
#include <stdio.h>
#include <stdlib.h>

Nodo* crearNodo(char valor, int indice)
{
    Nodo* nodo = malloc(sizeof(Nodo));

    nodo->valor = valor;
    nodo->indice = indice;
    nodo->izquierda = null;
    nodo->derecha = null;

    return nodo;
}

void imprimirArbol(Nodo* nodo, int nivel)
{
    int i;

    if (nodo != null)
    {
        printf(" %c", nodo->valor); 

        if(nodo->derecha != null)
        {
            printf("\n");

            for (i = 0 ; i < nivel + 1 ; i++)
            {
                if (i == nivel) { printf(" |____R "); }

                else { printf(" |      ");}
            }
            imprimirArbol(nodo->derecha, nivel + 1);
        }

        if(nodo->izquierda != null)
        {
            printf("\n");

            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
            }

            printf("\n");

            for (i = 0 ; i < nivel + 1 ; i++)
            {
                if(i == nivel) { printf(" |____L "); }

                else { printf(" |      "); }
            }

            imprimirArbol(nodo->izquierda, nivel + 1);
        }
    }
}

Nodo* construirArbol(const char* expresion)
{
    /*
    * X * Y / A + B * C ^ D
    * 0 1 2 3 4 5 6 7 8 9 10
    */
    Nodo* raiz = crearNodo(expresion[5], 5);

    raiz->izquierda = crearNodo(expresion[1], 1);
    raiz->derecha = crearNodo(expresion[7], 7);

    raiz->izquierda->izquierda = crearNodo(expresion[0], 0);
    raiz->izquierda->derecha = crearNodo(expresion[3], 3);

    raiz->izquierda->derecha->izquierda = crearNodo(expresion[2], 2);
    raiz->izquierda->derecha->derecha = crearNodo(expresion[4], 4);

    raiz->derecha->izquierda = crearNodo(expresion[6], 6);
    raiz->derecha->derecha = crearNodo(expresion[9], 9);

    raiz->derecha->derecha->izquierda = crearNodo(expresion[8], 8);
    raiz->derecha->derecha->derecha = crearNodo(expresion[10], 10);

    return raiz;
}

int esOperador(char valor)
{   // retorna 1 si el valor es un operador
    return (valor == '+' || valor == '-' || valor == '*' || valor == '/' || valor == '^');
}

void recorridoEnOrden(Nodo* raiz)
{
    if (raiz != null)
    {
        // se recorre el subarbol izquierdo
        recorridoEnOrden(raiz->izquierda); 
        // se visita la raiz
        printf("%c ", raiz->valor); 
        // seguimos con el subarbol derecho
        recorridoEnOrden(raiz->derecha);
    }
}

void obtenerIndices(Nodo* raiz, int* contador, int** arrayIndices)
{
    if (raiz != null)
    {
        obtenerIndices(raiz->izquierda, contador, arrayIndices);
        
        if (esOperador(raiz->valor))
        {
            (*contador)++;
            (*arrayIndices) = realloc(*arrayIndices, sizeof(int) * (*contador));
            (*arrayIndices)[*contador - 1] = raiz->indice;
        }

        obtenerIndices(raiz->derecha, contador, arrayIndices);
    }
}

Nodo* borrarArbol(Nodo** nodo)
{
    if ((*nodo) != null)
    {
        if((*nodo)->derecha != null)
        {
            (*nodo)->derecha = borrarArbol(&(*nodo)->derecha);
        }

        if((*nodo)->izquierda != null)
        {
            (*nodo)->izquierda = borrarArbol(&(*nodo)->izquierda);
        }

        free((*nodo));
    }

    return null;
}

void printArray(int* arr, int len)
{
    printf("[ ");

    for (int i = 0; i < len; i++)
    { printf("%d ", arr[i]); }

    printf("]");

    printf("\n");

    return;
}

void printNL(void)
{
    printf("\n\n\n");
    return;
}