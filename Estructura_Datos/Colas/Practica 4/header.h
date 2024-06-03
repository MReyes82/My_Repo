#pragma once
#include <stdbool.h>

typedef struct 
{
    char* nombre;
    char* autor;
    int fechaSalida;

} Cancion;

typedef struct Elemento 
{
    Cancion* cancion;
    struct Elemento* siguiente;
    struct Elemento* anterior;

} Elemento;

typedef struct 
{
    Elemento* inicio;
    Elemento* final;
    Elemento* actual;

    int maxTam;
    int cantidadElementos;  
    bool estaEnBucle;
    bool estaEnPrimIter;

} Cola;

void desplegarReproduccion(Cola* colaReproduccion);
void dequeue(Cola *cola, int posicion);
void enqueue(Cola* cola, Cancion* cancion, int posicion);
void inicializarCola(Cola* cola);
Elemento* alojarElemento(Cancion* cancion);
void mostrarColaReproduccion(Cola* cola);
int mostrarPlaylist(void);
void toggleBucle(Cola* cola, int activar);
bool estaEnModoCircular(Cola* cola);

static Cancion playlistOriginal[15] = 
{
    {"Like a Stone", "Audioslave", 2002},
    {"Decadence", "Disturbed", 2005},
    {"Something In The Way", "Nirvana", 1991},
    {"505", "Arctic Monkeys", 2007},
    {"Creep", "Radiohead", 1993},
    {"Freak On A Leash", "Korn", 1998},
    {"Twist", "Korn", 1996},
    {"Coming Undone", "Korn", 2005},
    {"The Less I Know The Better", "Tame Impala", 2015},
    {"Edge Of The Earth", "30 Seconds To Mars", 2002},
    {"Song 2", "Blur", 1997},
    {"The People That We Love", "Bush", 2001},
    {"Feel Good Inc", "Gorillaz", 2005},
    {"The Trooper", "Iron Maiden", 1983},
    {"Broken Promises", "Element Eighty", 2003}
};