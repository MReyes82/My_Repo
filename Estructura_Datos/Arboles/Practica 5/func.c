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

int numElementos(Nodo* nodo) // retorno la cantidad de nodos
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
        //return n;
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
    if (raiz == null) { return -1; } // si el arbol esta vacio

    if (raiz->valor == valorBusqueda)
    { return nivelActual; } // si es igual, retornamos el valor de nivel actual

    int nivel = calcularNivel(raiz->izquierda, valorBusqueda, nivelActual + 1);

    if (nivel != -1) { return nivel; }

    nivel = calcularNivel(raiz->derecha, valorBusqueda, nivelActual + 1);

    return nivel;
}


void insertarNodo(Nodo** raiz, int valor) 
{
    if (*raiz == null) 
    {
        *raiz = crearNodo(valor);
        return;
    }

    if ((*raiz)->valor == valor) 
    {
        insertarNodo(&(*raiz)->izquierda, valor);
        return;
    }

    if (valor < (*raiz)->valor) 
    {
        insertarNodo(&(*raiz)->izquierda, valor);

    } else {
        insertarNodo(&(*raiz)->derecha, valor);
    }
}

void insertarNodosBalanceados(Nodo** raiz, int* valores, int inicio, int fin) 
{
    if (inicio > fin) 
    {
        return;
    }

    int medio = (inicio + fin) / 2;
    insertarNodo(raiz, valores[medio]);

    insertarNodosBalanceados(raiz, valores, inicio, medio - 1);
    insertarNodosBalanceados(raiz, valores, medio + 1, fin);
}

void llenarArbolBalanceado(Nodo** raiz, int* valores, int n) 
{
    // Ordenar el arreglo de valores
    qsort(valores, n, sizeof(int), compararEnteros);

    // Insertar los valores balanceadamente en el árbol
    insertarNodosBalanceados(raiz, valores, 0, n - 1);
}

int compararEnteros(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}
