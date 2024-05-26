#ifndef HASH_H
#define HASH_H

#define null NULL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Movie.h"


typedef int (*FunctionFolding)(Movie*); //POINTER A FUNCION

typedef struct hashtable
{
    int size;          //DATOS QUE PUEDE CONTENER
    int amount_data; //DATOS CONTENIDOS
    Movie** table; //ALMACENAMIENTO
    FunctionFolding folding; //POINTER A FUNCION FOLDING

    int last_id_deleted; // ID DE LA ULTIMA PELICULA ELIMINADA
                         // UTILIZADO COMO METODO PARA EVITAR
                        // ID DUPLICADOS
    //int max_id;

} HashTable;

//* Funciones tabla hash
void initHashTable(HashTable* hash, int size, FunctionFolding folding);
int funcionHash(int llave, int tam);
int generarLlave(const char* nombre);
int calcularLlaveString(Movie* pelicula);
int getID(Movie* pelicula);
//void rehashing(HashTable* hash, Movie* pelicula, Movie** Peliculas, int size);
void liberarTabla(HashTable* hash);

//* Operaciones de tabla hash
void insertarPeliculaNombre(HashTable* hash, Movie* pelicula);
void insertarPeliculaID(HashTable* hash, Movie* pelicula);

void eliminarPeliculaNombre(HashTable* hash, char* nombre);
void eliminarPeliculaID(HashTable* hash, int id);
void imprimirTabla(HashTable* hash);

//* Funciones de busqueda
// ^ Antigua funcion de buscar por nombre, ahora se acepta mas de un elemento con el mismo nombre.
//Movie* buscarPeliculaNombre(HashTable* hash, char* nombre);
Movie** buscarPeliculasNombre(HashTable* hash, char* nombre, int* cantidadPeliculas);
void mostrarPeliculasNombre(Movie** peliculas, int cantidadPeliculas);
Movie* buscarPeliculaID(HashTable* hash, int id);
void remapearTabla(HashTable* hash, int newSize);

//* Funciones auxiliares
Movie* initMovie(int id, char* nombre, short int fecha, short int calificacion);
void imprimirDatosTabla(HashTable* hash);

#endif //HASH_H