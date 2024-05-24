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
    hash->last_id_deleted = -1;
    //hash->max_id = 0;

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
            free(hash->table[i]->name);
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
    if (buscarPeliculaID(hash, pelicula->id) != null)
    {
        printf("ID duplicado detectado. Reasignando ID\n");
        if (hash->last_id_deleted == -1)
        {
            printf("Error faltal:INSERCION FALLIDA.\n");
            return;
        }

        pelicula->id = hash->last_id_deleted;
        hash->last_id_deleted = -1;
    }

    int indice = rehashing(hash, pelicula, hash->table);
    hash->table[indice] = pelicula;
    hash->amount_data++;

    if (hash->amount_data > hash->size / 2)
    {   
        remapearTabla(hash, hash->size * 2);
    }

    return;
}

/*void eliminarPeliculaNombre(HashTable* hash, char* nombre)
{
    int llave = generarLlave(nombre);
    int indice = funcionHash(hash, llave);
    int nuevoIndice = indice;
    bool encontrado = false;

    int j = 0;
    while (hash->table[nuevoIndice] != null)
    {
        if (strcmp(hash->table[nuevoIndice]->name, nombre) == 0)
        {
            hash->last_id_deleted = hash->table[nuevoIndice]->id;
            free(hash->table[nuevoIndice]);
            free(hash->table[nuevoIndice]->name);
            hash->table[nuevoIndice] = null;
            hash->amount_data--;

            encontrado = true;
            return;
        }
        j++;
        nuevoIndice = sondeoCuadratico(hash, indice, j);
    }
    
    if (!encontrado)
    {
        printf("Pelicula no encontrada (FUNCION ELIMINAR POR ID)\n");
    }
    
    return;
}*/

void eliminarPeliculaID(HashTable* hash, int id)
{
    /*
    int llave = id;
    int indice = funcionHash(hash, llave);
    int nuevoIndice = indice;
    bool encontrado = false;

    bool seBorroUltimoElemento = false;
    
    //printf("size: %d, count: %d, id: %d\n", hash->size, hash->amount_data, id);
    * Ouput: size: 210, count: 105, id: 105
    // * Falta encontar un modo de registrar el ultimo ID insertado.
    * Y el mayor ID actual.

    if (hash->size == id)
    {
        printf("Bandera ultimo elemento activada\n");
        seBorroUltimoElemento = true;
    }

    int j = 0;
    while (hash->table[nuevoIndice] != null)
    {
        if (hash->table[nuevoIndice]->id == id)
        {
            hash->last_id_deleted = hash->table[nuevoIndice]->id;
            free(hash->table[nuevoIndice]);
            free(hash->table[nuevoIndice]->name);
            hash->table[nuevoIndice] = null;
            hash->amount_data--;

            encontrado = true;
            return;
        }
        j++;
        nuevoIndice = sondeoCuadratico(hash, indice, j);
    }

    if (seBorroUltimoElemento)
    {
        hash->size = hash->amount_data;
        remapearTabla(hash, hash->size);
    }

    if (!encontrado)
    {
        printf("Pelicula no encontrada (FUNCION ELIMINAR POR ID)\n");
    }
    */
    for (int i = 0 ; i < hash->size ; i++)
    {
        if (hash->table[i] != null && hash->table[i]->id == id)
        {
            hash->last_id_deleted = hash->table[i]->id;
            free(hash->table[i]);
            free(hash->table[i]->name);
            hash->table[i] = null;
            hash->amount_data--;

            return;
        }
    }
    printf("Pelicula no encontrada (FUNCION ELIMINAR POR ID)\n");

    return;
}

void imprimirTabla(HashTable* hash)
{
    for (int i = 0 ; i < hash->size ; i++)
    {
        if (hash->table[i] != null)
        {
            printf("%d - ", i); //* Indice
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

/*Movie* buscarPeliculaNombre(HashTable* hash, char* nombre)
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
}*/
Movie** buscarPeliculasNombre(HashTable* hash, char* nombre, int* cantidadPeliculas)
{
    int llave = generarLlave(nombre);
    int indice = funcionHash(hash, llave);
    int nuevoIndice = indice;

    int j = 0;
    
    Movie** resultados = calloc(1, sizeof(Movie*)); //* asumimos al menos una coincidencia.
    resultados[0] = null; //* Inicializamos el primer elemento como null, en caso de que no encuentre.
    *cantidadPeliculas = 0;

    while (hash->table[nuevoIndice] != null)
    {
        if (strcmp(hash->table[nuevoIndice]->name, nombre) == 0)
        {
            (*cantidadPeliculas)++;
            resultados = realloc(resultados, sizeof(Movie*) * ( (*cantidadPeliculas)));
            resultados[(*cantidadPeliculas) - 1] = hash->table[nuevoIndice];
        }
        j++;
        nuevoIndice = sondeoCuadratico(hash, indice, j);
    }

    return resultados;
}

void mostrarPeliculasNombre(Movie** peliculas, int cantidadPeliculas)
{
    if (peliculas[0] == null)
    {
        printf("Pelicula no encontrada\n");
        return;
    }

    printf("Peliculas encontradas con el nombre: %s\n", peliculas[0]->name);
    for (int i = 0 ; i < cantidadPeliculas ; i++)
    {
        printMovie(peliculas[i]);
        printf("\n");
    }
    
    return;

}

Movie* buscarPeliculaID(HashTable* hash, int id)
{
    /*
    * Pendiente de evaluar implementacion.
    * Esta tabla hash simplemente es un arreglo de punteros (?)
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
    */
    for (int i = 0 ; i < hash->size ; i++)
    {
        if (hash->table[i] != null && hash->table[i]->id == id)
        {
            //printf("Pelicula encontrada(Funcion).\n"); //* Debug
            return hash->table[i];
        }
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
Movie* initMovie(int id, char* nombre, short int fecha, short int calificacion)
{
    Movie* pelicula = malloc(sizeof(Movie));
    pelicula->id = id;
    pelicula->name = malloc(strlen(nombre) + 1);
    strcpy(pelicula->name, nombre);
    pelicula->release_date = fecha;
    pelicula->rating = calificacion;

    return pelicula;
}

void imprimirDatosTabla(HashTable* hash)
{
    printf("Size: %d | Cantidad Elementos: %d\n", hash->size, hash->amount_data);

    return;
}