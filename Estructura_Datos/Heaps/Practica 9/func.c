#include "header.h"
#include <stdio.h>
#include <stdlib.h>

Archivo* crearDocumento(char* nombre, int numeroPaginas)
{
    Archivo* nuevo = malloc(sizeof(Archivo));
    nuevo->nombre = nombre;
    nuevo->paginas = numeroPaginas;

    return nuevo;
}

void imprimirDocumento(Archivo* doc, int iterador)
{
    printf(
    "[%d] Nombre: %s | Paginas: %d\n", 
    doc->nombre, doc->paginas
    );

    return;
}

Nodo* crearNodo(Archivo* doc)
{
    Nodo* nuevo = malloc(sizeof(Nodo));
    nuevo->documento = doc;
    nuevo->izquierda = null;
    nuevo->derecha = null;

    return nuevo;
}

Heap* crearHeap(int tamMaximo, TipoDeHeap tipoDeHeap)
{   // * asume que se le pasa un valor positivo mayor que 0 como tamMaximo.
    Heap* nuevo = malloc(sizeof(Heap));
    nuevo->raiz = null;

    nuevo->nodos = malloc(sizeof(Nodo*) * tamMaximo);

    nuevo->cantidadNodos = 0;
    nuevo->capacidad = tamMaximo;
    nuevo->tipo = tipoDeHeap;

    return nuevo;
}

void recorridoEnOrden(Nodo* raiz, int* iterador)
{   // * asume que se le pasa "0" como parametro incial del iterador.
    if (raiz != null)
    {
        recorridoEnOrden(raiz->izquierda, iterador);

        imprimirDocumento(raiz->documento, iterador);
        (*iterador)++;

        recorridoEnOrden(raiz->derecha, iterador);
    }
}

void imprimirColaImpresion(Heap* mainHeap)
{
    int i = 0;
    recorridoEnOrden(mainHeap->raiz, &i);

    return;
}

int nodoPadre(Heap* heap, int indice)
{
    if (indice <= 0 || indice >= heap->cantidadNodos)
        return -1; // * no tiene padre (raiz o fuera de rango)

    return (indice - 1) / 2;
}

int nodoIzquierdo(Heap* heap, int indice)
{
    int izquierdo = 2 * indice + 1;

    if (izquierdo >= heap->cantidadNodos)
        return -1; // * no tiene hijo izquierdo

    return izquierdo;
}

int nodoDerecho(Heap* heap, int indice)
{
    int derecho = 2 * indice + 2;

    if (derecho >= heap->cantidadNodos)
        return -1; // * no tiene hijo derecho

    return derecho;
}

void realojarMemoria(Heap* heap)
{
    Nodo** referencias = heap->nodos;

    heap->nodos = malloc(sizeof(Nodo*) * heap->capacidad * 2);

    for (int i = 0; i < heap->capacidad; i++)
    {
        heap->nodos[i] = referencias[i];
    }
    heap->cantidadNodos *= 2;

    free(referencias);

    return;
}

