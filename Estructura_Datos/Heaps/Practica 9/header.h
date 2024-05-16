#pragma once

#include <stdbool.h>

#define null NULL
#define _MIN_ 0
#define _MAX_ 1

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

Archivo* crearDocumento(char* nombre, int numeroPaginas);
void imprimirDocumento(Archivo* doc, int iterador);
Nodo* crearNodo(Archivo* doc);
Heap* crearHeap(int tamMaximo, TipoDeHeap tipoDeHeap);
void recorridoEnOrden(Nodo* raiz, int* iterador);
void imprimirColaImpresion(Heap* mainHeap);
int nodoPadre(Heap* heap, int indice);
void realojarMemoria(Heap* heap);
void filtrar(Heap* mainHeap, int indice);
void insertar(Heap* mainHeap, Archivo* doc);
Nodo* extraer(Heap* mainHeap);
void liberarNodos(Nodo* raiz);
void liberarHeap(Heap* mainHeap);
void construirHeap(Heap* mainHeap);