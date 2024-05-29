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

} HashTable;


HashTable* initHashTable(int size);
void liberarTablaHash(HashTable* table);
unsigned int funcionHash(int id, int size);
unsigned int generarLlaveString(char* name, int size);
void insertarEnTablas(HashTable* id_table, HashTable* name_table, int id, char* name, int year, int rating);
void eliminarPorID(HashTable* id_table, HashTable* name_table, int id);
void eliminarPorNombre(HashTable* hashNombres, HashTable* hashID, char* name);
bool buscarPeliculasNombre(HashTable* name_table, char* name);
Movie* buscarPeliculaPorID(HashTable* id_table, int id);
void imprimirTablaHash(HashTable* table);

//* FUNCIONES MOVIE
void create_movies(HashTable* id_table, HashTable* name_table);
void printMovie(Movie* movie);
Movie* initMovie(int id, char* name, int year, int rating);