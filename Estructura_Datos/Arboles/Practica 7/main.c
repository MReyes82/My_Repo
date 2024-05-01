#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define size_exp 16

int main(void)
{
    // TODO: implementar parser para la expresion, y luego evaluarla
    // TODO: progreso de la practica = 30%

    // TODO: PS: este orden es el correcto para obtener el arbol de expresion indicado en el documento
    /*
    Nodo* arbolExpresion = null;
    const char expresion[] = "x+y/a+b*c^d";

    insertarNodo(&arbolExpresion, expresion[5], 5); +
    insertarNodo(&arbolExpresion, expresion[1], 1); + 
    insertarNodo(&arbolExpresion, expresion[7], 7); *
    insertarNodo(&arbolExpresion, expresion[0], 0); x 
    insertarNodo(&arbolExpresion, expresion[3], 3); /
    insertarNodo(&arbolExpresion, expresion[2], 2); y
    insertarNodo(&arbolExpresion, expresion[4], 4); a
    insertarNodo(&arbolExpresion, expresion[6], 6); b
    insertarNodo(&arbolExpresion, expresion[9], 9); ^
    insertarNodo(&arbolExpresion, expresion[8], 8); c
    insertarNodo(&arbolExpresion, expresion[10], 10); d

    printSpaces(3);
    //imprimirArbol(arbolExpresion, 0);
    recorridoEnOrden(arbolExpresion);
    printSpaces(3);
    imprimirArbol(arbolExpresion, 0);
    printSpaces(3);
    borrarArbol(&arbolExpresion);
    
    x+y/a+b*c^d
    (x+(y/a))+(b*(c^d))
    */
    bool runs = true;
    int opcion;
    char exp[size_exp];
    //int i;

    while (runs)
    {
        printSpaces(1);
        printf("EXPRESION: \n");
        printf("[0] CAPTURAR EXPRESION\n");
        printf("[1] EVALUAR EXPRESION\n");
        printf("[2] TERMINAR PROGRAMA\n");
        printf("\nElige una opcion > ");
        scanf("\n%d", &opcion);
        limpiarBufferDeEntrada(); // limpiar buffer de entrada

        switch (opcion)
        {
        case 0:
            printSpaces(1);
            printf("Ingresa la expresion: ");
            fgets(exp, size_exp, stdin);
            //system("pause");

            size_t len = strlen(exp);

            if (len > 0 && exp[len - 1] == '\n')
            { exp[len - 1] = '\0'; }

            bool expresionEsValida = esValida(exp);

            if (!expresionEsValida)
            {
                printf("La expresion no es valida.\n");
                limpiarBufferDeEntrada(); 
                break; // salimos.                    

            }else{
                printf("La expresion es valida.\n");
            }

            char* expPostfija = infixToPostfix(exp);

            printf("Postfix: %s\n", expPostfija);
            free(expPostfija);

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
