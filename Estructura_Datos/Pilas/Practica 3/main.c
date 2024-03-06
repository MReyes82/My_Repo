#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
    int opcion, i, seleccion;
    Pila *caja;
    caja = inicializarCaja();
    int runs = 1;

    StackArray pilaLibros[2];
    // incializamos el array de stacks
    for (i = 0 ; i < 2 ; i++)
    {
        pilaLibros[i].stackLibros = malloc(sizeof(Pila));
        pilaLibros[i].numStacks = 0;
        inicializarPila(pilaLibros[i].stackLibros, 0); // sin limite
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
            
            while (!vacia(*caja))
            {
                Libro *auxiliar = pop(caja);
                apilarPorGenero(&pilaLibros[0], auxiliar);
            }

            // mostramos generos
            for (int i = 0 ; i < pilaLibros[0].numStacks ; i++)
            {
                printf("\n[%d] %s", i, pilaLibros[0].stackLibros[i].cima->elementoLibro->genero);
            }
            seleccion = subMenu("\nElige una opcion > \n");

            imprimirPila(&pilaLibros[0].stackLibros[seleccion]);

            // regresamos los libros a la caja
            for (i = 0 ; i < pilaLibros[0].numStacks ; i++)
            {
                while (!vacia(pilaLibros[0].stackLibros[i]))
                {
                    push(caja, pop(&pilaLibros[0].stackLibros[i]));
                }
            }
            pilaLibros->numStacks = 0;
            
            break;

        case 3:
            printf("\n");

            while (!vacia(*caja))
            {
                Libro *auxiliar = pop(caja);
                apilarPorFecha(&pilaLibros[1], auxiliar);
            }

            // mostrando fechas
            for(i = 0 ; i < pilaLibros[1].numStacks ; i++)
            {
                printf("\n[%d] %d", i, pilaLibros[1].stackLibros[i].cima->elementoLibro->releaseDate);
            }

            seleccion = subMenu("\nElige una opcion > \n");

            imprimirPila(&pilaLibros[1].stackLibros[seleccion]);

            // regresamos los libros a la caja
            for (i = 0 ; i < pilaLibros[1].numStacks ; i++)
            {
                while (!vacia(pilaLibros[1].stackLibros[i]))
                {
                    push(caja, pop(&pilaLibros[1].stackLibros[i]));
                }
            }
            pilaLibros->numStacks = 0;

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