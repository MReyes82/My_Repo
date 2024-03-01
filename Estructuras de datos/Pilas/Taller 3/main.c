#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    int pilaTam;

    printf("Ingrese el tamaño de la pila > ");
    scanf("%d", &pilaTam);

    if (pilaTam <= 0)
    {
        printf("Tamaño no valido.\n");
        exit(EXIT_FAILURE);
    }

    Stack pila;
    pila.top = NULL;
    pila.length = 0;
    Stack auxiliar; // pila auxiliar para imprimir los datos de la pila
    auxiliar.top = NULL;
    auxiliar.length = 0;

    int opcion, datoBuffer, i, len;

    while (1)
    {
        printf("\n---------MENU--------\n");
        printf("Eliga una opcion.\n");
        printf("[1] Ver pila.\n[2] Push dato.\n[3] Pop dato.\n[4] Terminar programa.\n");
        printf("Eliga una opcion > ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("\n");
            if (vacia(&pila))
            {
                printf("Pila vacia.\n");
                break;
            }

            printf("Imprimiendo pila...\n");
            printf("TOP\n");
            
            len = pila.length;
            for (i = 0 ; i < len ; i++)
            {
                datoBuffer = 0;
                pop(&pila, &datoBuffer);
                printf("v\n");
                printf("%d\n", datoBuffer);
                push(&auxiliar, datoBuffer, pilaTam);
            }
            // regresamos los datos a la pila original
            for (i = 0 ; i < len ; i++)
            {
                datoBuffer = 0;
                pop(&auxiliar, &datoBuffer);
                push(&pila, datoBuffer, pilaTam);
            }

            printf("---------\n");
            break;
        
        case 2:
            printf("Ingrese el dato > ");
            scanf("%d", &datoBuffer);
            push(&pila, datoBuffer, pilaTam);

            break;

        case 3:
            printf("Ejecutando pop...\n");
            //datoBuffer = 0; iba a dejar estas instrucciones pero si hay stack underflow imprime el 0
            pop(&pila, &datoBuffer);
            //printf("Dato 'popeado': %d", datoBuffer);  tendria que hacer las funciones bool en vez
                                            // de void para saber si pudo hacer la instruccion o no
            break;
        
        case 4:
            printf("Terminando programa...\n");
            liberarMemoriaPila(&pila);
            exit(EXIT_SUCCESS);
            break;

        default:
            printf("Opcion no valida.\n");
            break;
        }
    }
    return 0;
}