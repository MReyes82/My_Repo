#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// archivos
Archivo* crearDocumento(char* nombre, int numeroPaginas) 
{
    Archivo* nuevo = malloc(sizeof(Archivo));
    nuevo->nombre = nombre;
    nuevo->paginas = numeroPaginas;

    return nuevo;
}

void imprimirDocumento(Archivo* doc, int iterador)
{
    printf("[%d] Nombre: %s, Paginas: %d\n", iterador, doc->nombre, doc->paginas);
    
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
    colaArchivos->siguiente = null;
    colaArchivos->cantidadArchivos = 0;
    colaArchivos->paginasDeLosArchivos = paginasDeLosArchivos; // paginas que tendran los archivos de esta cola

    return colaArchivos;
}

void encolarArchivo(ColaArchivos* colaArchivos, Archivo* doc, int tipoDePrioridad) 
{                                                                                  
    Nodo* nuevo = crearNodo(doc);

    if (tipoDePrioridad == 0) // si es 0 de menor a mayor
    {

        if (colaArchivos->inicio == null) // si la cola esta vacia
        {
            colaArchivos->inicio = nuevo; // el inicio sera el nuevo nodo
            colaArchivos->fin = nuevo; // el fin sera el nuevo nodo tambien
        }
        else if (doc->paginas < colaArchivos->inicio->documento->paginas) // si el documento a encolar tiene menos 
        {                                                                // paginas que el primer documento de la cola
            nuevo->siguiente = colaArchivos->inicio;                    // el nuevo nodo sera el inicio
            colaArchivos->inicio = nuevo;
        }
        else // si no es el caso anterior, se recorre la cola hasta encontrar el lugar donde se debe insertar el nuevo nodo
        {
            Nodo* actual = colaArchivos->inicio;

            while (actual->siguiente != null && actual->siguiente->documento->paginas <= doc->paginas)
            { actual = actual->siguiente; }

            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;

            if (nuevo->siguiente == null)
            { colaArchivos->fin = nuevo; }
        }
    }
    else if (tipoDePrioridad == 1) // si prioridad es 1 se ordena de mayor a menor, 
    {
        if (colaArchivos->inicio == null)
        {
            colaArchivos->inicio = nuevo;
            colaArchivos->fin = nuevo;
        }
        else if (doc->paginas > colaArchivos->inicio->documento->paginas)
        {   
            nuevo->siguiente = colaArchivos->inicio;
            colaArchivos->inicio = nuevo;
        }
        else
        {
            Nodo* actual = colaArchivos->inicio;

            while (actual->siguiente != null && actual->siguiente->documento->paginas >= doc->paginas)
            { actual = actual->siguiente; }

            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;

            if (nuevo->siguiente == null)
            { colaArchivos->fin = nuevo; }
        }
    }

    colaArchivos->cantidadArchivos++;

    return; 
}

Archivo* desencolarArchivo(ColaArchivos* colaArchivos)
{
    if (colaArchivos->inicio == null) // si la cola esta vacia, regresamos nulo
    { return null; }

    Nodo* nodoOut = colaArchivos->inicio; // nodo a desencolar es el del inicio
    Archivo* doc = nodoOut->documento;    // por defecto, el nodo a desencolar es el de mayor prioridad

    colaArchivos->inicio = nodoOut->siguiente; // el inicio sera el siguiente nodo del nodo a eliminar
    free(nodoOut); // liberamos el nodo a eliminar

    if (colaArchivos->inicio == null) // si se vacia la cola, actualizamos el apuntador de fin
    { colaArchivos->fin = null; }    // para que apunte a nulo

    colaArchivos->cantidadArchivos--;

    return doc;
}
// tal vez se borra
bool estaVacia(ColaArchivos* colaArchivos)
{
    //return (colaArchivos->cantidadArchivos == 0);
    return (colaArchivos->inicio == null);
}
// tal vez se borra
int obtenerNumeroDocumentos(ColaArchivos* colaDeDocumentos)
{
    if (estaVacia(colaDeDocumentos))
    { return 0; }

    return colaDeDocumentos->cantidadArchivos;
}
// falta
Archivo* procesarArchivoPrioridad(ColaImpresion* colaPrincipal, int prioridad)
{
    if (colaPrincipal == null || colaPrincipal->inicio == null)
    {
        printf("\nNo hay archivos en la cola de impresion.\n");
        return null;
    }

    ColaArchivos* colaActual = null;
    ColaArchivos* colaAnterior = null;

    if (prioridad == 0)
    {
        colaActual = colaPrincipal->inicio;

    }else if (prioridad == 1) {
        colaActual = colaPrincipal->fin;

    }else {
        printf("\nPrioridad no valida.\n");
        return null;
    }

    while (colaActual != null && ((prioridad == 0 && colaActual->inicio == null) 
                                || (prioridad == 1 && colaActual->fin == null))) {
        colaAnterior = colaActual;
        if (prioridad == 0)
        { colaActual = colaActual->siguiente; }

        else if (prioridad == 1)
        { colaActual = colaAnterior; }
    }

    if (colaActual == null)
    {
        printf("\nNo hay archivos en la cola de impresion.\n");
        return null;
    }

    Archivo* archivoProcesado = desencolarArchivo(colaActual);

    if (colaActual->inicio == null)
    {
        if (colaAnterior == null)
        {
            colaPrincipal->inicio = colaActual->siguiente;
        }
        else
        {
            colaAnterior->siguiente = colaActual->siguiente;    
        }

        if (colaActual == colaPrincipal->fin)
        {
            colaPrincipal->fin = colaAnterior;
        }

        free(colaActual);
        colaPrincipal->cantidadColas--;
    }

    return archivoProcesado;
}

void encolarArchivoPrioridad(ColaImpresion* colaPrincipal, Archivo* doc, int prioridad)
{
    if (colaPrincipal == null)
    {
        printf("\nNo se ha creado la cola de impresion.\n");
        return;
    }

    ColaArchivos* colaActual = colaPrincipal->inicio;
    //ColaArchivos* colaAnterior = null;

    while (colaActual != null && ((prioridad == 0 && doc->paginas < colaActual->paginasDeLosArchivos)  
                                  || (prioridad == 1 && doc->paginas > colaActual->paginasDeLosArchivos))) {
        //colaAnterior = colaActual;
        colaActual = colaActual->siguiente;
    }

    if (colaActual == null)
    {
        colaActual = crearColaArchivos(doc->paginas);
        //colaActual->siguiente = null;

        if (colaPrincipal->inicio == null)
        {
            colaPrincipal->inicio = colaActual;
            colaPrincipal->fin = colaActual;
        }
        else
        {
            if (prioridad == 0)
            {
                colaPrincipal->fin->siguiente = colaActual;
                colaPrincipal->fin = colaActual;
            }
            else if (prioridad == 1)
            {
                colaActual->siguiente = colaPrincipal->inicio;
                colaPrincipal->inicio = colaActual;
            }
        }
    }

    encolarArchivo(colaActual, doc, prioridad);
    colaPrincipal->cantidadColas++;

    return;
}

void imprimirColaArchivos(ColaArchivos* colaArchivos, int tipoDePrioridad, int* iterador)
{
    if (estaVacia(colaArchivos))
    { return; }

    ColaArchivos* auxiliar = crearColaArchivos(colaArchivos->paginasDeLosArchivos);

    while (!estaVacia(colaArchivos)) // vaciamos la cola principal para imprimir los elementos
    {
        Archivo* doc = desencolarArchivo(colaArchivos);
        imprimirDocumento(doc, (*iterador));
        encolarArchivo(auxiliar, doc, tipoDePrioridad);
        (*iterador)++;
    }

    while (!estaVacia(auxiliar)) // regresamos a la cola principal
    {
        Archivo* doc = desencolarArchivo(auxiliar);
        encolarArchivo(colaArchivos, doc, tipoDePrioridad);
    }

    free(auxiliar);

    return;
}

// cola impresion
void imprimirColaImpresion(ColaImpresion* colaImpresion)
{ // falta
    if (colaImpresion->inicio == null)
    { 
        printf("\nNo hay archivos en la cola de impresion.\n");
        return; 
    }

    ColaArchivos* colaActual = colaImpresion->inicio;

    int i = 0;
    while (colaActual != null)
    {
        imprimirColaArchivos(colaActual, colaImpresion->tipoDePrioridad, &i);
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
// falta
void vaciarColaImpresion(ColaImpresion* colaImpresion)
{
    if (colaImpresion->inicio == null)
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
// falta
void cambiarPrioridad(ColaImpresion* colaImpresion, int prioridad)
{

}  