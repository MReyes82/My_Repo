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

typedef struct Nodo
{
    Archivo* documento;
    struct Nodo* siguiente;

} Nodo;

typedef struct ColaArchivos // varias
{
    Nodo* inicio;
    Nodo* fin;
    struct ColaArchivos* siguiente;
    short int cantidadArchivos;
    short int paginasDeLosArchivos;

} ColaArchivos;

typedef struct ColaImpresion // una sola
{
    ColaArchivos* inicio;
    ColaArchivos* fin;
    short int cantidadColas;
    short int tipoDePrioridad;

} ColaImpresion;

// archivos
Archivo* crearDocumento(char* nombre, int numeroPaginas);
void imprimirDocumento(Archivo* doc, int iterador);
Nodo* crearNodo(Archivo* doc);
// cola archivos
ColaArchivos* crearColaArchivos(int paginasDeLosArchivos);
void encolarArchivo(ColaArchivos* colaArchivos, Archivo* doc);
Archivo* desencolarArchivo(ColaArchivos* colaArchivos);
int obtenerNumeroDocumentos(ColaArchivos* colaDeDocumentos);
void imprimirColaArchivos(ColaArchivos* colaArchivos, int* iterador);
bool estaVacio(ColaArchivos* colaArchivos);
ColaArchivos* encontrarColaArchivos(ColaImpresion* colaImpresion, int paginas);
// cola impresion
void imprimirColaImpresion(ColaImpresion* colaImpresion);
ColaImpresion crearColaImpresion(int tipoDePrioridad);
Archivo* procesarArchivoPrioridad(ColaImpresion* colaPrincipal, int prioridad);
void encolarColaArchivos(ColaImpresion* colaPrincipal, ColaArchivos* colaActual, int prioridad);
ColaArchivos* desencolarColaArchivos(ColaImpresion* colaPrincipal);
void encolarArchivoPrioridad(ColaImpresion* colaPrincipal, Archivo* doc, int prioridad);
void vaciarColaImpresion(ColaImpresion* colaImpresion);
void cambiarPrioridad(ColaImpresion* colaImpresion, int* prioridadNueva);



