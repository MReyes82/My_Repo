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
        //pilaLibros[i].numStacks = 0;
        inicializarPila(pilaLibros[i].stackLibros, 0); // sin limite
    }

    while (runs)
    {
        system("clear");
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
            char *genero = submenuApilarPorGenero();

            if (genero == NULL) { break; }
            
            while(!vacia(caja))
            {
                apilarPorGenero(&pilaLibros[0], pop(caja), genero);
            }

            free(genero);
            imprimirPila(pilaLibros[0].stackLibros);

            while(!vacia(pilaLibros[0].stackLibros))
            {
                push(caja, pop(pilaLibros[0].stackLibros));

            }
            
            break;

        case 3:
            printf("\n");
            int year = submenuApilarPorFecha();

            if (year < 0) { break; }
            
            while(!vacia(caja))
            {
                apilarPorFecha(&pilaLibros[1], pop(caja), year);
            }

            imprimirPila(pilaLibros[1].stackLibros);

            while(!vacia(&pilaLibros[1].stackLibros))
            {
                push(&caja, pop(&pilaLibros[1].stackLibros));

            }

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

    free(caja);

    return 0;
}