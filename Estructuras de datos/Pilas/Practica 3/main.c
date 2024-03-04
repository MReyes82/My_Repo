#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
    int opcion, i;
    Pila *caja;
    caja = inicializarCaja();
    int runs = 1;

    StackArray pilaLibros[2];
    // incializamos el array de stacks
    for (i = 0 ; i < 2 ; i++)
    {
        pilaLibros[i].stackLibros = malloc(sizeof(Pila));
        pilaLibros[i].numStacks = 0;
        inicializarPila(pilaLibros[i].stackLibros, -1); // sin limite
    }

    while (runs)
    {
        
        printf("\n[1] Mostrar contenido de la caja.");
        printf("\n[2] Apilar por genero.");
        printf("\n[3] Apilar por fecha.");
        printf("\n[4] Terminar programa.");
        printf("\nElige una opcion > ");
        scanf("\n%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("\n[1] Mostrar contenido de la caja.\n");
            imprimirPila(caja);
            break;
        
        case 2:
            printf("\n");
            char *generoInput = submenuApilarPorGenero();


            if (generoInput == NULL) { break; } // si el genero seleccionado
                                                // no es valido
            
            while(!vacia(*caja))
            {
                apilarPorGenero(pilaLibros, pop(caja), generoInput);
            }

            free(generoInput);
            imprimirPila(pilaLibros[0].stackLibros);
            
            break;

        case 3:
            printf("\n");
            int year = submenuApilarPorFecha();

            // si el año seleccionado no es valido
            if (year < 0) { break; }
            
            while(!vacia(*caja))
            {
                apilarPorFecha(pilaLibros, pop(caja), year);
            }

            imprimirPila(pilaLibros[1].stackLibros);

            break;
        
        case 4:
            printf("Hasta luego tilin\n");
            runs = 0;
            break;

        default:
            printf("\nERROR\n");
            break;
        }

    }
    
    for (i = 0 ; i < 2 ; i++)
    {
        free(pilaLibros[i].stackLibros);
    }

    vaciarPila(caja);
    free(caja);

    return 0;
}