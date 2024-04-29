#include "header.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    // TODO: implementar funciones del menu
    // TODO: progreso de la practica = 20%

    // TODO: PS: este orden es el correcto para obtener el arbol de expresion indicado en el documento
    Nodo* arbolExpresion = null;
    //int i;

    const char* expresion = "X+Y/A+B*C^D";
    printf("\n%s\n", expresion);

    insertarNodo(&arbolExpresion, expresion[5], 5);
    insertarNodo(&arbolExpresion, expresion[1], 1);
    insertarNodo(&arbolExpresion, expresion[7], 7);
    insertarNodo(&arbolExpresion, expresion[0], 0);
    insertarNodo(&arbolExpresion, expresion[3], 3);
    insertarNodo(&arbolExpresion, expresion[2], 2);
    insertarNodo(&arbolExpresion, expresion[4], 4);
    insertarNodo(&arbolExpresion, expresion[6], 6);
    insertarNodo(&arbolExpresion, expresion[9], 9);
    insertarNodo(&arbolExpresion, expresion[8], 8);
    insertarNodo(&arbolExpresion, expresion[10], 10);

    printSpaces(3);
    imprimirArbol(arbolExpresion, 0);
    printSpaces(3);
    borrarArbol(&arbolExpresion);
    return 0;
}
