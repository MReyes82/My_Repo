#pragma once

#include <stdbool.h>

#define null NULL
#define _MIN_ 0
#define _MAX_ 1

typedef struct Archivo
{
    char* nombre;
    short int paginas;

} Archivo;

typedef struct Nodo // ahora es un nodo de arbol binario,
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

    short int tamMaximo; // tamaño maximo del heap, si es -1 no tiene limite
    short int tipoDeHeap;

} Heap;