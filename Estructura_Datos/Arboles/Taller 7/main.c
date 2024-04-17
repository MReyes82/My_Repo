#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    Nodo* arbol = null;
      
    char valores[] = "X*Y/A+B*C^D";

    int contador = 0;
    
    int* indices = null;//malloc(sizeof(int)); // arreglo de indices. Necesita ser dinamico por lo tanto sera pointer.

    arbol = construirArbol(valores);

    printNL();
    imprimirArbol(arbol, 0);
    printNL();

    obtenerIndices(arbol, &contador, &indices);
  
    printf("Expresion: \n");
    recorridoEnOrden(arbol);
    printf("\n\nIndices: \n");
    printArray(indices, contador);
    
    borrarArbol(&arbol);
    free(indices);

    return 0;
}