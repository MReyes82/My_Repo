#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void)
{
    Nodo* arbol = null;
    int i;
    
    char valores[] = {'+', '*', '*'}; // expresion en notacion postfija
    
    int len = strlen(valores);
    //int* indices = null; // arreglo de indices. Necesita ser dinamico por lo tanto sera pointer.

    for (i = 0 ; i < len ; i++)
    {
        arbol = insertarNodo(arbol, valores[i]);
    }

    printNL();
    imprimirArbol(arbol, 0);
    printNL();

    borrarArbol(&arbol);

    return 0;
}