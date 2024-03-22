#pragma once

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

} Cola;

void desplegarReproduccion(Cola* colaReproduccion);
Cancion* dequeue(Cola *cola, int posicion);
void enqueue(Cola* cola, Cancion* cancion, int posicion);
void inicializarCola(Cola* cola);
Elemento* alojarElemento(Cancion* cancion);
//Cancion* crearCancion(char* nombre, char* autor, int fecha);
void mostrarColaReproduccion(Cola* cola);
int mostrarPlaylist(void);

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