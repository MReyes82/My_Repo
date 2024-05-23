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

} HashTable;

//* Funciones tabla hash
void initHashTable(HashTable* hash, int size, FunctionFolding folding);
int sondeoCuadratico(HashTable* hash, int indice, int i);
int funcionHash(HashTable* hash, int llave);
int generarLlave(const char* nombre);
int calcularLlaveString(Movie* pelicula);
int getID(Movie* pelicula);
int rehashing(HashTable* hash, Movie* pelicula, Movie** nuevasPeliculas);
void liberarTabla(HashTable* hash);

//* Operaciones de tabla hash
void insertarPeliculaNombre(HashTable* hash, Movie* pelicula);
void insertarPeliculaID(HashTable* hash, Movie* pelicula);
void eliminarPeliculaNombre(HashTable* hash, char* nombre);
void eliminarPeliculaID(HashTable* hash, int id);
void imprimirTabla(HashTable* hash);

//* Funciones de busqueda
Movie* buscarPeliculaNombre(HashTable* hash, char* nombre);
Movie* buscarPeliculaID(HashTable* hash, int id);
void remapearTabla(HashTable* hash, int newSize);

//* Funciones auxiliares
void vaciarArregloEstatico(HashTable* hash, Movie** arregloPeliculas);
Movie* initMovie(int id, char* nombre, short int fecha, short int calificacion);

#endif //HASH_H