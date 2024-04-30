#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{
    // TODO: implementar funciones del menu
    // TODO: progreso de la practica = 30%

    // TODO: PS: este orden es el correcto para obtener el arbol de expresion indicado en el documento
    /*
    Nodo* arbolExpresion = null;

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
    */
    bool runs = true;
    int opcion;
    //int i;

    // = "X+Y/A+B*C^D";
    //printf("\n%s\n", expresion);

    while (runs)
    {
        printSpaces(1);
        printf("EXPRESION: \n");
        printf("[0] CAPTURAR EXPRESION\n");
        printf("[1] EVALUAR EXPRESION\n");
        printf("[2] TERMINAR PROGRAMA\n");
        printf("\nElige una opcion > ");
        scanf("\n%d", &opcion);

        switch (opcion)
        {
        case 0:
            printSpaces(1);
            char expresion[] = {'X', '+', 'Y', '/', 'A', '+', 'B', '*', 'C', '^', 'D', '\0'};

            /*
            * me da un error de buffer
            char expresion[16];                       
            printf("Ingresa la expresion: ");
            scanf("\n%s", expresion);
            fgets(expresion, sizeof(expresion), stdin);
            
            printf("\nInput: %s\n", expresion);
            */

            bool call = esValida(expresion);

            if (call)
            {
                printf("Bien hecho papu\n");

            }else{
                printf("Hasta la proximaaaa\n");
            }
            
            break;
        
        case 1:
            printSpaces(1);
            // implementar

            break;

        case 2:
            printSpaces(1);
            runs = false;
            // implementar

            break;

        default:
            break;
        }
    }

    return 0;
}
