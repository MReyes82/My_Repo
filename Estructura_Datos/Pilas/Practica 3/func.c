#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Pila *inicializarCaja(void)
{
    Pila *caja;
    static Libro libros[45] = 
    {
        {"Cell","Horror",2006},
        {"The Street Lawyer","Thriller",1998},
        {"Nineteen Minutes","Thriller",2007},
        {"Harry Potter y la piedra filosofal","Fantasy",1997},
        {"Armageddon","Post-apocalyptic fiction",2003},
        {"The Jester","Historical fiction",2003},
        {"Harry Potter y el prisionero de Azkaban","Fantasy",1999},
        {"Star Wars: Episode I The Phantom Menace","Science fiction",1999},
        {"Dreamcatcher","Fantasy",2001},
        {"Rainbow Six","Thriller",1998},
        {"Hannibal","Horror",1999},
        {"Twelve Sharp","Crime",2006},
        {"The Bear and the Dragon","Thriller",2000},
        {"The Testament","Adventure Story",1999},
        {"Red Rabbit","Historical fiction",2002},
        {"Anansi Boys","Fantasy",2005},
        {"Airframe","Thriller",1997},
        {"Harry Potter y la camara secreta","Fantasy",1998},
        {"The King of Torts","Thriller",2003},
        {"The Da Vinci Code","Mystery",2003},
        {"Harry Potter y la Orden del Fenix","Fantasy",2003},
        {"Mary, Mary","Crime",2005},
        {"The Summons","Thriller",2002},
        {"Bag of Bones","Horror",1998},
        {"The 5th Horseman","Thriller",2006},
        {"Step on a Crack","Thriller",2007},
        {"Winter's Heart","Fantasy",2000},
        {"Plum Island","Fiction",1997},
        {"Eleven on Top","Crime",2005},
        {"Harry Potter y el misterio del principe","Fantasy",2005},
        {"The Closers","Crime",2005},
        {"Glorious Appearing","Post-apocalyptic fiction",2004},
        {"Prey ","Science fiction",2002},
        {"The Last Juror","Thriller",2004},
        {"'S' Is for Silence","Mystery",2005},
        {"4th of July","Mystery",2005},
        {"Harry Potter y las reliquias de la Muerte","Fantasy",2007},
        {"The Shelters of Stone","Historical fiction",2002},
        {"Harry Potter y el caliz de fuego","Fantasy",2000},
        {"The Dark Tower VII: The Dark Tower","Fantasy",2004},
        {"Book of the Dead ","Crime",2007},
        {"The Dark Tower VI: Song of Susannah","Fantasy",2004},
        {"Cold Mountain","Historical novel",1997},
        {"A Feast for Crows","Fantasy",2005}, 
        {"Hola" , "papu", 2047},
    };

    caja = (Pila *)malloc(sizeof(Pila));
    inicializarPila(caja, 45);
    
    for (int i = 0 ; i < 45 ; i++)
    {
        push(caja, &libros[i]);
    }
    

    return caja;
}

void inicializarPila(Pila *stackLibro,int longitud)
{
    stackLibro->cima = NULL;
    stackLibro->longitud = longitud;
    stackLibro->numElementos = 0;

    return;
}  

void imprimirPila(Pila *stackLibro)
{
    if (vacia(*stackLibro))
    {
        printf("La pila esta vacia.\n");
        return;
    }

    Pila auxiliar;
    inicializarPila(&auxiliar, stackLibro->longitud);

    printf("Lista:\n");
    
    while (!vacia(*stackLibro)) // sacamos todos los libros para mostrarlos
    {
        Libro *temp = NULL;
        temp = pop(stackLibro);
        printf("%d | %s, %s\n", temp->releaseDate, temp->nombre, temp->genero);
        push(&auxiliar, temp);
    }
    // regresamos los libros al stack original
    while (!vacia(auxiliar))
    {
        push(stackLibro, pop(&auxiliar));
    }

    return;
}

int llena(Pila stackLibro)
{   // retorna 1 si esta lleno y 0 si no
    if (stackLibro.longitud == 0 || stackLibro.numElementos < stackLibro.longitud)
    {
        return 0;
    }
    // si no se cumple, quiere decir que esta llena
    return 1;
}

int vacia(Pila stackLibro)
{   // retorna 1 si esta vacio y 0 si no
    return (stackLibro.numElementos == 0);
}

void push(Pila *stackLibro, Libro *nuevo)
{
    if (llena(*stackLibro))
    {
        printf("--Stack overflow.\n");
        return;
    }

    Elemento *nuevoElemento = alojarElemento(nuevo);
    nuevoElemento->sig = stackLibro->cima;
    stackLibro->cima = nuevoElemento;
    stackLibro->numElementos++;

    return;
}

Elemento *alojarElemento(Libro *input)
{
    Elemento *nuevo = malloc(sizeof(Elemento));
    nuevo->elementoLibro = input;
    nuevo->sig = NULL;

    return nuevo;
}

Libro *pop(Pila *stackLibro)
{
    if (vacia(*stackLibro))
    {
        printf("--Stack underflow.\n");
        return NULL;
    }

    Elemento *actual = stackLibro->cima; 
    Libro *popBuffer = actual->elementoLibro; 
    stackLibro->cima = actual->sig;
    //free(actual->elementoLibro);
    free(actual); 
    stackLibro->numElementos--; 

    return popBuffer; // regresar el libro al cual acabamos de hacer pop
}

void vaciarPila(Pila *stackLibro)
{
    while (!vacia(*stackLibro))
    {
        pop(stackLibro);
    }

    return;
}

void apilarPorGenero(StackArray *elementoArray, Libro *elementoLibro)
{
    int indice;
    for (indice = 0 ; indice < elementoArray->numStacks ; indice++)
    {   
        char *temp = elementoArray->stackLibros[indice].cima->elementoLibro->genero; // para mas legibilidad
        if (strcmp(temp, elementoLibro->genero) == 0)
        {
            push(&elementoArray->stackLibros[indice], elementoLibro);
            return;
        }
    }
    //printf("[%d]\n", indice);

    /* 
    realojamos el tamaño en caso que el genero no sea el deseado
    */
    Pila *auxiliar = NULL;
    while(auxiliar == NULL)
    {
        auxiliar = realloc(elementoArray->stackLibros, sizeof(Pila) * (elementoArray->numStacks + 1));
    }

    elementoArray->stackLibros = auxiliar;
    inicializarPila(&elementoArray->stackLibros[indice], 0);
    push(&elementoArray->stackLibros[indice], elementoLibro);
    elementoArray->numStacks++;

    return;
}

void apilarPorFecha(StackArray *elementoArray, Libro *elementoLibro)
{
    int indice;
    for (indice = 0 ; indice < elementoArray->numStacks ; indice++)
    {
        int temp = elementoArray->stackLibros[indice].cima->elementoLibro->releaseDate;
        if (temp == elementoLibro->releaseDate)
        {
            push(&elementoArray->stackLibros[indice], elementoLibro);
            return;
        }
    }
    //printf("[%d]\n", indice);

    Pila *auxiliar = NULL;
    while(auxiliar == NULL)
    {
        auxiliar = realloc(elementoArray->stackLibros, sizeof(Pila) * (elementoArray->numStacks + 1));
    }

    elementoArray->stackLibros = auxiliar;
    inicializarPila(&elementoArray->stackLibros[indice], 0);
    push(&elementoArray->stackLibros[indice], elementoLibro);
    elementoArray->numStacks++;

    return;
}

int subMenu(char *textoPrint)
{
    int output;
    printf("%s", textoPrint);
    scanf("\n%d", &output);

    return output;
}

