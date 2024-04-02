#include "header.h"
#include <stdlib.h>
#include <stdio.h>

#define null NULL

Nodo* crearNodo(int valor)
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
        printf(" %d", nodo->valor); 

        if(nodo->derecha != null)
        {
            printf("\n");

            for (i = 0 ; i < nivel + 1 ; i++)
            {
                if (i == nivel) { printf(" |____R "); }

                else { printf(" |      ");}
            }
            // recursivo: volvemos a empezar 
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

        //return null;
    }

    return null;
}

int contarElementos(Nodo* nodo)
{
    int n = 0;
    if (nodo != null)
    {
        if(nodo->derecha != null)
        {
            n += contarElementos(nodo->derecha);
        }

        if(nodo->izquierda != null)
        {
            n += contarElementos(nodo->izquierda);
        }

        n++;
        //return n;
    }

    return n;
}

int calcularAltura(Nodo* arbol)
{
    if (arbol == null)
    {   // caso base: la altura es 0
        return 0;
    }
    else
    {
        // llamamos a la funcion por cada lado del nodo Raiz
        int alturaIzquierda = calcularAltura(arbol->izquierda);
        int alturaDerecha = calcularAltura(arbol->derecha);

        /*
        * la altura del arbol es simplemente
        * la altura maxima de los "subarboles"
        * mas 1 (por la raiz)
        */
        if (alturaIzquierda > alturaDerecha)
        {
            return alturaIzquierda + 1;
        }
        else
        {
            return alturaDerecha + 1;
        }
    }
}

int compararArboles(Nodo* arbolA, Nodo* arbolB)
{   // regresa 1 si son iguales, 0 si no
    if (arbolA == null && arbolB == null)
    {
        return 1;
    }

    if (arbolA == null || arbolB == null)
    {
        return 0;
    }

    if (arbolA->valor != arbolB->valor)
    {
        return 0;
    }

    return compararArboles(arbolA->izquierda, arbolB->izquierda) && 
            compararArboles(arbolA->derecha, arbolB->derecha);
}