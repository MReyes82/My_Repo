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

void filtrar(Heap* mainHeap, int indice)
{   
    int izquierdo, derecho, max;
    Nodo* temporal;

    izquierdo = nodoIzquierdo(mainHeap, indice);
    derecho = nodoDerecho(mainHeap, indice);

    if (izquierdo != -1 
        && mainHeap->nodos[izquierdo]->documento->paginas 
                                > 
           mainHeap->nodos[indice]->documento->paginas)
    {
        max = izquierdo;
    }
    else
    {
        max = indice;
    }

    if (
        derecho != -1 
        && mainHeap->nodos[derecho]->documento->paginas 
                                > 
           mainHeap->nodos[max]->documento->paginas
       ){
        max = derecho;
    }

    if (max != indice)
    {
        temporal = mainHeap->nodos[indice];
        mainHeap->nodos[indice] = mainHeap->nodos[max];
        mainHeap->nodos[max] = temporal;
    }

    filtrar(mainHeap, max);

    return;
}

void insertar(Heap* mainHeap, Archivo* doc)
{
    if (mainHeap->cantidadNodos >= mainHeap->capacidad)
    {
        realojarMemoria(mainHeap);
    }

    mainHeap->cantidadNodos++;
    int i = mainHeap->cantidadNodos - 1;

    int documentoNuevo = doc->paginas; 
    int documentoPadre = mainHeap->nodos[(i - 1) / 2]->documento->paginas;

    while (i >= 0 && documentoNuevo > documentoPadre)
    {
        mainHeap->nodos[i] = mainHeap->nodos[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    mainHeap->nodos[i] = crearNodo(doc);

    return;
}

Nodo* extraer(Heap* mainHeap)
{
    Nodo* nodoOut;

    if (mainHeap->cantidadNodos < 1)
    {
        return null;
    }

    nodoOut = mainHeap->nodos[0];
    mainHeap->nodos[0] = mainHeap->nodos[mainHeap->cantidadNodos - 1];
    mainHeap->cantidadNodos--;

    filtrar(mainHeap, 0);

    return nodoOut;
}

void liberarNodos(Nodo* raiz)
{
    if (raiz == null)
    {
        return;
    }

    liberarNodos(raiz->izquierda);
    liberarNodos(raiz->derecha);

    free(raiz->documento);
    free(raiz);

    return;
}

void liberarHeap(Heap* mainHeap)
{
    if (mainHeap == null)
    {
        return;
    }
    liberarNodos(mainHeap->raiz);
    free(mainHeap);
    mainHeap = null;

    return;
}