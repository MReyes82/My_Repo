#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "header.h"

//* FUNCIONES TABLA HASH
HashTable* initHashTable(int size) 
{
    HashTable* nueva = malloc(sizeof(HashTable));

    nueva->size = size;
    nueva->dataAmount = 0;

    nueva->table = malloc(size * sizeof(Movie*));
    nueva->lastIDdeleted = -1;
    //nueva->table = calloc(size, sizeof(Movie*)

    //* Inicializar la tabla en null
    for (int i = 0; i < size; i++) 
    {
        nueva->table[i] = null;
    }

    return nueva;
}

void liberarTablaHash(HashTable* hash) 
{
    for (int i = 0; i < hash->size; i++) 
    {
        Movie* pelicula = hash->table[i];

        while (pelicula != null) 
        {
            Movie* temp = pelicula;
            pelicula = pelicula->siguiente;
            free(temp);
        }
    }

    free(hash->table);
    free(hash);

    return;
}

unsigned int funcionHash(int id, int size) 
{
    return (id - 1) % size;
}

unsigned int generarLlaveString(char* name, int size) 
{
    unsigned int llave = 0;
    int i = 0;

    while (name[i] != '\0') 
    {
        llave = (llave << 5) + (int) name[i];
        i++;
    }

    return llave % size;
}

/*void posicionarPunteroActual(Movie** apuntadorActual, Movie** apuntadorAnterior, int idBusqueda)
{
    //printf("Segfault en posicionar puntero\n");
    // Esta funcion se encarga recorrer la lista enlazada
    while (*apuntadorActual != null && (*apuntadorActual)->id != idBusqueda)
    {
        *apuntadorAnterior = *apuntadorActual;
        *apuntadorActual = (*apuntadorActual)->siguiente;
    }
    
    return;
}

void moverPunteroEliminar(HashTable* hash, Movie** actual, Movie** anterior, int index)
{
    printf("Segfault en mover puntro eliminar\n");
    if (*actual == null)
    {
        printf("Pelicula no encontrada.\n");
        return;
    }

    if (anterior != null)
    {
        printf("Asigna caso 1\n");

        if ((*actual)->siguiente == null)
        {
            printf("Fatal error.\n");
        }

        (*anterior)->siguiente = (*actual)->siguiente;

    } else  {
        printf("Fails to assign\n");
        hash->table[index] = (*actual)->siguiente;
    }
    printf("Segfault en posicionar puntero\n");

    return;
}*/

void insertarEnTablas(HashTable* hashID, HashTable* hashNombres, int id, char* name, int year, int rating) 
{
    //* Verificar el factor de carga de la tabla de ID's
    if (hashID->dataAmount >= hashID->size) //* Si la cantidad de elemtos es mayor o igual al tamaño de la tabla
    {
        int newSize = hashID->size + 1; //* Se duplica el tamaño de la tabla
        remapearTablaID(hashID, newSize);
    }

    //* insertar el nuevo elemento en la tabla de ID's
    unsigned int indice = funcionHash(id, hashID->size);

    Movie* nuevaPeliculaID = initMovie(id, name, year, rating);

    nuevaPeliculaID->siguiente = hashID->table[indice];
    hashID->table[indice] = nuevaPeliculaID;
    hashID->dataAmount++;

    //* Verificar el factor de carga de la tabla de nombres
    if ((float)hashNombres->dataAmount / hashNombres->size >= 0.75) //* Si el factor de carga es mayor a 0.25
    {
        int newSize = hashNombres->size * 2;
        remapearTablaNombre(hashNombres, newSize);
    }

    //* Insertar en la tabla de nombres
    indice = generarLlaveString(name, hashNombres->size);

    Movie* nuevaPeliculaNombre = initMovie(id, name, year, rating);

    nuevaPeliculaNombre->siguiente = hashNombres->table[indice];

    hashNombres->table[indice] = nuevaPeliculaNombre;
    hashNombres->dataAmount++;
}

//* OPERACIONES TABLA HASH
void eliminarPorID(HashTable* hashID, HashTable* hashNombres, int id) 
{
    unsigned int indice = funcionHash(id, hashID->size);
    Movie* actual = hashID->table[indice];
    Movie* anterior = null;

    //* Buscar la película en la tabla de ID

    //* Movemos el apuntador de la pelicula para eliminarla 
    while (actual != null && actual->id != id)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == null)
    {
        printf("Pelicula con ID %d no encontrada.\n", id);
        return;
    }

    //* Si la película fue encontrada, eliminarla
    if (anterior != null) {
        anterior->siguiente = actual->siguiente;

    } else {
        hashID->table[indice] = actual->siguiente;
    }

    hashID->lastIDdeleted = id;

    //* Ahora, buscamos la pelicula en la tabla de nombres

    // * colocamos el indice del elemento a buscar
    indice = generarLlaveString(actual->name, hashNombres->size);
    actual = hashNombres->table[indice];
    anterior = null;

    //* Recorremos la lista enlazada

    //* Movemos el apuntador de la pelicula para eliminarla 
    while (actual != null && actual->id != id)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    
    if (actual == null)
    {
        return;
    }

    //* Si se encontro, la eliminamos
    if (anterior !=  null) {
        anterior->siguiente = actual->siguiente;

    } else {
        hashNombres->table[indice] = actual->siguiente;
    }

    hashNombres->lastIDdeleted = id;

    free(actual);

    printf("Pelicula con ID %d eliminada.\n", id);

    return;
}

void eliminarPorNombre(HashTable* hashNombres, HashTable* hashID, char* name) 
{
    unsigned int indice = generarLlaveString(name, hashNombres->size);

    Movie* actual = hashNombres->table[indice];
    Movie* anterior = null;

    bool encontrado = false;

    //* Revisamos en caso de que haya mas de una pelicula con el mismo nombre
    printf("Peliculas encontradas con el nombre %s: \n\n", name);

    while (actual != null) 
    {
        if (strcmp(actual->name, name) == 0) {
          
            printMovie(actual);
            printf("\n");
            encontrado = true;
        }
        actual = actual->siguiente;
    }

    if (!encontrado) 
    {
        printf("No se encontraron peliculas con el nombre %s.\n", name);
        return;
    }

    int idAeliminar;
    printf("Ingrese el ID de la pelicula que desea eliminar: ");
    scanf("%d", &idAeliminar);

    actual = hashNombres->table[indice];
    anterior = null;

    //* Buscamos en la tabla de nombres
    while (actual != null && actual->id != idAeliminar)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == null) 
    {
        printf("ID de pelicula invalido. La pelicula no fue encontrada.\n");
        return;
    }

    /// * Eliminamos la pelicula si fue encontrada

    if (anterior != null) {
        anterior->siguiente = actual->siguiente;

    } else {
        hashNombres->table[indice] = actual->siguiente;
    }

    hashNombres->lastIDdeleted = idAeliminar;

    indice = funcionHash(actual->id, hashID->size);
    Movie* peliculaID = hashID->table[indice];
    anterior = null;

    //* Posicionamos los apuntadores en la posicion correcta
    while (peliculaID != null && peliculaID->id != actual->id)
    {
        anterior = peliculaID;
        peliculaID = peliculaID->siguiente;
    }

    // * La eliminamos si fue encontrada
    if (peliculaID != null)
    {
        if (anterior != null) {
            anterior->siguiente = peliculaID->siguiente;
        } else {
            hashID->table[indice] = peliculaID->siguiente;
        }
    }

    hashID->lastIDdeleted = actual->id;
    
    free(peliculaID);
    free(actual);

    hashNombres->dataAmount--;
    hashID->dataAmount--;

    printf("Pelicula con nombre %s e ID %d eliminada.\n", name, idAeliminar);

    return;
}


Movie* buscarPeliculaPorID(HashTable* hash, int id) 
{
    unsigned int indice = funcionHash(id, hash->size);

    Movie* actual = hash->table[indice];

    while (actual != null && actual->id != id) 
    {
        actual = actual->siguiente;
    }

    return actual;
}

bool buscarPeliculasNombre(HashTable* hash, char* name) 
{
    unsigned int indice = generarLlaveString(name, hash->size);

    Movie* pelicula = hash->table[indice];

    bool encontrado = false;

    printf("RESULTADOS ENCONTRADOS PARA EL NOMBRE: %s\n\n", name);

    while (pelicula) 
    {
        if (strcmp(pelicula->name, name) == 0) 
        {
            printMovie(pelicula);
            printf("\n");
            
            encontrado = true;
        }
        pelicula = pelicula->siguiente;
    }
    
    return encontrado;
}

void remapearTablaNombre(HashTable* hashNombre, int newSize)
{
    int i;
    Movie** nuevaTabla = malloc(newSize * sizeof(Movie*));

    //* Inicializar los valores de la nueva tabla en nulo
    for (i = 0 ; i < newSize ; i++)
        nuevaTabla[i] = null;

    //* Rehashing de los elementos a la nueva tabla
    for (i = 0 ; i < hashNombre->size ; i++)
    {
        Movie* actual = hashNombre->table[i];

        while (actual != null)
        {
            unsigned int nuevoIndice = generarLlaveString(actual->name, newSize);

            Movie* siguiente = actual->siguiente;
            actual->siguiente = nuevaTabla[nuevoIndice];
            nuevaTabla[nuevoIndice] = actual;

            actual = siguiente;
        }
    }

    //* Liberacion de la tabla anterior
    free(hashNombre->table);
    
    //* Reasignamos el apuntador de tabla de la hash
    hashNombre->table = nuevaTabla;
    //* ajustamos el tamaño 
    hashNombre->size = newSize;

    return;
}

void remapearTablaID(HashTable* hashID, int newSize)
{
    int i;
    Movie** nuevaTabla = malloc(newSize * sizeof(Movie*));

    for (i = 0 ; i < newSize ; i++)
        nuevaTabla[i] = null;

    for (i = 0 ; i < hashID->size ; i++)
    {
        Movie* actual = hashID->table[i];

        while (actual != null) 
        {
            unsigned int nuevoIndice = funcionHash(actual->id, newSize);

            Movie* siguiente = actual->siguiente;
            actual->siguiente = nuevaTabla[nuevoIndice];
            nuevaTabla[nuevoIndice] = actual;

            actual = siguiente;
        }
    }

    free(hashID->table);
    hashID->table = nuevaTabla;
    hashID->size = newSize;

    return;
}


void imprimirTablaHash(HashTable* table) 
{
    printf("SIZE: %d | ", table->size);
    printf("DATA AMOUNT: %d\n\n", table->dataAmount);

    for (int i = 0; i < table->size; i++) 
    {
        Movie* actual = table->table[i];
        while (actual) 
        {
            printf("%-9d|", i);
            printMovie(actual);

            actual = actual->siguiente;
        }
    }

    return;
}

//* FUNCIONES MOVIE
void create_movies(HashTable* hash, HashTable* hashNombres) 
{
    Movie movies[SIZE_DATA] = {
        {1,"Blade Runner 2049\0",2017,80},
        {2,"Interstellar\0",2014,87},
        {3,"Mad Max: Fury Road\0",2015,81},
        {4,"Children of Men\0",2006,79},
        {5,"Inception\0",2010,88},
        {6,"Tenet\0",2020,73},
        {7,"Once Upon a Time... In Hollywood\0",2019,76},
        {8,"Inglourious Basterds\0",2009,84},
        {9,"The Lord of the Rings: The Return of the King\0",2003,90},
        {10,"The Wolf of Wall Street\0",2013,82},
        {11,"Disturbia\0",2007,68},
        {12,"Dunkirk\0",2017,78},
        {13,"Troy\0",2004,73},
        {14,"The Dark Knight\0",2008,90},
        {15,"Forrest Gump\0",1994,88},
        {16,"Fight Club\0",1999,88},
        {17,"Star Wars: Episode V - Empire Strikes Back\0",1980,87},
        {18,"The Silence of the Lamps\0",1991,86},
        {19,"Saving Private Ryan\0",1998,86},
        {20,"The Departed\0",2006,85},
        {21,"Whiplash\0",2014,85},
        {22,"Spider-Man: Into the Spider-Verse\0",2018,85},
        {23,"Avengers: Infinity War\0",2018,84},
        {24,"Django Unchained\0",2012,85},
        {25,"The Ministry of Ungentlemanly Warfare\0",2024,73},
        {26,"Godzilla x Kong: The New Empire\0",2024,65},
        {27,"Monkey Man\0",2024,71},
        {28,"Road House\0",2024,62},
        {29,"Rebel Moon - Part Two: The Scargiver\0",2024,52},
        {30,"Wish\0",2023,56},
        {31,"Anyone But You\0",2023,62},
        {32,"The Fall Guy\0",2024,74},
        {33,"The Bricklayer\0",2023,51},
        {34,"Anatomy of a Fall\0",2023,77},
        {35,"Hit man\0",2023,77},
        {36,"Glass\0",2019,66},
        {37,"Barbie\0",2023,68},
        {38,"Stolen\0",2024,56},
        {39,"Madame Web\0",2024,38},
        {40,"Joker\0",2019,84},
        {41,"The Shawshank Redemption\0",1994,93},
        {42,"Pulp Fiction\0",1994,92},
        {43,"Titanic\0",1997,89},
        {44,"The Matrix\0",1999,87},
        {45,"The Sixth Sense\0",1999,85},
        {46,"Gladiator\0",2000,86},
        {47,"Memento\0",2000,85},
        {48,"The Lord of the Rings: The Fellowship of the Ring\0",2001,88},
        {49,"A Beautiful Mind\0",2001,86},
        {50,"Spirited Away\0",2001,89},
        {51,"The Lord of the Rings: The Two Towers\0",2002,89},
        {52,"Finding Nemo\0",2003,90},
        {53,"The Incredibles\0",2004,89},
        {54,"Eternal Sunshine of the Spotless Mind\0",2004,88},
        {55,"Million Dollar Baby\0",2004,87},
        {56,"Brokeback Mountain\0",2005,87},
        {57,"Crash\0",2004,78},
        {58,"Pan's Labyrinth\0",2006,89},
        {59,"The Prestige\0",2006,88},
        {60,"No Country for Old Men\0",2007,90},
        {61,"There Will Be Blood\0",2007,89},
        {62,"WALL-E\0",2008,89},
        {63,"Slumdog Millionaire\0",2008,88},
        {64,"The Dark Knight\0",2008,90},
        {65,"Up\0",2009,88},
        {66,"Avatar\0",2009,83},
        {67,"Inception\0",2010,88},
        {68,"Toy Story 3\0",2010,87},
        {69,"Black Swan\0",2010,85},
        {70,"The Social Network\0",2010,88},
        {71,"The King's Speech\0",2010,87},
        {72,"The Artist\0",2011,88},
        {73,"Hugo\0",2011,87},
        {74,"The Help\0",2011,81},
        {75,"The Avengers\0",2012,85},
        {76,"Django Unchained\0",2012,87},
        {77,"Life of Pi\0",2012,86},
        {78,"Gravity\0",2013,87},
        {79,"12 Years a Slave\0",2013,88},
        {80,"Her\0",2013,89},
        {81,"Boyhood\0",2014,87},
        {82,"Birdman or (The Unexpected Virtue of Ignorance)\0",2014,88},
        {83,"The Grand Budapest Hotel\0",2014,87},
        {84,"Spotlight\0",2015,88},
        {85,"Mad Max: Fury Road\0",2015,90},
        {86,"The Revenant\0",2015,88},
        {87,"La La Land\0",2016,89},
        {88,"Arrival\0",2016,88},
        {89,"Moonlight\0",2016,88},
        {90,"Get Out\0",2017,87},
        {91,"Dunkirk\0",2017,89},
        {92,"The Shape of Water\0",2017,87},
        {93,"Three Billboards Outside Ebbing, Missouri\0",2017,88},
        {94,"Coco\0",2017,89},
        {95,"Call Me by Your Name\0",2017,88},
        {96,"Lady Bird\0",2017,87},
        {97,"Bohemian Rhapsody\0",2018,88},
        {98,"A Star is Born\0",2018,87},
        {99,"Black Panther\0",2018,88},
        {100,"Parasite\0",2019,89},
        {101,"Jojo Rabbit\0",2019,87},
        {102,"Joker\0",2019,86},
        {103,"Once Upon a Time... In Hollywood\0",2019,88},
        {104,"1917\0",2019,88},
        {105,"The Irishman\0",2019,87}
    };

    for (int i = 0; i < SIZE_DATA; i++) 
    {
        insertarEnTablas(hash, hashNombres, movies[i].id, movies[i].name, movies[i].year, movies[i].rating);
    }

    return;
}

void printMovie(Movie* movie)
{
    printf("%-3d | ", movie->id);
    printf("%-55s | ", movie->name);
    printf("%d | ", movie->year);
    printf("%d ", movie->rating);
    printf("\n");

    return;
}
Movie* initMovie(int id, char* name, int year, int rating)
{
    Movie* nueva = malloc(sizeof(Movie));

    nueva->id = id;
    strcpy(nueva->name, name);
    nueva->year = year;
    nueva->rating = rating;
    nueva->siguiente = null;

    return nueva;
}
