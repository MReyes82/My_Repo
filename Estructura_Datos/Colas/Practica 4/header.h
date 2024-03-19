#pragma once
#include <stdint.h>

typedef struct Cancion
{
    char* nombre;
    char* autor;
    uint16_t releaseDate; // entero sin signo de 16 bits.

} Cancion;

typedef struct Elemento
{
    Cancion* cancion;
    struct Elemento* siguiente;
    struct Elemento* anterior;

} Elemento;

typedef struct Queue
{
    Elemento* inicio;
    Elemento* final;
    Elemento* actual;
    int length;
    int numeroElementos;
    int posicionActual;

} Queue;

int llena(Queue cola);
int vacia(Queue cola);
//void enqueue(Queue* cola, int datoAInsertar); // poner
void insertarPosicion(Queue* cola, Cancion* datoAInsertar, int posicion);
void eliminarPosicion(Queue* cola, int posicion);
//Elemento* dequeue(Queue* colan); // quitar
void printQueue(Queue* cola);
void desplegarReproduccion(Queue* cola);
Elemento* alojarElemento(Cancion *elemento);
Queue initQueue(int length);
int printStaticQueue();

static Cancion listaPredefinina[15] = 
{
    {"Song 2", "Blur", 1997},
    {"Bohemian Rhapsody", "Queen", 1975},
    {"Imagine", "John Lennon", 1971},
    {"Hey Jude", "The Beatles", 1968},
    {"Stairway to Heaven", "Led Zeppelin", 1971},
    {"Hotel California", "Eagles", 1977},
    {"Smells Like Teen Spirit", "Nirvana", 1991},
    {"Billie Jean", "Michael Jackson", 1983},
    {"Thriller", "Michael Jackson", 1982},
    {"Bohemian Like You", "The Dandy Warhols", 2000},
    {"Under Pressure", "Queen", 1981},
    {"Wish You Were Here", "Pink Floyd", 1975},
    {"Highway to Hell", "AC/DC", 1979},
    {"Back in Black", "AC/DC", 1980},
    {"Let It Be", "The Beatles", 1970}
};