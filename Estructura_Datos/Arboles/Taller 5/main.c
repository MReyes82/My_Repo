#include "header.h"
#include <stdlib.h>
#include <stdio.h>

#define null NULL
#define desdeRaiz 0

int main (void)
{
    Nodo* raiz = crearNodo(10);

    raiz->izquierda = crearNodo(5);
    raiz->derecha = crearNodo(15);

    Nodo* raiz1 = crearNodo(10);

    raiz1->izquierda = crearNodo(5);
    raiz1->derecha = crearNodo(15);

    printf("\nMostrando arbol 1...\n");
    imprimirArbol(raiz, desdeRaiz);

    printf("\nCantidad de elementos del arbol 1: %d\n", contarElementos(raiz));

    printf("\nLa altura del arbol 1 es: %d\n", calcularAltura(raiz));

    printf("\nMostrando arbol 2...\n");
    imprimirArbol(raiz1, desdeRaiz);

    printf("\nCantidad de elementos del arbol 2: %d\n", contarElementos(raiz1));

    printf("\nLa altura del arbol 2 es: %d\n", calcularAltura(raiz1));

    if (compararArboles(raiz, raiz1))
    {
        printf("\nLos arboles son iguales.\n");

    }else{
        printf("\nLos arboles no son iguales\n");
    }

    raiz = borrarArbol(&raiz);

    if (raiz == null)
    {
        //printf("\nArbol 1 borrado.\n");
    }

    raiz1 = borrarArbol(&raiz1);

    if (raiz1 == null)
    {
        //printf("\nArbol 2 borrado.\n");
    }


    raiz = crearNodo(10);

    raiz->izquierda = crearNodo(5);
    raiz->derecha = crearNodo(15);

    raiz1 = crearNodo(10);

    raiz1->izquierda = crearNodo(5);
    raiz1->derecha = crearNodo(10);

    printf("\nMostrando arbol 1...\n");
    imprimirArbol(raiz, desdeRaiz);

    printf("\nCantidad de elementos del arbol 1: %d\n", contarElementos(raiz));

    printf("\nLa altura del arbol 1 es: %d\n", calcularAltura(raiz));

    printf("\nMostrando arbol 2...\n");
    imprimirArbol(raiz1, desdeRaiz);

    printf("\nCantidad de elementos del arbol 2: %d\n", contarElementos(raiz1));

    printf("\nLa altura del arbol 2 es: %d\n", calcularAltura(raiz1));

    if (compararArboles(raiz, raiz1))
    {
        printf("\nLos arboles son iguales.\n");

    }else{
        printf("\nLos arboles no son iguales\n");
    }

    raiz = borrarArbol(&raiz);

    if (raiz == null)
    {
        printf("\nArbol 1 borrado.\n");
    }

    raiz1 = borrarArbol(&raiz1);

    if (raiz1 == null)
    {
        printf("\nArbol 2 borrado.\n");
    }

    return 0;
}