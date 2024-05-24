#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Movie.h"
#include "Hash.h"

void imprimirArreglo(Movie **movies)
{
    Movie *dataTemp = null;
    int i;
    for(i = 0 ; i < SIZE_DATA ; i++)
    {
        dataTemp = getMovie(movies,i);

        if(dataTemp)
        {
            printMovie(movies[i]);
            printf("\n");
        }
    }

    return;
}

void liberarArreglo(Movie **movies)
{
    int i;

    for(i = 0 ; i < SIZE_DATA ; i++)
    {
        if (movies[i] != null)
        {
            free(movies[i]);
        }
    }
    free(movies);

    return;
}

// TODO: Arreglar bug de identificador duplicado.
// ^ No Memry leaks

int main(void)
{
    int i, opcion, subopcion;
    bool runs = true;
    char nombre[50];

    HashTable tablaHashIdentificadores;
    HashTable tablaHashNombres;

    Movie **arregloPeliculas = NULL;
    arregloPeliculas = create_movies();

    initHashTable(&tablaHashIdentificadores, SIZE_DATA, getID);
    initHashTable(&tablaHashNombres, SIZE_DATA, calcularLlaveString);

    for (i = 0 ; i < SIZE_DATA ; i++)
    {
        Movie *pelicula = getMovie(arregloPeliculas, i);

        if (pelicula == null)
        {
            continue;
        }

        Movie* aTabla1 = initMovie(pelicula->id, pelicula->name, pelicula->release_date, pelicula->rating);
        Movie* aTabla2 = initMovie(pelicula->id, pelicula->name, pelicula->release_date, pelicula->rating);

        insertarPeliculaID(&tablaHashIdentificadores, aTabla1);
        insertarPeliculaNombre(&tablaHashNombres, aTabla2);

        pelicula = null;
    }                   

    liberarArreglo(arregloPeliculas);

    while (runs)
    {
        printf("\n----MENU----\n");
        printf("[0] MOSTRAR HASH ID\n");
        printf("[1] MOSTRAR HASH NOMBRE\n");
        printf("[2] BUSCAR PELICULA ID\n");
        printf("[3] BUSCAR PELICULA NOMBRE\n");
        printf("[4] AGREGAR PELICULA\n");
        printf("[5] ELIMINAR PELICULA\n");
        printf("[6] TERMINAR PROGRAMA\n");

        printf("Eliga una opcion > ");
        scanf("\n%d",&opcion);

        switch (opcion)
        {
        case 0:
            printf("\n----Mostrando tabla hash 1----\n");
            imprimirDatosTabla(&tablaHashIdentificadores);
            imprimirTabla(&tablaHashIdentificadores);

            break;

        case 1:
            printf("\n----Mostrando tabla hash 2----\n");
            imprimirDatosTabla(&tablaHashNombres);
            imprimirTabla(&tablaHashNombres);

            break;
        
        case 2:
            printf("\n----Buscando pelicula por ID---\n");

            printf("Ingrese el ID de la pelicula > ");
            scanf("%d",&i);

            Movie *pelicula = buscarPeliculaID(&tablaHashIdentificadores, i);

            if (pelicula != null)
            {
                printMovie(pelicula);
                printf("\n");

                break;
            }

            printf("Pelicula no encontrada\n");

            break;

        case 3:
            printf("\n----Buscando pelicula por nombre---\n");

            printf("\nIngrese el nombre de la pelicula > ");
            scanf("\n%[^\n]s", nombre);

            Movie* peliculaNombre = buscarPeliculaNombre(&tablaHashNombres, nombre);

            if (peliculaNombre != null)
            {
                printMovie(peliculaNombre);
                printf("\n");

                break;
            }

            printf("Pelicula no encontrada\n");

            break;

        case 4:
            printf("\n----Agregando pelicula---\n");

            int id, fecha, calificacion;

            printf("\nIngrese el nombre de la pelicula > ");
            scanf("\n%[^\n]s", nombre);
            printf("Ingrese la fecha de la pelicula > ");
            scanf("%d", &fecha);
            printf("Ingrese la calificacion de la pelicula > ");
            scanf("%d", &calificacion);

            id = tablaHashIdentificadores.amount_data + 1;
            // ^^^: This is a bug. The ID should be the next available ID, not the amount of data + 1.
            Movie *peliculaNueva = initMovie(id, nombre, fecha, calificacion);
            Movie *peliculaNueva1 = initMovie(id, nombre, fecha, calificacion);


            insertarPeliculaID(&tablaHashIdentificadores, peliculaNueva);
            insertarPeliculaNombre(&tablaHashNombres, peliculaNueva1);

            break;

        case 5:
            printf("\n----Eliminando pelicula---\n");

            printf("[0] Eliminar por ID\n");
            printf("[1] Eliminar por nombre\n");
            printf("Eliga una opcion > ");
            
            scanf("\n%d", &subopcion);

            if (subopcion == 0)
            {
                printf("\nIngrese el ID de la pelicula > ");
                scanf("\n%d", &i);

                Movie* peliculaEliminar = buscarPeliculaID(&tablaHashIdentificadores, i);

                if (peliculaEliminar == NULL)
                {
                    printf("Pelicula no encontrada\n");
                    break;
                }
                char* nombre = peliculaEliminar->name;

                eliminarPeliculaID(&tablaHashIdentificadores, i);
                eliminarPeliculaNombre(&tablaHashNombres, nombre);
            }
            else if (subopcion == 1)
            {
                printf("\nIngrese el nombre de la pelicula > ");
                scanf("\n%[^\n]s", nombre);

                Movie* peliculaEliminar = buscarPeliculaNombre(&tablaHashNombres, nombre);

                if (peliculaEliminar == NULL)
                {
                    printf("Pelicula no encontrada\n");
                    break;
                }
                int idTemp = peliculaEliminar->id;

                eliminarPeliculaNombre(&tablaHashNombres, nombre);
                printf("Borra en tabla 1\n");
                eliminarPeliculaID(&tablaHashIdentificadores, idTemp);
                printf("Borra en tabla 2\n");
            }

            break;

        case 6:
            runs = false;
            break;

        default:
            break;
        }
    }

    liberarTabla(&tablaHashIdentificadores);
    liberarTabla(&tablaHashNombres);

    printf("Programa terminado\n");
    
    return 0;
}