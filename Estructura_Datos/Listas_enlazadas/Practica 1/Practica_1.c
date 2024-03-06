#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include "practica_1_header.h"
#include <stdbool.h>

int main (void)
{
    /*
    Nodo *primeraListaAsc;
    Nodo *primeraListaDes;
    Nodo *segundaListaAsc;
    Nodo *segundaListaDes;
    */

    int const numeroArticulos = 15; 
    int opcion;
    bool sigueCorriendo = true;
    Auto listaDatosAOrdenar[15] = 
    {
        {2000, "Corolla", 4}, //1
        {2014, "Civic", 4},   // 2
        {2005, "Clio", 4},    // 3
        {2024, "Versa", 4},  // 4
        {2020, "Silverado", 8}, //5
        {1999, "Cavalier", 4}, //6
        {1973, "Mustang", 8},  //7
        {2016, "370Z", 6},   //8
        {1996, "Supra", 6},  //9
        {2015, "330i", 4},  //10
        {2019, "CRV", 4}, //11
        {2010, "Camry", 6}, //12
        {2017, "Accord", 6}, //13
        {2017, "GTR", 6}, //14
        {2004, "Blazer", 8} //15
    };

    printf("Iniciando.\n");
    while (sigueCorriendo)
    {
        printf("\n--------------MENU-------------\n");
        printf("[1] Ordenar lista por año, ascendente.\n");
        printf("[2] Ordenar lista por año, descendente.\n");
        printf("[3] Ordenar lista por cantidad de cilindros, ascendente.\n");
        printf("[4] Ordenar lista por cantidad de cilindros, descendente.\n");
        printf("[5] Terminar programa.\n");
        printf("> ");
        scanf("\n%d", &opcion);
        int i;

        switch (opcion)
        {
        case 1:
            system("clear");
            Nodo *primeraListaAsc = NULL;

            for (i = 0 ; i < numeroArticulos ; i++)
            {
               printf("Agregando elemento %d\n", i+1);
               insertarNodoEnLista(&primeraListaAsc, listaDatosAOrdenar[i].year,
               listaDatosAOrdenar[i].modelo, listaDatosAOrdenar[i].cilindrosMotor);
            }

            printf("\nLista desordenada: \n");
            imprimirNodos(primeraListaAsc);
            ordenarListaPorYear(&primeraListaAsc, '>');

            printf("\nLista ordenada: \n");
            imprimirNodos(primeraListaAsc);

            printf("\nLiberando memoria...\n");
            liberarMemoriaNodos(&primeraListaAsc);

            break;
        
        case 2:
            system("clear");
            Nodo *primeraListaDes = NULL;

            for (i = 0 ; i < numeroArticulos ; i++)
            {
               printf("Agregando elemento %d\n", i+1);
               insertarNodoEnLista(&primeraListaDes, listaDatosAOrdenar[i].year,
               listaDatosAOrdenar[i].modelo, listaDatosAOrdenar[i].cilindrosMotor);
            }

            printf("\nLista desordenada: \n");
            imprimirNodos(primeraListaDes);
            ordenarListaPorYear(&primeraListaDes, '<');

            printf("\nLista ordenada: \n");
            imprimirNodos(primeraListaDes);

            printf("\nLiberando memoria...\n");
            liberarMemoriaNodos(&primeraListaDes);

            break;

        case 3:
            system("clear");
            Nodo *segundaListaAsc = NULL;

            for (i = 0 ; i < numeroArticulos ; i++)
            {
               printf("Agregando elemento %d\n", i+1);
               insertarNodoEnLista(&segundaListaAsc, listaDatosAOrdenar[i].year,
               listaDatosAOrdenar[i].modelo, listaDatosAOrdenar[i].cilindrosMotor);
            }

            printf("\nLista desordenada: \n");
            imprimirNodos(segundaListaAsc);
            ordenarListaPorCilindros(&segundaListaAsc, '>');

            printf("\nLista ordenada: \n");
            imprimirNodos(segundaListaAsc);

            printf("\nLiberando memoria...\n");
            liberarMemoriaNodos(&segundaListaAsc);

            break;
        
        case 4:
            system("clear");
            Nodo *segundaListaDes = NULL;

            for (i = 0 ; i < numeroArticulos ; i++)
            {
               printf("Agregando elemento %d\n", i+1);
               insertarNodoEnLista(&segundaListaDes, listaDatosAOrdenar[i].year,
               listaDatosAOrdenar[i].modelo, listaDatosAOrdenar[i].cilindrosMotor);
            }

            printf("\nLista desordenada: \n");
            imprimirNodos(segundaListaDes);
            ordenarListaPorCilindros(&segundaListaDes, '<');

            printf("\nLista ordenada: \n");
            imprimirNodos(segundaListaDes);

            printf("\nLiberando memoria...\n");
            liberarMemoriaNodos(&segundaListaDes);

            break;

        case 5:
            sigueCorriendo = false;
            printf("Hasta luego.\n");
            break;

        default:
            printf("ERROR, OPCION NO VALIDA\n");
            break;
        }
    }
    
    return 0;
}
