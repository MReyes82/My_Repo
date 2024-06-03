#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    int i, valorBuffer;
    Nodo* arbol = null;
    Nodo* arbolOriginal = null; // auxiliar para saber si quedaron iguales o no a la hora de eliminar un nodo.

    int valores[] = {5, 3, 10, 1, 4, 9, 11};

    for (i = 0 ; i < 7 ; i++)
    {
        arbol = insertarNodo(arbol, valores[i]);
        arbolOriginal = insertarNodo(arbolOriginal, valores[i]);
    }

    printNL(); // utilidad para imprimir 3 nuevas lineas
    printf("Arbol capturado:\n\n");
    imprimirArbol(arbol, 0);

    printNL();

    printf("Pre orden: \n");
    recorridoPreOrden(arbol);

    printNL();
    printf("En orden: \n");
    recorridoEnOrden(arbol);

    printNL();
    printf("Post orden: \n");
    recorridoPostOrden(arbol);
    printNL();

    Nodo* arbolInv = invertirArbol(arbol);
    printf("Arbol invertido:\n\n");
    imprimirArbol(arbolInv, 0);
    printNL();

    // revertir al orden orginal para poder eliminar un nodo
    arbol = invertirArbol(arbolInv);
    //imprimirArbol(arbol, 0); // debug
    printNL();

    printf("Ingrese el valor a borrar: ");
    scanf("\n%d", &valorBuffer);

    arbol = borrarNodo(arbol, valorBuffer);
    
    if (compararArboles(arbol, arbolOriginal)) 
    /*
    * revisamos si los arboles son iguales, si lo son, quiere decir que no se encontro el valor en el arbol
    */
    {
        printf("No se encontro el valor en el arbol.\n");
    }
    else{
        printf("Arbol despues de borrar el nodo %d:\n\n", valorBuffer);
        imprimirArbol(arbol, 0);
    }

    printNL();

    borrarArbol(&arbol);
    arbolInv = null;
    borrarArbol(&arbolOriginal);

    return 0;
}