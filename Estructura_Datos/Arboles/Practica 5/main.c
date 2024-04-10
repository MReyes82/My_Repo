#include "header.h"
#include <stdio.h>
#include <stdlib.h>
//#include <time.h>

#define raiz 0
#define SIZE 9
#define null NULL

int main (void)
{
    //srand(time(NULL));

    int valorBuff;

    Nodo* arbol = null;
    /*crearNodo(10);
    arbol->izquierda = crearNodo(8);
    arbol->derecha = crearNodo(5);

    arbol->izquierda->izquierda = crearNodo(6);
    arbol->izquierda->derecha = crearNodo(9);

    arbol->derecha->izquierda = crearNodo(4);
    arbol->derecha->derecha = crearNodo(1);

    printf("\n");
    imprimirArbol(arbol, raiz);
    
    printf("\n\n> ");
    scanf("\n%d", &valorBuff);
    printf("\n\n");
    */
    //arbol = borrarArbol(&arbol);

    //if (arbol == NULL) { printf("\nSet to null\n"); }
    
    printf("Ingresando {%d} valores.\n", SIZE);

    int* valores = calloc(SIZE, sizeof(int));

    for (int i = 0 ; i < SIZE ; i++) 
    {
        //int temp;
        printf("\n> ");
        scanf("\n%d", &valores[i]);
    }

    llenarArbolBalanceado(&arbol, valores, SIZE);

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

    //printf("\nMostrando arbol.\n\n");
    //imprimirArbol(arbol, raiz);

    printf("\nProfunidad del arbol: %d\n", calcularAltura(arbol));
    printf("Cantidad de nodos del arbol: %d\n", numElementos(arbol));

    borrarArbol(&arbol);
    free(valores);

    return  0;
}