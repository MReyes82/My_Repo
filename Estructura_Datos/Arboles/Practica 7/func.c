#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Nodo* crearNodo(char valor, int index)
{
    Nodo* nuevo = malloc(sizeof(Nodo));
    nuevo->valor = valor;
    nuevo->index = index;
    nuevo->izquierda = nuevo->derecha = null;

    return nuevo;
}

void insertarNodo(Nodo** raiz, char valor, int index)
{
    // recorrido preorden para la insersion
    // revisamos el nodo primero, si es nolo insertamos directamente
    if (*raiz == null)
    {
        (*raiz) = crearNodo(valor, index);
        return;
    }
    // si no es nulo, vamos el subarbol izquierdo
    if (index < (*raiz)->index) // si el indice del nuevo nodo es menor al del nodo raiz
    { insertarNodo(&(*raiz)->izquierda, valor, index); }

    else if (index > (*raiz)->index) // si el indice del nuevo nodo es mayor al del nodo raiz
    { insertarNodo(&(*raiz)->derecha, valor, index); } // insertamos en subarbol derecho
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

void borrarArbol(Nodo** raiz) // borrar TODOS los nodos de un arbol
{
    // si terminamos de borrar, salimos de la funcion
    if (*raiz == null) { return; }
    // recorrido postorden para borrar el arbol

    //empezamos borrando el subarbol izquierdo
    borrarArbol(&(*raiz)->izquierda);
    // despues el derecho
    borrarArbol(&(*raiz)->derecha);
    // borramos (llamamos a la funcion free) el nodo raiz al ultimo
    free((*raiz));
    (*raiz) = null;
}

void recorridoEnOrden(Nodo* raiz)
{
    if (raiz != null)
    {
        recorridoEnOrden(raiz->izquierda);
        imprimirCharNodo(raiz->valor);
        recorridoEnOrden(raiz->derecha);
    }
}

void imprimirCharNodo(char caracterDelNodo)
{
    printf("%c", caracterDelNodo);
    return;
}

void printSpaces(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\n");
    }

    return;
}

//bool esValida(const char* expresion); // implementar funcion que evalua una expresion
