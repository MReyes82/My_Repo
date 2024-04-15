#include "header.h"
#include <stdio.h>
#include <stdlib.h>

Nodo* crearNodo(char valor)
{
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->valor = valor;
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

Nodo* insertarNodo(Nodo* raiz, char valor) 
{
    if (raiz == null)
    {
        raiz = crearNodo(valor);
    }
    else if (esOperador(valor))
    {
        raiz->izquierda = insertarNodo(raiz->izquierda, valor);
    }
    else
    {
        raiz->derecha = insertarNodo(raiz->derecha, valor);
    }

    return raiz;
}

int esOperador(char valor)
{   // retorna 1 si el valor es un operador
    return (valor == '+' || valor == '-' || valor == '*' || valor == '/' || valor == '^');
}

void recorridoPreOrden(Nodo* raiz)
{
    if (raiz != null) // mientras el nodo recibido como argumento no sea nulo
    {                 // es decir, mientras haya nodos que seguir visitando
        // se visita la raiz.
        printf("%c ", raiz->valor); 
        // se sigue con el subarbol izquierdo de la raiz.
        recorridoPreOrden(raiz->izquierda); 
        // posteriormente, el subarbol derecho.
        recorridoPreOrden(raiz->derecha); 
    }
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

void recorridoPostOrden(Nodo* raiz)
{
    if (raiz != null)
    {
        recorridoPostOrden(raiz->izquierda);
        recorridoPostOrden(raiz->derecha);
        // hasta el final se visita la raiz
        printf("%c ", raiz->valor);
    }
}

void printNL(void)
{
    printf("\n\n\n");
    return;
}