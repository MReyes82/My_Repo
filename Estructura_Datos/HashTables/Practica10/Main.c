#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "Movie.h"
#include "Hash.h"


void liberarArreglo(Movie **movies)
{
    int i;

    for(i = 0 ; i < SIZE_DATA ; i++)
    {
        if (movies[i] != null)
        {
            free(movies[i]);
            printf("Liberacion %d\n", i);
        }
    }
    free(movies);

    return;
}

// TODO: Undefined behavior pending
// ^ No Memry leaks

int main(void)
{
    //srand(time(NULL));
    int idTemp = SIZE_DATA;
    int i, opcion, subopcion;
    bool runs = true;
    char nombre[64];

    int tam = SIZE_DATA;

    HashTable tablaHashIdentificadores;
    HashTable tablaHashNombres;

    Movie **arregloPeliculas = NULL;
    arregloPeliculas = create_movies();

    initHashTable(&tablaHashIdentificadores, tam, getID);
    printf("Tabla 1 inicializada\n");
    initHashTable(&tablaHashNombres, (tam * 4), calcularLlaveString);
    printf("Tabla 2 inicializada\n");

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
        printf("%d Primera insercion & ", i);
        insertarPeliculaNombre(&tablaHashNombres, aTabla2);
        printf("Segunda insercion\n");

        pelicula = null;
    }             

    printf("Peliculas insertadas\n");

    printf("Crashea aqui");
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
            imprimirTabla(&tablaHashIdentificadores);

            break;

        case 1:
            printf("\n----Mostrando tabla hash 2----\n");
            imprimirTabla(&tablaHashNombres);

            break;
        
        case 2:
            printf("\n----Buscando pelicula por ID---\n");

            printf("Ingrese el ID de la pelicula > ");
            scanf("%d", &i);

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

            //Movie* peliculaNombre = buscarPeliculaNombre(&tablaHashNombres, nombre);
            Movie** peliculas = buscarPeliculasNombre(&tablaHashNombres, nombre, &i);

            if (peliculas[0] == null)
            {
                printf("Pelicula no encontrada\n");
                break;
            }

            mostrarPeliculasNombre(peliculas, i);

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

            id = idTemp++;

            Movie *peliculaNueva = initMovie(id, nombre, fecha, calificacion);
            Movie *peliculaNueva1 = initMovie(id, nombre, fecha, calificacion);

            insertarPeliculaID(&tablaHashIdentificadores, peliculaNueva);
            insertarPeliculaID(&tablaHashNombres, peliculaNueva1);

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

                eliminarPeliculaID(&tablaHashIdentificadores, i);
                eliminarPeliculaID(&tablaHashNombres, i);
            }
            else if (subopcion == 1)
            {
                printf("\nIngrese el nombre de la pelicula > ");
                scanf("\n%[^\n]s", nombre);

                Movie** peliculasEliminar = buscarPeliculasNombre(&tablaHashNombres, nombre, &i);

                if (peliculasEliminar[0] == NULL)
                {
                    printf("Pelicula no encontrada\n");
                    break;
                }
                
                mostrarPeliculasNombre(peliculasEliminar, i);
                printf("Inserte el ID de la pelicula que desea eliminar > ");
                int op;
                scanf("\n%d", &op);

                eliminarPeliculaID(&tablaHashIdentificadores, op);
                eliminarPeliculaID(&tablaHashNombres, op);
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