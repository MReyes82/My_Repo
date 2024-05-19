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
    printf("[%d] Nombre: %s | Paginas: %d\n", iterador, doc->nombre, doc->paginas);

    return;
}

void procesarArchivo(Heap* mainHeap)
{
    if (mainHeap->cantidadNodos == 0)
    {
        printf("No hay archivos para procesar.\n");
        return;
    }

    Archivo* archivo = extraerMaxMin(mainHeap);

    printf("Archivo procesado: \n");
    imprimirDocumento(archivo, 0);

    free(archivo->nombre);
    free(archivo);

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

void insertarEnArbol(Nodo** raiz, Archivo* doc, TipoDeHeap prioridadActual)
{
    if (*raiz == null)
    {
        *raiz = crearNodo(doc);
    }
    else
    {   
        Nodo* actual = *raiz;
        if (prioridadActual == HEAP_MINIMO) 
        {   // * Algoritmo de inserción normal. Se ordena en base a la cantidad de paginas.
            if (doc->paginas < actual->documento->paginas)
            {   
                insertarEnArbol(&actual->izquierda, doc, prioridadActual);
            }
            else
            {
                insertarEnArbol(&actual->derecha, doc, prioridadActual);
            }
        }
        else if (prioridadActual == HEAP_MAXIMO)
        {
            if (doc->paginas > actual->documento->paginas)
            {
                insertarEnArbol(&actual->izquierda, doc, prioridadActual);
            }
            else
            {
                insertarEnArbol(&actual->derecha, doc, prioridadActual);
            }
        }
    }
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

    mainHeap->nodos[mainHeap->cantidadNodos] = nuevo; //* la ultima posicion sera el nuevo nodo.
    //* re-ordenar
    heapifyArriba(mainHeap, mainHeap->cantidadNodos);
    insertarEnArbol(&mainHeap->raiz, nuevo->documento, mainHeap->tipo);

    mainHeap->cantidadNodos++;

    return;   
}

bool estaVacioHeap(Heap* h)
{
    return (h->cantidadNodos == 0);
}


//* Ajustar el heap desde un nodo dado hacia arriba.
void heapifyArriba(Heap* mainHeap, int indice)
{
    if (indice == 0) 
    {
        return;
    }

    int indicePadre = padre(indice);

    /*
    * Si el heap es minimo y el nodo actual es menor que su padre,
    * o si el heap es un maximo y el nodo actual es mayor que si padre,
    * intercambiamos el nodo actual con su padre y recursivamente
    * seguimos ajustando hacia arrbia.
    */
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

//* Ajustar el heap desde un nodo dado hacia abajo.
void heapifyAbajo(Heap* mainHeap, int indice)
{
    int indiceIzquierdo = izquierdo(indice); //* Indice del hijo izquierdo
    int indiceDerecho = derecho(indice); //* Indice del hijo derecho
    int indiceExtremo = indice; //* Indice del nodo mas extremo (nodo raiz)

    /*
    * Si el heap es minimo y el hijo izquierdo es menor que el nodo actual,
    * o si el heap es maximo y el hijo izquierdo es mayor que el nodo actual,
    * el nodo mas extremo sera el hijo izquierdo.
    */
    if (
        indiceIzquierdo < mainHeap->cantidadNodos
        && 
        (
            (mainHeap->tipo == HEAP_MINIMO && mainHeap->nodos[indiceIzquierdo]->documento->paginas < mainHeap->nodos[indiceExtremo]->documento->paginas)
            ||
            (mainHeap->tipo == HEAP_MAXIMO && mainHeap->nodos[indiceIzquierdo]->documento->paginas > mainHeap->nodos[indiceExtremo]->documento->paginas)
        )
    ){
        indiceExtremo = indiceIzquierdo; //* El hijo izquierdo sera el mas extremo.
    }

    /*
    * Si el heap es minimo y el hijo derecho es menor que el nodo actual,
    * o si el heap es maximo y el hijo derecho es mayor que el nodo actual,
    * el nodo mas extremo sera el hijo derecho.
    */
    if (
        indiceDerecho < mainHeap->cantidadNodos
        &&
        (
            (mainHeap->tipo == HEAP_MINIMO && mainHeap->nodos[indiceDerecho]->documento->paginas < mainHeap->nodos[indiceExtremo]->documento->paginas)
            ||
            (mainHeap->tipo == HEAP_MAXIMO && mainHeap->nodos[indiceDerecho]->documento->paginas > mainHeap->nodos[indiceExtremo]->documento->paginas)
        )
    ){
        indiceExtremo = indiceDerecho; //* El hijo derecho sera el mas extremo.
    }

    if (indiceExtremo != indice) //* Si el nodo mas extremo no es el nodo actual.
    {
        swapNodos(&mainHeap->nodos[indice], &mainHeap->nodos[indiceExtremo]); //* Intercambiamos el nodo actual con el mas extremo.
        heapifyAbajo(mainHeap, indiceExtremo); //* Recursivamente seguimos ajustando hacia abajo.
    }

    return;
}

Archivo* extraerMaxMin(Heap* mainHeap)
{
    if (estaVacioHeap(mainHeap))
    {
        printf("Heap vacio\n.");
        return null;
    }

    Nodo* raiz = mainHeap->nodos[0];
    Nodo* ultimo = mainHeap->nodos[mainHeap->cantidadNodos - 1];

    mainHeap->nodos[0] = ultimo;
    mainHeap->cantidadNodos--;

    //* Re-ordenamos y reconstruimos el arbol.
    heapifyAbajo(mainHeap, 0);
    reconstruirArbol(mainHeap);

    Archivo* doc = raiz->documento;
    free(raiz);

    return doc;
}

void eliminarEnPosicion(Heap* mainHeap)
{
    if (mainHeap->cantidadNodos == 0)
    {
        return;
    }

    int posicion;
    imprimirColaImpresion(mainHeap);
    printf("\nElige el archivo a eliminar > ");
    scanf("%d", &posicion);

    if (posicion < 0 || posicion >= mainHeap->cantidadNodos)
    {
        return;
    }

    Nodo* raiz = mainHeap->nodos[posicion]; //* apuntador al nodo a eliminar
    Nodo* ultimo = mainHeap->nodos[mainHeap->cantidadNodos - 1]; //* apuntador al ultimo nodo

    mainHeap->nodos[posicion] = ultimo; //* reemplazamos el nodo eliminado con el ultimo nodo
    mainHeap->cantidadNodos--; 

    heapifyAbajo(mainHeap, posicion); //* ajustamos el heap hacia abajo
    reconstruirArbol(mainHeap);

    printf("Archivo eliminado: \n");
    imprimirDocumento(raiz->documento, 0);
    free(raiz->documento->nombre); //* liberamos la memoria del documento
    free(raiz->documento);

    return;
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
    printf("Reconstruyendo arbol\n");
    reconstruirArbol(heap);
    printf("Arbol reconstruido\n");

    return;
}

void imprimirColaImpresion(Heap* mainHeap)
{
    int i;
    for (i = 0 ; i < mainHeap->cantidadNodos ; i++)
    {
        imprimirDocumento(mainHeap->nodos[i]->documento, i);
    }
    
    printf("\n------Heap binario------\n");
    i = 0;
    recorridoEnOrden(mainHeap->raiz, &i);
    
    return;
}

void reconstruirArbol(Heap* mainHeap)
{
    borrarArbol(mainHeap->raiz);
    mainHeap->raiz = null;

    for (int i = 0 ; i < mainHeap->cantidadNodos ; i++)
    {
        insertarEnArbol(&mainHeap->raiz, mainHeap->nodos[i]->documento, mainHeap->tipo);
    }

    return;
}

//* Funciones de liberacion de memoria
void liberarHeap(Heap* mainHeap)
{
    for (int i = 0 ; i < mainHeap->cantidadNodos ; i++)
    {
        free(mainHeap->nodos[i]->documento->nombre);
        //printf("String %d liberado\n", i);
        free(mainHeap->nodos[i]->documento);
        //printf("Apuntador documento %d liberado\n", i);
        free(mainHeap->nodos[i]);
        //printf("Apuntador nodo %d liberado\n", i);
    }
    
    liberarMemoriaArbol(mainHeap->raiz);
    mainHeap->raiz = null;
    mainHeap->cantidadNodos = 0;

    return;
}

void borrarArbol(Nodo* raiz)
{
    if (raiz != null)
    {
        borrarArbol(raiz->izquierda);
        borrarArbol(raiz->derecha);
        free(raiz);
    }

    return;
}

void liberarMemoriaArbol(Nodo* raiz)
{
    if (raiz != null)
    {
        liberarMemoriaArbol(raiz->izquierda);
        liberarMemoriaArbol(raiz->derecha);
        free(raiz->documento->nombre);
        free(raiz->documento);
        //free(raiz);
    }

    return;
}


