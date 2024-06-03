#include "header.h"
#include <stdio.h>
#include <stdlib.h>

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

void recorridoPreOrden(Nodo* raiz)
{
    if (raiz != null) // mientras el nodo recibido como argumento no sea nulo
    {                 // es decir, mientras haya nodos que seguir visitando
        // se visita la raiz.
        printf("%d ", raiz->valor); 
        // se sigue con el subarbol izquierdo de la raiz.
        recorridoPreOrden(raiz->izquierda); 
        // posteriormente, el subarbol derecho.
        recorridoPreOrden(raiz->derecha); 
    }

    //printf("\n");
}

void recorridoEnOrden(Nodo* raiz)
{
    if (raiz != null)
    {
        // se recorre el subarbol izquierdo
        recorridoEnOrden(raiz->izquierda); 
        // se visita la raiz
        printf("%d ", raiz->valor); 
        // seguimos con el subarbol derecho
        recorridoEnOrden(raiz->derecha);
    }

    //printf("\n");
}

void recorridoPostOrden(Nodo* raiz)
{
    if (raiz != null)
    {
        recorridoPostOrden(raiz->izquierda);
        recorridoPostOrden(raiz->derecha);
        // hasta el final se visita la raiz
        printf("%d ", raiz->valor);
    }

    //printf("\n");
}

void printNL(void)
{
    printf("\n\n\n");
    return;
}

Nodo* invertirArbol(Nodo* raiz)
{
    if (raiz == null)
    { return raiz; }

    Nodo* auxiliar = raiz->izquierda;
    raiz->izquierda = invertirArbol(raiz->derecha);
    raiz->derecha = invertirArbol(auxiliar);

    return raiz; // regresar raiz modificada
}

Nodo* borrarNodo(Nodo* raiz, int valor)
{
    if (raiz == null)
    { return raiz; }

    if (valor < raiz->valor)
    {
        raiz->izquierda = borrarNodo(raiz->izquierda, valor);
        
    }else if(valor > raiz->valor){
        raiz->derecha = borrarNodo(raiz->derecha, valor);

    }else{ // el valor el nodo es igual al valor de busqueda
            // lo que significa que este es el nodo a eliminar
        if (raiz->izquierda == null && raiz->derecha == null)
        {
            free(raiz);
            raiz = null;

        }else if(raiz->izquierda == null){
            Nodo* aux = raiz;
            raiz = raiz->derecha;
            free(aux);

        }else if(raiz->derecha == null){
            Nodo* aux = raiz;
            raiz = raiz->izquierda;
            free(aux);

        }else{ // la raiz tiene dos hijos
            Nodo* aux = raiz->derecha;

            while (aux->izquierda != null)
            {
                aux = aux->izquierda;
            }

            raiz->valor = aux->valor;
            raiz->derecha = borrarNodo(raiz->derecha, aux->valor);
        }
    }

    return raiz;
}

int compararArboles(Nodo* arbolA, Nodo* arbolB) // regresa 1 si son iguales
{
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