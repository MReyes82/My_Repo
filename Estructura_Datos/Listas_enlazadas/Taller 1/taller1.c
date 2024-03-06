#include "taller1_headers.h"
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    Nodo *inicio_lista = NULL;

    insertarNodoEnLista(&inicio_lista, 13);
    insertarNodoEnLista(&inicio_lista, 5);
    insertarNodoEnLista(&inicio_lista, 9);

    printf("-------------------------------\n");
    printf("Lista desordenada: \n");
    imprimirNodos(inicio_lista);
    // aqui hice una funcion que solo ordena la lista
    ordenarListaAscendente(&inicio_lista);
    printf("\nLista ordenada: \n");
    imprimirNodos(inicio_lista);

    insertarNodoEnLista(&inicio_lista, 2);
    insertarNodoEnLista(&inicio_lista, 18);
    insertarNodoEnLista(&inicio_lista, 6);
    insertarNodoEnLista(&inicio_lista, 7);
    insertarNodoEnLista(&inicio_lista, 9);
    insertarNodoEnLista(&inicio_lista, 16);

    printf("\nLista desordenada: \n");
    imprimirNodos(inicio_lista);
    ordenarListaAscendente(&inicio_lista);
    printf("\nLista ordenada: \n");
    imprimirNodos(inicio_lista);

    liberarMemoriaNodos(&inicio_lista);

    printf("\n-------------------------------\n");

    return 0;
}