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

    if (estaVacio(colaArchivos))
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
    if (estaVacio(colaArchivos)) // si la cola esta vacia, regresamos nulo
    { return null; }

    Nodo* nodoOut = colaArchivos->inicio; // nodo a desencolar es el del inicio
    Archivo* doc = nodoOut->documento;    // por defecto, el nodo a desencolar es el de mayor prioridad

    colaArchivos->inicio = colaArchivos->inicio->siguiente; // el inicio sera el siguiente nodo del nodo a eliminar
    free(nodoOut); // liberamos el nodo a eliminar

    if (colaArchivos->inicio == null) // si se vacia la cola, actualizamos el apuntador de fin
    { colaArchivos->fin = null; }    // para que apunte a nulo

    colaArchivos->cantidadArchivos--;

    return doc;
}
// tal vez se borra
bool estaVacio(ColaArchivos* colaArchivos)
{
    //return (colaArchivos->cantidadArchivos == 0);
    return (colaArchivos->inicio == null);
}
// tal vez se borra
int obtenerNumeroDocumentos(ColaArchivos* colaDeDocumentos)
{
    if (estaVacio(colaDeDocumentos))
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

    ColaArchivos* colaActual = desencolarColaArchivos(colaPrincipal);

    if (colaActual == null)
    {
        return null;
    }

    Archivo* archivoOut = desencolarArchivo(colaActual);

    if (archivoOut == null)
    {
        return null;
    }

    if (!estaVacio(colaActual)) // si la cola no queda vacia tras sacar el archivo de mayor prioridad
    {                           // la regresamos a la cola impresion
        encolarColaArchivos(colaPrincipal, colaActual, prioridad);
    }

    return archivoOut;
}

void encolarColaArchivos(ColaImpresion* colaPrincipal, ColaArchivos* colaActual, int prioridad)
{
    if (colaPrincipal == null || colaActual == null)
    {
        printf("\nApuntador nulo.\n");
        return;
    }

    if (colaPrincipal->inicio == null)
    {
        colaPrincipal->inicio = colaActual;
        colaPrincipal->fin = colaActual;
    }
    else
    {
        if (prioridad == _MIN_)
        {
            ColaArchivos* actual = colaPrincipal->inicio;
            ColaArchivos* anterior = null;

            while (actual != null && actual->paginasDeLosArchivos < colaActual->paginasDeLosArchivos)
            {
                anterior = actual;
                actual = actual->siguiente;
            }

            if (anterior == null)
            {
                colaActual->siguiente = colaPrincipal->inicio;
                colaPrincipal->inicio = colaActual;
            }
            else
            {
                colaActual->siguiente = anterior->siguiente;
                anterior->siguiente = colaActual;
            }
        }
        else if (prioridad == _MAX_)
        {
            ColaArchivos* actual = colaPrincipal->inicio;
            ColaArchivos* anterior = null;

            while (actual != null && actual->paginasDeLosArchivos > colaActual->paginasDeLosArchivos)
            {
                anterior = actual;
                actual = actual->siguiente;
            }

            if (anterior == null)
            {
                colaActual->siguiente = colaPrincipal->inicio;
                colaPrincipal->inicio = colaActual;
            }
            else
            {
                colaActual->siguiente = anterior->siguiente;
                anterior->siguiente = colaActual;
            }
        }
    }
    
    colaPrincipal->cantidadColas++;
}

ColaArchivos* desencolarColaArchivos(ColaImpresion* colaPrincipal)
{
    if (colaPrincipal == null)
    {
        printf("ERROR: cola de impresion no iniciada.\n");
        return null;
    }
    if (estaVacio(colaPrincipal->inicio))
    {
        printf("ERROR: cola vacia.\n");
        return null;
    }

    ColaArchivos* colaOut = colaPrincipal->inicio;
    colaPrincipal->inicio = colaPrincipal->inicio->siguiente;
    colaPrincipal->cantidadColas--;

    if (colaPrincipal->inicio == null)
    {
        colaPrincipal->fin = null;
    }

    return colaOut;
}

ColaArchivos* encontrarColaArchivos(ColaImpresion* colaImpresion, int paginas)
{
    if (colaImpresion == null)
    {
        printf("\nNo se ha creado la cola de impresion.\n");
        return null;
    }

    ColaArchivos* colaActual = colaImpresion->inicio;

    while (colaActual != null)
    {
        if (!estaVacio(colaActual) && colaActual->paginasDeLosArchivos == paginas)
        {
            return colaActual;
        }

        colaActual = colaActual->siguiente;
    }

    return null;
}

void encolarArchivoPrioridad(ColaImpresion* colaPrincipal, Archivo* doc, int prioridad)
{
    if (colaPrincipal == null || doc == null)
    {
        printf("\nApuntador nulo.\n");
        return;
    }

    ColaArchivos* colaDondeInsertar = encontrarColaArchivos(colaPrincipal, doc->paginas);
    // si no se encuentra una cola
    if (colaDondeInsertar == null)
    {
        colaDondeInsertar = crearColaArchivos(doc->paginas);
        encolarColaArchivos(colaPrincipal, colaDondeInsertar, prioridad);
    }
    encolarArchivo(colaDondeInsertar, doc);
    
    return;
}

void imprimirColaArchivos(ColaArchivos* colaArchivos, int* iterador)
{
    if (estaVacio(colaArchivos))
    { return; }

    ColaArchivos* auxiliar = crearColaArchivos(colaArchivos->paginasDeLosArchivos);

    while (!estaVacio(colaArchivos)) // vaciamos la cola principal para imprimir los elementos
    {
        Archivo* doc = desencolarArchivo(colaArchivos);
        imprimirDocumento(doc, (*iterador));
        encolarArchivo(auxiliar, doc);
        (*iterador)++;
    }

    while (!estaVacio(auxiliar)) // regresamos a la cola principal
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

void cambiarPrioridad(ColaImpresion* colaImpresion, int* prioridadNueva)
{
    if (colaImpresion->inicio == null)
    { return; }

    int prioridadAnterior = colaImpresion->tipoDePrioridad;

    // cambiamos la prioridad   
    if (prioridadAnterior == _MIN_)
    { 
        *prioridadNueva = _MAX_;
    }
    else if (prioridadAnterior == _MAX_)
    {
        *prioridadNueva = _MIN_;
    }
    // vaciamos a la cola auxiliar 
    Archivo* tmp = null;
    ColaImpresion auxiliar = crearColaImpresion(*prioridadNueva);

    tmp = procesarArchivoPrioridad(colaImpresion, prioridadAnterior);
    while (tmp != null)
    {
        encolarArchivoPrioridad(&auxiliar, tmp, *prioridadNueva);
        tmp = procesarArchivoPrioridad(colaImpresion, prioridadAnterior);
    }
    // regresamos a la cola prinicpal, ya ordenado con la nueva prioridad.
    tmp = procesarArchivoPrioridad(&auxiliar, *prioridadNueva);
    while (tmp != null)
    {
        encolarArchivoPrioridad(colaImpresion, tmp, *prioridadNueva);
        tmp = procesarArchivoPrioridad(&auxiliar, *prioridadNueva);
    }

    if (*prioridadNueva == _MIN_)
    {
        colaImpresion->tipoDePrioridad = _MIN_;
    }
    else if (*prioridadNueva == _MAX_)
    {
        colaImpresion->tipoDePrioridad = _MAX_;
    }

    return;
}  