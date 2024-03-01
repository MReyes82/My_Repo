#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Pila *inicializarCaja(void)
{
    Pila *caja;
    Libro libros[44] = 
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
        {"A Feast for Crows","Fantasy",2005}
    };

    caja = malloc(sizeof(Pila));
    inicializarPila(caja, 44);
    
    for (int i = 0 ; i < 44 ; i++)
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
    if (vacia(stackLibro))
    {
        printf("La pila esta vacia.\n");
        return;
    }

    Pila auxiliar;
    inicializarPila(&auxiliar, stackLibro->longitud);

    printf("Lista:\n");

    while (!vacia(stackLibro)) // sacamos todos los libros para mostrarlos
    {
        Libro *temp = pop(stackLibro);
        printf("%d | %s, %s", temp->releaseDate, temp->nombre, temp->genero);
        push(&auxiliar, temp);
    }
    // regresamos los libros al stack original
    while (!vacia(stackLibro))
    {
        push(stackLibro, pop(&auxiliar));
    }

    return;
}

int llena(Pila *stackLibro)
{   // retorna 1 si esta lleno y 0 si no
    return (stackLibro->longitud == stackLibro->numElementos); 
}

int vacia(Pila *stackLibro)
{   // retorna 1 si esta vacio y 0 si no
    return (stackLibro->numElementos == 0);
}

void push(Pila *stackLibro, Libro *nuevo)
{
    if (llena(stackLibro))
    {
        printf("Stack overflow.\n");
        return;
    }

    Elemento *nuevoElemento = alojarElemento(nuevo);
    nuevoElemento->sig = stackLibro->cima;
    stackLibro->cima = nuevoElemento;
    stackLibro->numElementos++;

    return;
}

Elemento *alojarElemento(void *input)
{
    Elemento *nuevo = malloc(sizeof(Elemento));
    nuevo->elementoLibro = input;
    nuevo->sig = NULL;

    return nuevo;
}

Libro *pop(Pila *stackLibro)
{
    if (vacia(stackLibro))
    {
        printf("Stack underflow.\n");
        return NULL;
    }

    Elemento *actual = stackLibro->cima; 
    Libro *popBuffer = actual->elementoLibro; 
    stackLibro->cima = actual->sig;
    free(actual->elementoLibro);
    free(actual); 
    stackLibro->numElementos--; 

    return popBuffer; // regresar el libro al cual acabamos de hacer pop
}

void vaciarPila(Pila *stackLibro)
{
    while (!vacia(stackLibro))
    {
        pop(stackLibro);
    }

    return;
}

void apilarPorGenero(StackArray *elementoArray, Libro *elementoLibro, char *genero)
{
    if (llena(elementoArray->stackLibros)) { return ;}
    // si el genero del parametro elementoLibro 
    //(el resultado de hacer pop al elemento actual de "caja" en main)
    // coincide con el genero deseado, pusheamos a la pila
    if (strcmp(elementoLibro->genero, genero) == 0)
    {
        push(elementoArray->stackLibros, elementoLibro);
    }

    return;
}

void apilarPorFecha(StackArray *elementoArray, Libro *elementoLibro, int releaseDate)
{
    if (elementoLibro->releaseDate == releaseDate)
    {
        push(elementoArray->stackLibros, elementoLibro);
    }

     return;
}

char *submenuApilarPorGenero(void)
{
    int opcion;
    char *output = malloc(50 * sizeof(char));

    printf("[2] APILAR POR GENERO\n\n");
    printf("[0] Fantasy\n");
    printf("[1] Historical novel\n");
    printf("[2] Crime\n");
    printf("[3] Historical fiction\n");
    printf("[4] Mystery\n");
    printf("[5] Thriller\n");
    printf("[6] Science fiction\n");
    printf("[7] Post-apocalyptic fiction\n");
    printf("[8] Fiction\n");
    printf("[9] Horror\n");
    printf("[10] Adventure Story\n\n");
    printf("Escoge una opcion: ");
    scanf("\n%d", &opcion);

    switch (opcion)
    {
    case 0:
        strcpy(output, "Fantasy");
        break;
    
    case 1:
        strcpy(output, "Historical novel");
        break;
    
    case 2:
        strcpy(output, "Crime");
        break;
    
    case 3:
        strcpy(output, "Historical fiction");
        break;

    case 4:
        strcpy(output, "Mystery");
        break;

    case 5:
        strcpy(output, "Thriller");
        break;

    case 6:
        strcpy(output, "Science fiction");
        break;

    case 7:
        strcpy(output, "Post-apocalyptic fiction");
        break;
    
    case 8:
        strcpy(output, "Fiction");
        break;

    case 9:
        strcpy(output, "Horror");
        break;
    
    case 10:
        strcpy(output, "Adventure Story");
        break;

    default:
        printf("ERROR\n");
        free(output);
        output = NULL;
        break;
    }

    return output;
}

int submenuApilarPorFecha(void)
{
    int output;
    printf("[3] APILAR POR FECHA\n\n");
    printf("Ingrese el año para filtar por fecha de publicacion (1997 - 2007): \n");
    scanf("\n%d", &output);

    if (output < 1997 && output > 2007) 
    {
        output = -1;
    }
    

    return output;
}