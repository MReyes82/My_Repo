#pragma once

typedef struct Elemento
{
    int dato;
    struct Elemento *siguiente;
    struct Elemento *anterior;
    //int indice;

} Elemento;


typedef struct Queue 
{
    Elemento *inicio;
    Elemento *final;
    int length;
    int numeroElementos;

} Queue;

int llena(Queue cola);
int vacia(Queue cola);
void enqueue(Queue* cola, int datoAInsertar); // poner
void insertarPosicion(Queue* cola, int datoAInsertar, int posicion);
Elemento* dequeue(Queue* colan); // quitar
void printQueue(Queue* cola);
Elemento* alojarElemento(int dato);//, int indice);
Queue initQueue(int length);