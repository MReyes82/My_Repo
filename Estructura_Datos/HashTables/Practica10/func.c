#include "Hash.h"
#include "Movie.h"
#include "stdbool.h"

/*
! Ultimo refactor hecho:
! Se cambio el metodo de resolución de colisiones
! de Sondeo Cuadratico a Encadenamiento.
*/

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

    for (int i = 0; i < size; i++)
    {
        hash->table[i] = null;
    }

    return;
}

int funcionHash(int llave, int tam) //* {llave generada} mod {tamaño de la tabla}
{
    return llave % tam;
}

int generarLlave(const char* nombre)
{
    int llave = 0;
    int i = 0;
    
    while (nombre[i] != '\0')
    {
        llave = (llave << 5) + (int) nombre[i];
        i++;
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

/*void rehashing(HashTable* hash, Movie* pelicula, Movie** Peliculas, int nuevoSize)
{
    while (pelicula != null)
    {
        int nuevoIndice = funcionHash(hash->folding(pelicula), nuevoSize);

        Movie* sig = pelicula->siguiente;
        pelicula->siguiente = Peliculas[nuevoIndice];
        Peliculas[nuevoIndice] = pelicula;

        pelicula = sig;
    }

    return;
}*/

void liberarTabla(HashTable* hash)
{
    for (int i = 0 ; i < hash->size ; i++)
    {
        Movie* actual = hash->table[i];

        while (actual != null) // * Iteramos sobre la lista enlazada generada.
        {
            Movie* temp = actual; // * Guardamos la referencia al nodo actual.
            actual = actual->siguiente; // * Guardamos la referencia al siguiente nodo.
            free(temp); // * Liberamos el nodo actual.
        }
    }

    free(hash->table);
    free(hash);

    return;
}

/*
^ ----------------------
* Operaciones de tabla hash
^ ----------------------
*/

void insertarPeliculaNombre(HashTable* hash, Movie* pelicula)
{
    if ( ((float) hash->amount_data / hash->size) >= 0.75)
    {
        remapearTabla(hash, hash->size * 2);
    }

    int indice = funcionHash(hash->folding(pelicula), hash->size);
    pelicula->siguiente = hash->table[indice];

    hash->table[indice] = pelicula;
    hash->amount_data++;


    return;
}

void insertarPeliculaID(HashTable* hash, Movie* pelicula)
{
    if (hash->amount_data >= hash->size)
    {
        remapearTabla(hash, hash->size * 2);
    }

    int indice = funcionHash(hash->folding(pelicula), hash->size);
    pelicula->siguiente = hash->table[indice];

    hash->table[indice] = pelicula;
    hash->amount_data++;

    return;
}

void eliminarPeliculaNombre(HashTable* hash, char* nombre)
{
    int indice = funcionHash(generarLlave(nombre), hash->size);
    Movie* actual = hash->table[indice];
    Movie* anterior = null;

    //bool encontrado = false;

    while (actual != null)
    {
        anterior = null;
        actual = actual->siguiente;
    }

    if (actual == null)
    {
        return;
    }

    if (anterior != null) {
        anterior->siguiente = actual->siguiente;
    }else{
        hash->table[indice] = actual->siguiente;
    }

    return;
}

void eliminarPeliculaID(HashTable* hash, int id)
{
    int indice = funcionHash(id, hash->size);
    Movie* actual = hash->table[indice];
    Movie* anterior = null;

    while (actual != null && actual->id != id) //* Buscamos la pelicula.
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == null) {
        printf("Pelicula no encontrada\n");
        return;
    }

    hash->last_id_deleted = actual->id;

    if (anterior != null) { // * Si no lo encuentra en la primera posicion.

        anterior->siguiente = actual->siguiente;

    } else { // * Si lo encuentra en la primera posicion.
    
        hash->table[indice] = actual->siguiente;
    }

    free(actual);
    hash->amount_data--;

    printf("Pelicula eliminada\n");

    return;
}

void imprimirTabla(HashTable* hash)
{
    imprimirDatosTabla(hash);
    for (int i = 0 ; i < hash->size ; i++)
    {
        Movie* actual = hash->table[i];

        while (actual != null)
        {
            printf("Indice: %-9d | ", i);
            printMovie(actual);
            printf("\n");
            actual = actual->siguiente;
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
    int indice = funcionHash(generarLlave(nombre), hash->size);
    Movie* actual = hash->table[indice];
    
    Movie** resultados = calloc(1, sizeof(Movie*)); //* asumimos al menos una coincidencia.
    resultados[0] = null; //* Inicializamos el primer elemento como null, en caso de que no encuentre.
    *cantidadPeliculas = 0;

    while (actual != null)
    {
        if (strcmp(actual->name, nombre) == 0)
        {
            (*cantidadPeliculas)++;
            resultados = realloc(resultados, sizeof(Movie*) * ( (*cantidadPeliculas)));
            resultados[(*cantidadPeliculas) - 1] = actual;
        }
        actual = actual->siguiente;
    }

    return resultados;
}

void mostrarPeliculasNombre(Movie** peliculas, int cantidadPeliculas)
{
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
    int indice = funcionHash(id, hash->size);
    Movie* actual = hash->table[indice];

    while (actual != null && actual->id != id)
    {
        actual = actual->siguiente;
    }

    return actual;
}

void remapearTabla(HashTable* hash, int newSize)
{
    int i;
    int nuevoIndice;

    Movie** nuevasPeliculas = malloc(newSize * sizeof(Movie*));

    for (i = 0 ; i < newSize ; i++)
    {
        nuevasPeliculas[i] = null;
    }

    for (i = 0 ; i < hash->size ; i++)
    {
        Movie* actual = hash->table[i];
        
        while (actual != null)
        {
            nuevoIndice = funcionHash(hash->folding(actual), newSize);
            Movie* siguiente = actual->siguiente;
            
            actual->siguiente = nuevasPeliculas[nuevoIndice];
            nuevasPeliculas[nuevoIndice] = actual;

            actual = siguiente;
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
    pelicula->siguiente = null;

    return pelicula;
}

void imprimirDatosTabla(HashTable* hash)
{
    printf("SIZE: %d | CANTIDAD ELEMENTOS: %d\n", hash->size, hash->amount_data);
    printf("FACTOR DE CARGA: %.2f\n\n", (float) hash->amount_data / (float) hash->size);

    return;
}