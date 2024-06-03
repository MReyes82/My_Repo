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

int numElementos(Nodo* nodo) // retorna la cantidad de nodos
{
    int n = 0;
    if (nodo != null)
    {
        if(nodo->derecha != null)
        {
            n += numElementos(nodo->derecha);
        }

        if(nodo->izquierda != null)
        {
            n += numElementos(nodo->izquierda);
        }

        n++;
    }

    return n;
}

int calcularAltura(Nodo* arbol) // calcula la profundidad/altura
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

int calcularNivel(Nodo* raiz, int valorBusqueda, int nivelActual) 
{
    if (raiz == null) 
    { return -1; } // si el arbol esta vacio

    if (raiz->valor == valorBusqueda)
    { return nivelActual - 1; } // si es igual, retornamos el valor de nivel actual

    int nivel = calcularNivel(raiz->izquierda, valorBusqueda, nivelActual + 1);

    if (nivel != -1) 
    { return nivel; }

    nivel = calcularNivel(raiz->derecha, valorBusqueda, nivelActual + 1);

    return nivel;
}

/* 
*   insertar un nodo al arbol, manteniendo el orden preestablecido
*   regresa la raiz del arbol 
*/ 
Nodo* insertarNodo(Nodo* raiz, int valor) 
{
    if (raiz == null)
    {
        raiz = crearNodo(valor);
    }
    else if (valor <= raiz->valor)
    {
        raiz->izquierda = insertarNodo(raiz->izquierda, valor);
    }
    else
    {
        raiz->derecha = insertarNodo(raiz->derecha, valor);
    }

    return raiz;
}