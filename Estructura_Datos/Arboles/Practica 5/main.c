#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define raiz 0
#define null NULL

int main (int argc, char* argv[]) // recibe como argumento un numero entrero
{
    if (argc < 2)
    {
        printf("Faltan Argumentos\n");
        return 1;
    }

    int SIZE = atoi(argv[1]);
    int valorBuff;

    Nodo* arbol = null;
    
    printf("Ingresando {%d} valores.\n", SIZE);

    int* valores = calloc(SIZE, sizeof(int));

    for (int i = 0 ; i < SIZE ; i++) 
    {
        printf("\n> ");
        scanf("\n%d", &valores[i]);
        arbol = insertarNodo(arbol, valores[i]);
    }

    printf("\nMostrando arbol.\n\n");
    imprimirArbol(arbol, raiz);

    printf("\n\nInserte el valor a buscar > ");
    scanf("\n%d", &valorBuff);

    int lvl = calcularNivel(arbol, valorBuff, 1);

    if (lvl == -1)
    {
        printf("No se encontro el valor.\n");
    }else{
        printf("El nivel donde esta el valor {%d} es: %d\n", valorBuff, lvl);
    }

    printf("\nProfunidad del arbol: %d\n", calcularAltura(arbol));
    printf("Cantidad de nodos del arbol: %d\n\n", numElementos(arbol));

    borrarArbol(&arbol);
    free(valores);

    return  0;
}