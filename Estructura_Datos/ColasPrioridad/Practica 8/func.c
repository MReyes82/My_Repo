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
    { 
        return null; 
    }

    Nodo* nodoOut = colaArchivos->inicio; // nodo a desencolar es el del inicio
    Archivo* doc = nodoOut->documento;    // por defecto, el nodo a desencolar es el de mayor prioridad

    colaArchivos->inicio = colaArchivos->inicio->siguiente; // el inicio sera el siguiente nodo del nodo a eliminar
    free(nodoOut); // liberamos el nodo a eliminar

    if (colaArchivos->inicio == null) // si se vacia la cola, actualizamos el apuntador de fin
    {                                 // para que apunte a nulo
        colaArchivos->fin = null; 
    }    

    colaArchivos->cantidadArchivos--;

    return doc;
}

void vaciarColaArchivos(ColaArchivos* cola)
{
    if (estaVacio(cola))
    {
        return;
    }

    Archivo* temp = desencolarArchivo(cola);

    while (temp != null)
    {
        free(temp->nombre); // liberamos la memoria que alojamos en main.
        free(temp);
        cola->cantidadArchivos--;
        temp = desencolarArchivo(cola);
    }

    return;
}

bool estaVacio(ColaArchivos* colaArchivos)
{
    return (colaArchivos->inicio == null);
}
// falta
Archivo* procesarArchivoPrioridad(ColaImpresion* colaPrincipal, int prioridad)
{
    if (colaPrincipal == null || colaPrincipal->inicio == null)
    {
        //printf("\nNo hay archivos en la cola de impresion.\n");
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
        //printf("\nApuntador nulo.\n");
        return;
    }
    
    if (colaPrincipal->inicio == null) 
    {
        enqueueColaArchivos(colaPrincipal, colaActual);
    }
    else
    {
        ColaImpresion auxiliar = crearColaImpresion(colaPrincipal->tipoDePrioridad);

        if (prioridad == _MIN_) // si la prioridad es de menor a mayor
        {
            // desencolamos hasta estar en la posicion correcta
            while (colaPrincipal->inicio != null && colaPrincipal->inicio->paginasDeLosArchivos < colaActual->paginasDeLosArchivos)
            {
                ColaArchivos* actual = desencolarColaArchivos(colaPrincipal);
                enqueueColaArchivos(&auxiliar, actual);
            }
            enqueueColaArchivos(&auxiliar, colaActual); // insertamos en orden en la cola auxiliar

            while (colaPrincipal->inicio != null) // terminamos de vaciar la cola principal si es que faltan elementos
            {
                ColaArchivos* actual = desencolarColaArchivos(colaPrincipal);
                enqueueColaArchivos(&auxiliar, actual);
            }            
        }
        else if (prioridad == _MAX_)
        {
            while (colaPrincipal->inicio != null && colaPrincipal->inicio->paginasDeLosArchivos > colaActual->paginasDeLosArchivos)
            {
                ColaArchivos* actual = desencolarColaArchivos(colaPrincipal);
                enqueueColaArchivos(&auxiliar, actual);
            }
            enqueueColaArchivos(&auxiliar, colaActual);

            while (colaPrincipal->inicio != null)
            {
                ColaArchivos* actual = desencolarColaArchivos(colaPrincipal);
                enqueueColaArchivos(&auxiliar, actual);
            }
        }

        *colaPrincipal = auxiliar; // actualizamos la cola principal con la cola auxiliar
    }

    colaPrincipal->cantidadColas++; 
    /*
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
    
    colaPrincipal->cantidadColas++;*/
}

void enqueueColaArchivos(ColaImpresion* colaPrincipal, ColaArchivos* colaNueva)
{
    if (colaPrincipal == null || colaNueva == null)
    { return; }

    if (colaPrincipal->inicio == null)
    {
        colaPrincipal->inicio = colaNueva;
        colaPrincipal->fin = colaNueva;
    }
    else
    {
        colaPrincipal->fin->siguiente = colaNueva;
        colaPrincipal->fin = colaNueva;
    }

    colaPrincipal->cantidadColas++;

    return;
}

ColaArchivos* desencolarColaArchivos(ColaImpresion* colaPrincipal)
{
    if (colaPrincipal == null)
    {
        //printf("ERROR: cola de impresion no iniciada.\n");
        return null;
    }
    if (colaPrincipal->inicio == null) 
    {
        //printf("ERROR: cola vacia.\n");
        return null;
    }
    /*      
    *           ^^^^^^^^^^^
    * nota: no usamos estaVacio ya que esta necesita acceder al valor "inicio"
    * de la cola, y si la cola esta vacia, acceder a este valor nos daria un
    * segmentation fault
    */
    
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
        //printf("\nNo se ha creado la cola de impresion.\n");
        return null;
    }

    ColaImpresion auxiliar = crearColaImpresion(colaImpresion->tipoDePrioridad);
    ColaArchivos* colaEncontrada = null;

    while (colaImpresion->inicio != null)
    {
        ColaArchivos* actual = desencolarColaArchivos(colaImpresion);

        if (actual->paginasDeLosArchivos == paginas)
        {
            colaEncontrada = actual;
        }

        enqueueColaArchivos(&auxiliar, actual);
    }

    *colaImpresion = auxiliar;

    return colaEncontrada;

    /*
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
    */
}

void encolarArchivoPrioridad(ColaImpresion* colaPrincipal, Archivo* doc, int prioridad)
{
    if (colaPrincipal == null || doc == null)
    {
        //printf("\nApuntador nulo.\n");
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

    ColaImpresion auxiliar = crearColaImpresion(colaImpresion->tipoDePrioridad);
    ColaArchivos* colaActual = desencolarColaArchivos(colaImpresion);
    
    int i = 1;
    while (colaActual != null)
    {
        printf("\n---Archivos de {%d} paginas:---\n", colaActual->paginasDeLosArchivos);
        imprimirColaArchivos(colaActual, &i);

        enqueueColaArchivos(&auxiliar, colaActual);
        colaActual = desencolarColaArchivos(colaImpresion);   
    }
    
    colaActual = desencolarColaArchivos(&auxiliar);
    while (colaActual != null)
    {
        enqueueColaArchivos(colaImpresion, colaActual);
        colaActual = desencolarColaArchivos(&auxiliar);   
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

    ColaArchivos* colaActual = desencolarColaArchivos(colaImpresion);

    while (colaActual != null)
    {
        vaciarColaArchivos(colaActual);
        colaImpresion->cantidadColas--;

        colaActual = desencolarColaArchivos(colaImpresion);
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

void eliminarArchivoPos(ColaImpresion* colaPrincipal, int posicion)
{
    if (colaPrincipal == null || colaPrincipal->inicio == null)
    {
        return;
    }

    if (posicion < 1) // solo validamos que sea mayor a 1, si el indice elegido es mayor 
    {                  // a la cantidad de archivos total, simplemente no se eliminara nada
        return;
    }

    ColaImpresion auxiliar = crearColaImpresion(colaPrincipal->tipoDePrioridad);
    Archivo* tmp = null;

    int iterador = 1;

    tmp = procesarArchivoPrioridad(colaPrincipal, colaPrincipal->tipoDePrioridad);

    while (tmp != null)
    {
        if (iterador != posicion) // si no es el archivo a eliminar, lo encolamos en la cola auxiliar
        {
            encolarArchivoPrioridad(&auxiliar, tmp, colaPrincipal->tipoDePrioridad);
        }

        tmp = procesarArchivoPrioridad(colaPrincipal, colaPrincipal->tipoDePrioridad);
        iterador++;
    }
    // regresamos de la cola auxiliar a la cola principal, ya sin el archivo a eliminar
    tmp = procesarArchivoPrioridad(&auxiliar, colaPrincipal->tipoDePrioridad);
    while (tmp != null)
    {
        encolarArchivoPrioridad(colaPrincipal, tmp, colaPrincipal->tipoDePrioridad);
        tmp = procesarArchivoPrioridad(&auxiliar, colaPrincipal->tipoDePrioridad);
    } 

    return;
}

bool colaImpresionVacia(ColaImpresion* colaImpresion)
{
    return (colaImpresion->inicio == null);
}










