#include "header.h"
#include <stdio.h>
#include <stdlib.h>
//#include <time.h>

#define raiz 0

int main (void)
{
    //srand(time(NULL));

    int valorBuff;

    Nodo* arbol = crearNodo(10);
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

    int lvl = calcularNivel(arbol, valorBuff, 1);

    if (lvl == -1)
    {
        printf("No se encontro el valor.\n");
    }else{
        printf("El nivel donde esta el valor {%d} es: %d\n", valorBuff, lvl);
    }

    arbol = borrarArbol(&arbol);

    if (arbol == NULL) { printf("\nSet to null\n"); }
    /*
    int temp;
    for (int i = 0 ; i < 7 ; i++)
    {
        printf("\n> ");
        scanf("\n%d", &temp);
        insertarNodo(&arbol, temp);
    }

    printf("\n");
    imprimirArbol(arbol, raiz);
    borrarArbol(&arbol);
    */
    //arbol = NULL;
    

    return  0;
}