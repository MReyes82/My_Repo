#pragma once

#include <stdbool.h>

#define null NULL

typedef enum
{
    HEAP_MINIMO,
    HEAP_MAXIMO

} TipoDeHeap;

typedef struct Archivo
{
    char* nombre;
    short int paginas;

} Archivo;

typedef struct Nodo // ahora es un nodo de arbol binario
{
    Archivo* documento;
    //struct Nodo* siguiente;
    struct Nodo* izquierda;
    struct Nodo* derecha;

} Nodo;

typedef struct Heap
{
    Nodo* raiz; // referencia al nodo raiz para funciones como recorridos
    Nodo** nodos; // arreglo de referencias de nodos para funciones como heapify

    int cantidadNodos;
    short int capacidad; // tamaño maximo del heap, si es -1 no tiene limite
    TipoDeHeap tipo;

} Heap;

//* Funciones para archivos
Archivo* crearDocumento(char* nombre, int numeroPaginas);
void imprimirDocumento(Archivo* doc, int iterador);
void procesarArchivo(Heap* mainHeap);

//* Funciones para nodos y arboles
Nodo* crearNodo(Archivo* doc);
void recorridoEnOrden(Nodo* raiz, int* iterador);
void insertarEnArbol(Nodo** raiz, Archivo* doc, TipoDeHeap prioridadActual);
void reconstruirArbol(Heap* mainHeap);

//* Funciones para el heap
Heap* crearHeap(int tamMaximo, TipoDeHeap tipoDeHeap);
void insertarNodo(Heap* mainHeap, Archivo* doc);
bool estaVacioHeap(Heap* h);
void heapifyArriba(Heap* mainHeap, int indice);
void heapifyAbajo(Heap* mainHeap, int indice);
Archivo* extraerMaxMin(Heap* mainHeap);
void eliminarEnPosicion(Heap* mainHeap);

//* Funciones auxiliares
int padre(int i);
int izquierdo(int i);
int derecho(int i);
void swapNodos(Nodo** nodoA, Nodo** nodoB);
void cambiarPrioridad(Heap* heap, TipoDeHeap nuevoTipo);
void imprimirColaImpresion(Heap* mainHeap);

//* Funciones de liberacion de memoria
void liberarHeap(Heap* mainHeap);
void borrarArbol(Nodo* raiz);
