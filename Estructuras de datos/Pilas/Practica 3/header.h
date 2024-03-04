#pragma once

typedef struct Libro
{
    char nombre[50];
    char genero[50];
    int releaseDate;

} Libro;

typedef struct Elemento
{
    Libro *elementoLibro;
    struct Elemento *sig;

} Elemento;

typedef struct Pila
{
    Elemento *cima;
    int longitud;
    int numElementos;

} Pila;

typedef struct StackArray
{
    Pila *stackLibros;
    int numStacks;

} StackArray;

Elemento *alojarElemento(Libro *input);
Pila* inicializarCaja(void);
void inicializarPila(Pila *stackLibro,int longitud);
void imprimirPila(Pila *stackLibro);
int llena(Pila stackLibro);
int vacia(Pila stackLibro);
void push(Pila *stackLibro, Libro *nuevo);
Libro *pop(Pila *stackLibro);
void vaciarPila(Pila *stackLibro);
void apilarPorGenero(StackArray *elementoArray, Libro *elementoLibro, char *genero);
void apilarPorFecha(StackArray *elementoArray, Libro *elementoLibro, int releaseDate);
char *submenuApilarPorGenero(void);
int submenuApilarPorFecha(void);