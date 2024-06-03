#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stdbool.h"

#define NAME_SIZE 100
#define SIZE_DATA 105
#define null NULL

typedef struct Movie 
{
    int id;
    char name[NAME_SIZE];
    int year;
    int rating;
    struct Movie* siguiente;
    
} Movie;

typedef struct 
{
    Movie** table;
    int size;
    int dataAmount;

    int lastIDdeleted;

} HashTable;


//* FUNCIONES TABLA HASH
HashTable* initHashTable(int size);
void liberarTablaHash(HashTable* table);
void insertarEnTablas(HashTable* hashID, HashTable* hashNombre, int id, char* name, int year, int rating);
unsigned int funcionHash(int id, int size);
unsigned int generarLlaveString(char* name, int size);
void imprimirTablaHash(HashTable* table);

//* OPERACIONES TABLA HASH

// * aux
//void posicionarPunteroActual(Movie** apuntadorActual, Movie** apuntadorAnterior, int idBusqueda);
//void moverPunteroEliminar(HashTable* hash, Movie** actual, Movie** anterior, int index);
// * aux
void eliminarPorID(HashTable* hashID, HashTable* hashNombre, int id);
void eliminarPorNombre(HashTable* hashNombres, HashTable* hashID, char* name);
bool buscarPeliculasNombre(HashTable* hashNombre, char* name);
Movie* buscarPeliculaPorID(HashTable* hashID, int id);
void remapearTablaNombre(HashTable* hashNombre, int newSize);
void remapearTablaID(HashTable* hashID, int newSize);

//* FUNCIONES MOVIE
void create_movies(HashTable* hashID, HashTable* hashNombre);
void printMovie(Movie* movie);
Movie* initMovie(int id, char* name, int year, int rating);