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
// recibe el apuntador a la cola correcta a insertar el archivo y el archivo a insertar
void encolarArchivo(ColaArchivos* colaArchivos, Archivo* doc) 
{                                                                                  
    Nodo* nuevo = crearNodo(doc);

    if (colaArchivos->inicio == null)
    {
        colaArchivos->inicio = nuevo;
        colaArchivos->fin = nuevo;
    }
    else
    {
        colaArchivos->fin->siguiente = nuevo;
        colaArchivos->fin = nuevo;
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

    if (prioridad == _MIN_)
    {
        colaActual = colaPrincipal->inicio;

    }else if (prioridad == _MAX_) {
        colaActual = colaPrincipal->fin;

    }else {
        printf("\nPrioridad no valida.\n");
        return null;
    }

    while (colaActual != null && ((prioridad == 0 && colaActual->inicio == null) 
                                || (prioridad == 1 && colaActual->fin == null))) {
        colaAnterior = colaActual;
        if (prioridad == _MIN_)
        { colaActual = colaActual->siguiente; }

        else if (prioridad == _MAX_)
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

    while (colaActual != null && ((prioridad == _MIN_ && doc->paginas <= colaActual->paginasDeLosArchivos)  
                                  || (prioridad == _MAX_ && doc->paginas >= colaActual->paginasDeLosArchivos))) {
        //colaAnterior = colaActual;
        colaActual = colaActual->siguiente;
    }

    if (colaActual == null)
    {
        colaActual = crearColaArchivos(doc->paginas);
        //colaPrincipal->cantidadColas++;

        colaActual->siguiente = null;

        if (colaPrincipal->inicio == null)
        {
            colaPrincipal->inicio = colaActual;
            colaPrincipal->fin = colaActual;
        }
        else
        {
            if (prioridad == _MIN_)
            {
                colaPrincipal->fin->siguiente = colaActual;
                colaPrincipal->fin = colaActual;
            }
            else if (prioridad == _MAX_)
            {
                colaActual->siguiente = colaPrincipal->inicio;
                colaPrincipal->inicio = colaActual;
            }
        }
    }

    encolarArchivo(colaActual, doc);
    colaPrincipal->cantidadColas++;

    return;
}

void imprimirColaArchivos(ColaArchivos* colaArchivos, int* iterador)
{
    if (estaVacia(colaArchivos))
    { return; }

    ColaArchivos* auxiliar = crearColaArchivos(colaArchivos->paginasDeLosArchivos);

    while (!estaVacia(colaArchivos)) // vaciamos la cola principal para imprimir los elementos
    {
        Archivo* doc = desencolarArchivo(colaArchivos);
        imprimirDocumento(doc, (*iterador));
        encolarArchivo(auxiliar, doc);
        (*iterador)++;
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

    int i = 1;
    while (colaActual != null)
    {
        printf("\n---Archivos de {%d} paginas:---\n", colaActual->paginasDeLosArchivos);
        imprimirColaArchivos(colaActual, &i);
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

void cambiarPrioridad(ColaImpresion* colaImpresion, int* prioridad)
{
    if (colaImpresion->inicio == null)
    { return; }

    int prioridadAnterior = colaImpresion->tipoDePrioridad;

    // cambiamos la prioridad   
    if (*prioridad == _MIN_)
    { 
        *prioridad = _MAX_;
        colaImpresion->tipoDePrioridad = _MAX_;
    }
    else if (*prioridad == _MAX_)
    {
        *prioridad = _MIN_;
        colaImpresion->tipoDePrioridad = _MIN_;
    }
    // vaciamos a la cola auxiliar 
    Archivo* tmp = null;
    ColaImpresion auxiliar = crearColaImpresion(*prioridad);

    do
    {
        tmp = procesarArchivoPrioridad(colaImpresion, prioridadAnterior);

        if (tmp == null)
        { break; }

        encolarArchivoPrioridad(&auxiliar, tmp, *prioridad);

    }  while (tmp != null);

    // regresamos a la cola prinicpal, ya ordenado con la nueva prioridad.
    tmp = null;
    do 
    {
        tmp = procesarArchivoPrioridad(&auxiliar, *prioridad);

        if (tmp == null)
        { break; }

        encolarArchivoPrioridad(colaImpresion, tmp, *prioridad);

    }  while (tmp != null);
    
    return;
}  