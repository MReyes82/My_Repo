#include "Hash.h"
#include "Movie.h"
#include "stdbool.h"

/*
^ ----------------------
* Funciones tablas hash
^ ----------------------
*/
void initHashTable(HashTable* hash, int size, FunctionFolding folding)
{
    hash->size = size;
    hash->amount_data = 0;
    hash->table = malloc(sizeof(Movie*) * size);
    hash->folding = folding;

    for (int i = 0; i < size; i++)
    {
        hash->table[i] = NULL;
    }

    return;
}

int funcionHash(HashTable* hash, int llave)
{
    return llave % hash->size;
}

int sondeoCuadratico(HashTable* hash, int indice, int k)
{
    return (indice + (k * k)) % hash->size;
}

int generarLlave(const char* nombre)
{
    int len = strlen(nombre);
    int llave = 0, i;

    for (i = 0 ; i < len ; i += 2)
    {
        int grupo = 0;
        grupo = (grupo * 256 + nombre[i]);

        if (i + 1 < len)
        {
            grupo = grupo * 256 + nombre[i + 1];
        }
        llave += grupo;
    }

    return llave;
}

int calcularLlaveString(Movie* pelicula)
{
    //* Esta funcion es utilizada como funcion folding,
    //* para el caso de la segunda tabla hash.
    return generarLlave(pelicula->name);
}

int getID(Movie* pelicula)
{
    //* Esta funcion es utilizada como funcion folding,
    //* para el caso de la primer tabla hash.
    return pelicula->id;
}

int rehashing(HashTable* hash, Movie* pelicula, Movie** Peliculas)
{
    int llave = hash->folding(pelicula);
    int indice = funcionHash(hash, llave);
    int nuevoIndice = indice;

    int j = 0;
    while (Peliculas[nuevoIndice] != null)
    {
        j++;
        nuevoIndice = sondeoCuadratico(hash, indice, j);
    }

    return nuevoIndice;
}

void liberarTabla(HashTable* hash)
{
    for (int i = 0 ; i < hash->size ; i++)
    {
        if (hash->table[i] != null)
        {
            free(hash->table[i]);
        }
    }

    free(hash->table);
    //hash->table = null;
    //free(hash);

    return;
}

/*
^ ----------------------
* Operaciones de tabla hash
^ ----------------------
*/

void insertarPeliculaNombre(HashTable* hash, Movie* pelicula)
{
    if (hash->amount_data >= (hash->size * 0.25) )
    {
        remapearTabla(hash, hash->size * 2); //* Mantenemos el factor de carga en 0.25
    }

    int indice = rehashing(hash, pelicula, hash->table);
    hash->table[indice] = pelicula;
    hash->amount_data++;

    return;
}

void insertarPeliculaID(HashTable* hash, Movie* pelicula)
{
    if (hash->amount_data >= (hash->size * 0.75) )
    {
        remapearTabla(hash, hash->size * 2); //* Mantenemos el factor de carga en 0.75
    }

    int indice = rehashing(hash, pelicula, hash->table);
    hash->table[indice] = pelicula;
    hash->amount_data++;

    return;
}

void eliminarPeliculaNombre(HashTable* hash, const char* nombre)
{
    int llave = generarLlave(nombre);
    int indice = funcionHash(hash, llave);
    int nuevoIndice = indice;
    //bool encontrado = false;

    int j = 0;
    while (hash->table[nuevoIndice] != null)
    {
        if (strcmp(hash->table[nuevoIndice]->name, nombre) == 0)
        {
            free(hash->table[nuevoIndice]);
            hash->table[nuevoIndice] = null;
            hash->amount_data--;

            //encontrado = true;
            return;
        }
        j++;
        nuevoIndice = sondeoCuadratico(hash, indice, j);
    }
    
    /*if (!encontrado)
    {
        printf("Pelicula no encontrada\n");
    }*/
    
    return;
}

void eliminarPeliculaID(HashTable* hash, int id)
{
    int llave = id;
    int indice = funcionHash(hash, llave);
    int nuevoIndice = indice;
    //bool encontrado = false;

    int j = 0;
    while (hash->table[nuevoIndice] != null)
    {
        if (hash->table[nuevoIndice]->id == id)
        {
            free(hash->table[nuevoIndice]);
            hash->table[nuevoIndice] = null;
            hash->amount_data--;

            //encontrado = true;
            return;
        }
        j++;
        nuevoIndice = sondeoCuadratico(hash, indice, j);
    }

    /*if (!encontrado)
    {
        printf("Pelicula no encontrada\n");
    }*/

    return;
}

void imprimirTabla(HashTable* hash)
{
    for (int i = 0 ; i < hash->size ; i++)
    {
        if (hash->table[i] != null)
        {
            printMovie(hash->table[i]);
            printf("\n");
        }
    }

    return;
}

/*
^ ----------------------
* Funciones de busqueda
^ ----------------------
*/

Movie* buscarPeliculaNombre(HashTable* hash, const char* nombre)
{
    int llave = generarLlave(nombre);
    int indice = funcionHash(hash, llave);
    int nuevoIndice = indice;

    int j = 0;
    while (hash->table[nuevoIndice] != null)
    {
        if (strcmp(hash->table[nuevoIndice]->name, nombre) == 0)
        {
            return hash->table[nuevoIndice];
        }
        j++;
        nuevoIndice = sondeoCuadratico(hash, indice, j);
    }

    return null;
}

Movie* buscarPeliculaID(HashTable* hash, int id)
{
    int llave = id;
    int indice = funcionHash(hash, llave);
    int nuevoIndice = indice;

    int j = 0;
    while (hash->table[nuevoIndice] != null)
    {
        if (hash->table[nuevoIndice]->id == id)
        {
            return hash->table[nuevoIndice];
        }
        j++;
        nuevoIndice = sondeoCuadratico(hash, indice, j);
    }

    return null;
}

void remapearTabla(HashTable* hash, int newSize)
{
    Movie** nuevasPeliculas = calloc(newSize, sizeof(Movie*));

    for (int i = 0 ; i < hash->size ; i++)
    {
        if (hash->table[i] != null)
        {
            Movie* pelicula = hash->table[i];

            int index = rehashing(hash, pelicula, nuevasPeliculas);
            nuevasPeliculas[index] = pelicula;
        }
    }

    free(hash->table);
    hash->table = nuevasPeliculas;
    hash->size = newSize;
    
    return;
}

//* Funciones auxiliares
void vaciarArregloEstatico(HashTable* hash, Movie** arregloPeliculas)
{
    for (int i = 0 ; i < hash->size ; i++)
    {
        Movie* temp = getMovie(arregloPeliculas, i);

        if (temp == null)
        {
            continue;
        }
        
        hash->table[i] = malloc(sizeof(Movie));
        memcpy(hash->table[i], temp, sizeof(Movie));

        //free(temp);
        temp = null;

        hash->amount_data++;
    }

    return;
}

Movie* initMovie(int id, char* nombre, short int fecha, short int calificacion)
{
    Movie* pelicula = malloc(sizeof(Movie));
    pelicula->id = id;
    pelicula->name = nombre;
    pelicula->release_date = fecha;
    pelicula->rating = calificacion;

    return pelicula;
}