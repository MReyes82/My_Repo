#include "header.h"
#include <stdio.h>
#include <stdlib.h>


//* Funciones para archivos
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
    iterador, doc->nombre, doc->paginas
    );

    return;
}

//* Funciones para nodos y arboles
Nodo* crearNodo(Archivo* doc)
{
    Nodo* nuevo = malloc(sizeof(Nodo));
    
    nuevo->documento = doc;
    nuevo->izquierda = null;
    nuevo->derecha = null;

    return nuevo;
}

void recorridoEnOrden(Nodo* raiz, int* iterador)
{   // * asume que se le pasa "0" como parametro incial del iterador.
    if (raiz != null)
    {
        recorridoEnOrden(raiz->izquierda, iterador);

        imprimirDocumento(raiz->documento, *iterador);
        (*iterador)++;

        recorridoEnOrden(raiz->derecha, iterador);
    }
}

void insertarEnArbol(Nodo** raiz, Nodo* nuevo, TipoDeHeap prioridadActual)
{
    if (*raiz == null)
    {
        *raiz = nuevo;
    }
    else
    {
        Nodo* actual = *raiz;

        if (nuevo->documento->paginas < actual->documento->paginas)
        {
            insertarEnArbol(&actual->izquierda, nuevo, prioridadActual);
        }
        else
        {
            insertarEnArbol(&actual->derecha, nuevo, prioridadActual);
        }
    }
    /*
    if (prioridadActual == HEAP_MINIMO)
    {
        if (nuevo->documento->paginas < actual->documento->paginas)
        {
            insertarEnArbol(&actual->izquierda, nuevo, prioridadActual);
        }
        else
        {
            insertarEnArbol(&actual->derecha, nuevo, prioridadActual);
        }
    }
    else if (prioridadActual == HEAP_MAXIMO)
    {
        if (nuevo->documento->paginas > actual->documento->paginas)
        {
            insertarEnArbol(&actual->izquierda, nuevo, prioridadActual);
        }
        else
        {
            insertarEnArbol(&actual->derecha, nuevo, prioridadActual);
        }
    }
    */
}

//* Funciones para el heap
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

void insertarNodo(Heap* mainHeap, Archivo* doc)
{
    if (mainHeap->cantidadNodos == mainHeap->capacidad)
    {
        return;
    }

    Nodo* nuevo = crearNodo(doc);

    mainHeap->nodos[mainHeap->cantidadNodos] = nuevo;
    //* re-ordenar
    heapifyArriba(mainHeap, mainHeap->cantidadNodos);
    insertarEnArbol(&mainHeap->raiz, nuevo, mainHeap->tipo);

    mainHeap->cantidadNodos++;

    return;   
}

bool estaVacioHeap(Heap* h)
{
    return (h->cantidadNodos == 0);
}

void heapifyArriba(Heap* mainHeap, int indice)
{
    if (indice == 0)
    {
        return;
    }

    int indicePadre = padre(indice);

    if (
        (mainHeap->tipo == HEAP_MINIMO && mainHeap->nodos[indice]->documento->paginas < mainHeap->nodos[indicePadre]->documento->paginas) 
        ||
        (mainHeap->tipo == HEAP_MAXIMO && mainHeap->nodos[indice]->documento->paginas > mainHeap->nodos[indicePadre]->documento->paginas)
    ){
        swapNodos(&mainHeap->nodos[indice], &mainHeap->nodos[indicePadre]);
        heapifyArriba(mainHeap, indicePadre);
    }

    return;
}

void heapifyAbajo(Heap* mainHeap, int indice)
{
    int indiceIzquierdo = izquierdo(indice);
    int indiceDerecho = derecho(indice);
    int indiceExtremo = indice;

    if (
        indiceIzquierdo < mainHeap->cantidadNodos
        && 
        (
            (mainHeap->tipo == HEAP_MINIMO && mainHeap->nodos[indiceIzquierdo]->documento->paginas < mainHeap->nodos[indiceExtremo]->documento->paginas)
            ||
            (mainHeap->tipo == HEAP_MAXIMO && mainHeap->nodos[indiceIzquierdo]->documento->paginas > mainHeap->nodos[indiceExtremo]->documento->paginas)
        )
    ){
        indiceExtremo = indiceIzquierdo;
    }

    if (
        indiceDerecho < mainHeap->cantidadNodos
        &&
        (
            (mainHeap->tipo == HEAP_MINIMO && mainHeap->nodos[indiceDerecho]->documento->paginas < mainHeap->nodos[indiceExtremo]->documento->paginas)
            ||
            (mainHeap->tipo == HEAP_MAXIMO && mainHeap->nodos[indiceDerecho]->documento->paginas > mainHeap->nodos[indiceExtremo]->documento->paginas)
        )
    ){
        indiceExtremo = indiceDerecho;
    }

    if (indiceExtremo != indice)
    {
        swapNodos(&mainHeap->nodos[indice], &mainHeap->nodos[indiceExtremo]);
        heapifyAbajo(mainHeap, indiceExtremo);
    }

    return;
}

//void realojarMemoria(Heap* heap);
void insertar(Heap* mainHeap, Archivo* doc)
{

}

Archivo* extraerMaxMin(Heap* mainHeap)
{
    if (estaVacioHeap(mainHeap))
    {
        printf("Regresa nulo por estar vacio.");
        return null;
    }

    Nodo* raiz = mainHeap->nodos[0];
    Nodo* ultimo = mainHeap->nodos[mainHeap->cantidadNodos - 1];

    mainHeap->nodos[0] = ultimo;
    mainHeap->cantidadNodos--;

    heapifyAbajo(mainHeap, 0);

    Archivo* doc = raiz->documento;

    free(raiz);

    return doc;
}

//* Funciones auxiliares
int padre(int i)
{
    return (i - 1) / 2;    
}

int izquierdo(int i)
{
    return 2 * i + 1;
}

int derecho(int i)
{
    return 2 * i + 2; 
}

void swapNodos(Nodo** nodoA, Nodo** nodoB)
{
    Nodo* temp = *nodoA;
    *nodoA = *nodoB;
    *nodoB = temp;

    return;
}

void cambiarPrioridad(Heap* heap, TipoDeHeap nuevoTipo)
{
    if (heap->tipo == nuevoTipo)
    {
        return;
    }

    heap->tipo = nuevoTipo;

    int i;
    for (i = heap->cantidadNodos / 2 - 1 ; i >= 0 ; i--)
    {
        heapifyAbajo(heap, i);
    }

    for (i = 0 ; i < heap->cantidadNodos ; i++)
    {
        insertarEnArbol(&heap->raiz, heap->nodos[i], heap->tipo);
    }

    return;
}

void imprimirColaImpresion(Heap* mainHeap)
{
    int i;
    for (i = 0 ; i < mainHeap->cantidadNodos ; i++)
    {
        imprimirDocumento(mainHeap->nodos[i]->documento, i);
    }

    printf("------Heap binario------\n");
    i = 0;
    recorridoEnOrden(mainHeap->raiz, &i);

    return;
}

//* Funciones de liberacion de memoria
void liberarHeap(Heap* mainHeap)
{
    for (int i = 0 ; i < mainHeap->cantidadNodos ; i++)
    {
        free(mainHeap->nodos[i]->documento->nombre);
        free(mainHeap->nodos[i]->documento);
        free(mainHeap->nodos[i]);
    }

    mainHeap->cantidadNodos = 0;
    mainHeap->raiz = null;

    return;
}
/*
void liberarNodos(Nodo* raiz);
void freeNodo(Nodo* node);
*/



