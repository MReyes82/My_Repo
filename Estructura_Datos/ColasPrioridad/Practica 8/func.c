#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// archivos
Archivo* crearDocumento(char* nombre, int numeroPaginas)
{
    Archivo* doc = malloc(sizeof(Archivo));
    doc->nombre = nombre;
    doc->paginas = numeroPaginas;

    return doc;
}

void imprimirDocumento(Archivo* doc)
{
    printf("Nombre: %s - Paginas: %d\n", doc->nombre, doc->paginas);
    
    return;
}

Nodo* crearNodo(Archivo* doc)
{
    Nodo* nodo = malloc(sizeof(Nodo));
    nodo->documento = doc;
    nodo->siguiente = null;

    return nodo;
}
// cola archivos
ColaArchivos* crearColaArchivos(int paginasDeLosArchivos)
{
    ColaArchivos* colaArchivos = malloc(sizeof(ColaArchivos));
    colaArchivos->inicio = null;
    colaArchivos->fin = null;
    colaArchivos->cantidadArchivos = 0;
    colaArchivos->paginasDeLosArchivos = paginasDeLosArchivos; // paginas que tendran los archivos de esta cola

    return colaArchivos;
}

void encolarArchivo(ColaArchivos* colaArchivos, Archivo* doc)
{
    Nodo* nodo = crearNodo(doc);

    if (estaVacia(colaArchivos))
    {
        colaArchivos->inicio = nodo;
        colaArchivos->fin = nodo;

        return;
    }

    colaArchivos->fin->siguiente = nodo;
    colaArchivos->fin = nodo;

    colaArchivos->cantidadArchivos++;

    return; 
}

Archivo* desencolarArchivo(ColaArchivos* colaArchivos)
{
    if (estaVacia(colaArchivos))
    { return null; }

    Nodo* nodoOut = colaArchivos->inicio;
    Archivo* doc = nodoOut->documento;

    colaArchivos->inicio = colaArchivos->inicio->siguiente;

    if (estaVacia(colaArchivos))
    { colaArchivos->fin = null; }

    free(nodoOut);

    colaArchivos->cantidadArchivos--;

    return doc;
}

bool estaVacia(ColaArchivos* colaArchivos)
{
    //return (colaArchivos->cantidadArchivos == 0);
    return (colaArchivos->inicio == null);
}

int obtenerNumeroDocumentos(ColaArchivos* colaDeDocumentos)
{
    if (estaVacia(colaDeDocumentos))
    { return 0; }

    return colaDeDocumentos->cantidadArchivos;
}

Archivo* desencolarArchivoPrioridad(ColaImpresion* colaPrincipal, int prioridad)
{
    return null;
}

void encolarArchivoPrioridad(ColaImpresion* colaPrincipal, Archivo* doc, int prioridad)
{
    ColaArchivos* colaActual = colaPrincipal->inicio;
    ColaArchivos* colaAnterior = null;

    while (colaActual != null && ((prioridad == _MIN_ && colaActual->paginasDeLosArchivos < doc->paginas) || (prioridad == _MAX_ && colaActual->paginasDeLosArchivos > doc->paginas)))
    {
        colaAnterior = colaActual;
        colaActual = colaActual->siguiente;
    }

    if (colaActual == null || colaActual->paginasDeLosArchivos != doc->paginas)
    {
        ColaArchivos* nuevaCola = crearColaArchivos(doc->paginas);
        
        if (colaAnterior == null)
        {
            nuevaCola->siguiente = colaPrincipal->inicio;
            colaPrincipal->inicio = nuevaCola;
        }
        else
        {
            nuevaCola->siguiente = colaActual->siguiente;
            colaAnterior->siguiente = nuevaCola;
        }

        colaActual = nuevaCola;
    }

    encolarArchivo(colaActual, doc);

    return;
}

void imprimirColaArchivos(ColaArchivos* colaArchivos)
{
    if (estaVacia(colaArchivos))
    { return; }

    ColaArchivos* auxiliar = crearColaArchivos(colaArchivos->paginasDeLosArchivos);

    while (!estaVacia(colaArchivos)) // vaciamos la cola principal para imprimir los elementos
    {
        Archivo* doc = desencolarArchivo(colaArchivos);
        imprimirDocumento(doc);
        encolarArchivo(auxiliar, doc);
    }

    while (!estaVacia(auxiliar)) // regresamos a la cola principal
    {
        Archivo* doc = desencolarArchivo(auxiliar);
        encolarArchivo(colaArchivos, doc);
    }

    free(auxiliar);

    return;
}

// cola impresion
void imprimirColaImpresion(ColaImpresion* colaImpresion)
{
    if (colaImpresion->inicio == null)
    { 
        printf("\nNo hay archivos en la cola de impresion.\n");
        return; 
    }

    ColaArchivos* colaActual = colaImpresion->inicio;

    while (colaActual != null)
    {
        imprimirColaArchivos(colaActual);
        colaActual = colaActual->siguiente;
    }
    
    return;
}

ColaImpresion crearColaImpresion(int tipoDePrioridad)
{
    ColaImpresion colaImpresion;
    colaImpresion.inicio = null;
    colaImpresion.fin = null;
    colaImpresion.cantidadColas = 0;
    colaImpresion.tipoDePrioridad = tipoDePrioridad;
    
    return colaImpresion;
}

void vaciarColaImpresion(ColaImpresion* colaImpresion)
{
    if (estaVacia(colaImpresion->inicio))
    { return; }

    ColaArchivos* colaActual = colaImpresion->inicio;
    ColaArchivos* colaSiguiente = null;

    while (colaActual != null)
    {
        colaSiguiente = colaActual->siguiente;
        free(colaActual);
        colaActual = colaSiguiente;
    }

    return;
}   

void cambiarPrioridad(ColaImpresion* colaImpresion, int prioridad)
{

}  