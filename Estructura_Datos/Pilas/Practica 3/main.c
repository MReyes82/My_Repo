#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main (void)
{
    int option, selection;
    Stack* box = init_book_box();
    bool runs = true;

    Stack* selected_stack;
    
    Stack_array* box_stacked_by_genre = init_stack_array();
    Stack_array* box_stacked_by_year = init_stack_array();

    while (runs)
    {
        printf("\n[1] Mostrar contenido de la caja.");
        printf("\n[2] Apilar por genero.");
        printf("\n[3] Apilar por fecha.");
        printf("\n[4] Terminar programa.");
        printf("\n> ");
        scanf("\n%d", &option);

        switch (option)
        {
        case 1:
            printf("\n[1] MOSTRAR CONTENIDO DE LA CAJA\n");
            print_stack(box);

            break;
        
        case 2:
            printf("\n[2] APILAR POR GENERO\n");
            
            while (!isEmpty(box))
            {
                Book* aux = pop(box);
                printf("Pops\n");
                genre_stackify(box_stacked_by_genre, aux);
            }

            // mostramos generos
            print_stack_array(box_stacked_by_genre, GENRE);

            selection = sub_menu("\nElige una opcion > \n");

            selected_stack = get_stack(box_stacked_by_genre, selection);
            print_stack(selected_stack);

            // regresamos los libros a la caja
            while (box_stacked_by_genre->top_book_stack != NULL)
            {
                Stack* aux = pop_stack(box_stacked_by_genre);

                while (!isEmpty(aux))
                {
                    Book* tmp = pop(aux);
                    push(box, tmp);
                }
            }
            
            break;

        case 3:
            printf("\n[3] APILAR POR AÑO\n");

            while (!isEmpty(box))
            {
                Book* aux = pop(box);
                date_stackify(box_stacked_by_year, aux);
            }

            // mostramos fechas
            print_stack_array(box_stacked_by_year, YEAR);

            selection = sub_menu("\nElige una opcion > \n");

            selected_stack = get_stack(box_stacked_by_year, selection);
            print_stack(selected_stack);

            // regresamos los libros a la caja
            while (box_stacked_by_year->top_book_stack != NULL)
            {
                Stack* aux = pop_stack(box_stacked_by_year);

                while (!isEmpty(aux))
                {
                    Book* tmp = pop(aux);
                    push(box, tmp);
                }
            }

            break;
        
        case 4:
            printf("Hasta luego tilin\n");
            runs = false;
            break;

        default:
            printf("\nERROR\n");
            break;
        }

    }
    
    free_stack_arr(box_stacked_by_genre);
    free_stack_arr(box_stacked_by_year);

    empty_stack(box);
    free(box);

    return 0;
}