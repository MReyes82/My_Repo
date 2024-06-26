#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Nodo* crearNodo(char valor, int index)
{
    Nodo* nuevo = malloc(sizeof(Nodo));
    nuevo->valor = valor;
    nuevo->index = index;
    nuevo->izquierda = nuevo->derecha = null;

    return nuevo;
}

void insertarNodo(Nodo** raiz, char valor, int index)
{
    // recorrido preorden para la insersion
    // revisamos el nodo primero, si es nolo insertamos directamente
    if (*raiz == null)
    {
        (*raiz) = crearNodo(valor, index);
        return;
    }
    // si no es nulo, vamos el subarbol izquierdo
    if (index < (*raiz)->index) // si el indice del nuevo nodo es menor al del nodo raiz
    { insertarNodo(&(*raiz)->izquierda, valor, index); }

    else if (index > (*raiz)->index) // si el indice del nuevo nodo es mayor al del nodo raiz
    { insertarNodo(&(*raiz)->derecha, valor, index); } // insertamos en subarbol derecho
}

void imprimirArbol(Nodo* nodo, int nivel)
{
    int i;

    if (nodo != null)
    {
        printf(" %c", nodo->valor); 

        if(nodo->derecha != null)
        {
            printf("\n");

            for (i = 0 ; i < nivel + 1 ; i++)
            {
                if (i == nivel) { printf(" |____R "); }

                else { printf(" |      ");}
            }
            imprimirArbol(nodo->derecha, nivel + 1);
        }

        if(nodo->izquierda != null)
        {
            printf("\n");

            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
            }

            printf("\n");

            for (i = 0 ; i < nivel + 1 ; i++)
            {
                if(i == nivel) { printf(" |____L "); }

                else { printf(" |      "); }
            }

            imprimirArbol(nodo->izquierda, nivel + 1);
        }
    }
}

void borrarArbol(Nodo** raiz) // borrar TODOS los nodos de un arbol
{
    // si terminamos de borrar, salimos de la funcion
    if (*raiz == null) { return; }
    // recorrido postorden para borrar el arbol

    //empezamos borrando el subarbol izquierdo
    borrarArbol(&(*raiz)->izquierda);
    // despues el derecho
    borrarArbol(&(*raiz)->derecha);
    // borramos (llamamos a la funcion free) el nodo raiz al ultimo
    free((*raiz));
    (*raiz) = null;
}

void recorridoEnOrden(Nodo* raiz)
{
    if (raiz != null)
    {
        recorridoEnOrden(raiz->izquierda);
        imprimirCharNodo(raiz->valor);
        recorridoEnOrden(raiz->derecha);
    }
}

void imprimirCharNodo(char caracterDelNodo)
{
    printf("%c", caracterDelNodo);
    return;
}

void printSpaces(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\n");
    }

    return;
}

NodoST* pop(Stack* st)
{
    if (st->cantidadNodos == 0) 
    {   
        printf("ERROR:underflow\n");
        return null; 
    }

    NodoST* out = st->cima;
    st->cima = st->cima->siguiente;
    st->cantidadNodos--;

    return out;
}

void push(Stack* st, char valor)
{
    if (st->cantidadNodos == st->maxTam)
    {
        printf("ERROR:overflow\n");
        return;
    }

    if (st->cima == null)
    {
        st->cima = initNodo(valor);
        st->cantidadNodos++;
        //return;
    }
    else
    {
        NodoST* nuevo = initNodo(valor);
        nuevo->siguiente = st->cima;
        st->cima = nuevo;
        st->cantidadNodos++;
    }
    
    return;
}

NodoST* initNodo(char valor)
{
    NodoST* nuevo = malloc(sizeof(NodoST));
    nuevo->valor = valor;
    nuevo->siguiente = null;

    return nuevo;
}

void vaciarStack(Stack* st)
{
    while (!estaVacio(st))
    {
        NodoST* temp = pop(st);
        free(temp);
    }

    return;
}

Stack initStack(int maxTam)
{
    Stack nuevo;
    nuevo.cima = null;
    nuevo.cantidadNodos = 0;
    nuevo.maxTam = maxTam;

    return nuevo;
}

bool esParBalanceado(char apertura, char cierre)
{
    return (apertura == '(' && cierre == ')');
}

bool esValida(char* expresion) // acepta expresions con o sin parentesis
{
    if (expresion == null)
    { 
        printf("ERROR: expresion nula\n");
        return false; 
    }

    Stack st = initStack(-1); // stack sin limite

    char chActual;

    for (int i = 0 ; i < strlen(expresion) ; i++)
    {
        chActual = expresion[i];

        if (chActual == '(')
        {
            push(&st, chActual);
            continue;
        }

        if (chActual == ')')
        {
            if (estaVacio(&st))
            {
                vaciarStack(&st);
                return false;
            }

            NodoST* temp = pop(&st);
            char chApertura = temp->valor;

            if (!esParBalanceado(chApertura, chActual))
            {
                vaciarStack(&st);
                return false;
            }
        }
    }

    int cantidadNodos = st.cantidadNodos;
    vaciarStack(&st);

    return (cantidadNodos == 0);
}

bool esOperador(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

bool estaVacio(Stack* st)
{
    return (st->cantidadNodos == 0);
}

void limpiarBufferDeEntrada(void)
{
    /*
    * esta funcion solo limpia el buffer de entrada para poder 
    * usar fgets despues de un scanf, aparantemente
    * no se puede usar fgets despues de un scanf
    * debido a que scanf deja un caracter de nueva linea '\n' en el buffer
    */
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    return;
}

char* infixToPostfix(char* infix)
{
    if (infix == null)
    { return null; }

    int tamExp = strlen(infix);

    Stack st = initStack(-1); // stack sin limite

    char* postfix = malloc(tamExp + 1);
    int j = 0;

    for (int i = 0 ; i < tamExp ; i++)
    {
        if (!esOperador(infix[i]))
        {
            postfix[j++] = infix[i];
        }
        else if (infix[i] == '(')
        {
            push(&st, infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (st.cima != null && st.cima->valor != '(')
            {
                postfix[j++] = pop(&st)->valor;
            }
            pop(&st);
        }
        else
        {
            while (st.cima != null && st.cima->valor != '(' && precedencia(infix[i]) <= precedencia(st.cima->valor))
            {
                postfix[j++] = pop(&st)->valor;
            }
            push(&st, infix[i]);
        }
    }

    while (st.cima != null)
    {
        postfix[j++] = pop(&st)->valor;
    }

    postfix[j] = '\0';

    return postfix;
}

int precedencia(char ch)
{
    if (ch == '^') 
    { return 3; }

    if (ch == '*' || ch == '/') 
    { return 2; }
    
    if (ch == '+' || ch == '-') 
    { return 1; }

    return -1;
}

int* obtenerIndice(char* infix, char* postfix)
{
    // TODO: arreglar problema con caracter '+' repetido
    if (infix == null || postfix == null)
    { return null; }

    int* indices = malloc((strlen(postfix)) * sizeof(int));
    bool chRepetidoEncontrado = true;

    int i = 0;

    while (postfix[i] != '\0')
    {
        char chActual = postfix[i];
        int j = 0;

        while (infix[j] != '\0')
        {
            if (chActual == infix[j])
            {
                if (chActual == '+' && chRepetidoEncontrado)
                {
                    j++;
                    chRepetidoEncontrado = false;
                    continue;
                }

                if (chActual == '+' && i < strlen(postfix) && !chRepetidoEncontrado)
                { chRepetidoEncontrado = true; }

                indices[i] = j;
                break;
            }
            j++;
        }
        i++;
    }

    return indices;
}
