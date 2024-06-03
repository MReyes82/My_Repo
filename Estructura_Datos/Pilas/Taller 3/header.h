#pragma once
#include <stdbool.h>

typedef struct Nodo
{
    int dato;
    struct Nodo *sig;
} Nodo;

typedef struct Stack
{
    Nodo *top;
    int length;

} Stack;

void pop(Stack *fullStack, int *datoAEliminar);
void push(Stack *fullStack, int datoAIngresar, int numeroNodos);
Nodo *alojarNodo(int dato);
void liberarMemoriaPila(Stack *fullStack);
bool vacia(Stack *fullStack);
bool llena(Stack *fullStack, int numeroNodos);
int cantidadDeNodos(Stack *fullStack);