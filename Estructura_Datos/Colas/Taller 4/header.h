#pragma once

typedef struct Elemento
{
    int dato;
    struct Elemento *siguiente;

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
void enqueue(Queue cola, int datoAInsertar); // poner
void dequeue(Queue cola, int datoAQuitar); // quitar