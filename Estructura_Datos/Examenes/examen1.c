#include <stdio.h>
#include <stdlib.h>

typedef struct Elemento
{
    int dato;
    struct Elemento* sig;

} Elemento;

typedef struct Lista
{
    Elemento* inicio;
    Elemento* final;
    int cantidadElementos;
    
} Lista;

void crearElemento(Lista** p, int dato)
{
    ;
}

void agregarDato(Lista *p, int dato)
{
    Elemento *q;
    Elemento *r;
    q = p->inicio;

    if (q == NULL)
    {
        crearElemento(&q, dato);
        p->inicio = q;
        p->inicio->sig = q;
        p->cantidadElementos++;
        return;
    }

    do
    {
        r = q;
        q = q->sig;

    } while (q != p->inicio);

    crearElemento(&q, dato);
    q->sig = p->inicio;
    r->sig = q;
    p->inicio
    
}

void concatenar(Lista* q, Lista* p)
{
    Elemento* q_1, q_2;
    Elemento* r_1, r_2;
    q_1 = q->inicio;

    if (p->inicio == NULL)
    {
        q->inicio = p-> inicio;
        q->cantidadElementos = ;
    }
}

int main (void)
{
    printf("ADIOS MUNDO\n");
    return 0;
}