#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

Book* init_book(char* title, char* genre, int year)
{
    Book* new_book = malloc(sizeof(Book));
    strcpy(new_book->title, title);
    strcpy(new_book->genre, genre);
    new_book->release_date = year;

    return new_book;
}

Node* init_node(Book* book_node)
{
    Node* new_node = malloc(sizeof(Node));
    new_node->element_book = book_node;
    new_node->next = NULL;

    return new_node;

}

Stack* init_book_box(void)
{
    Stack* box;
    Book books[BOX_SIZE] = 
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
    };

    box = init_stack(BOX_SIZE);
    
    for (int i = 0 ; i < BOX_SIZE ; i++)
    {
        Book* tmp = init_book(
            books[i].title, 
            books[i].genre, 
            books[i].release_date);

        push(box, tmp);
        //push(box, &books[i]);
    }
    
    return box;
}

Stack* init_stack(int length)
{
    Stack* new_stack = malloc(sizeof(Stack));

    new_stack->st_top = NULL;
    new_stack->next = NULL;

    new_stack->stack_lenth = length;
    new_stack->node_count = 0;

    return new_stack;

}

Stack_array init_stack_array(void)
{
    Stack_array new_stack_array;

    new_stack_array.top_book_stack = NULL;
    new_stack_array.stack_count = 0;

    return new_stack_array;
}

void print_stack(Stack* book_stack)
{
    if (isEmpty(book_stack))
    {
        printf("The stack is empty.\n");
        return;
    }

    Stack* aux = init_stack(book_stack->stack_lenth);

    while (!isEmpty(book_stack))
    {
        Book* tmp = pop(book_stack);
        print_book(tmp);
        push(aux, tmp);
    }

    while (!isEmpty(aux))
    {
        push(book_stack, pop(aux));
    }

    return;
}

bool isFull(Stack* st)
{
    if (st->stack_lenth == 0 || st->node_count < st->stack_lenth)
    {
        return false;
    }
    return true;
}

bool isEmpty(Stack* st)
{
    return (st->st_top == NULL);
}

//* Push a book into a struct of type "Stack"
void push(Stack* book_stack, Book* new_book)
{
    if (isFull(book_stack))
     return;

    if (book_stack->st_top == NULL) 
    {
        book_stack->st_top = init_node(new_book);

    } else {
        Node* new_node = init_node(new_book);
        new_node->next = book_stack->st_top;
        book_stack->st_top = new_node;
    }

    book_stack->node_count++;

    return;
}

//* Pop a book from a struct of type "Stack"
Book* pop(Stack* book_stack)
{
    if (isEmpty(book_stack))
    {
        return NULL;
    }

    Node* current = book_stack->st_top;
    Book* popBuffer = current->element_book;
    book_stack->st_top = book_stack->st_top->next;
    free(current);

    book_stack->node_count--;

    return popBuffer;
}

//* Pushes a struct of type "Stack" into a struct of type "Stack_array"
void push_stack(Stack_array* st_arr, Stack* st)
{
    //* Check if the stack array is initialized
    //* To avoid segfault
    if (st_arr == NULL)
    {
        return;
    }   

    if (st_arr->top_book_stack == NULL)
    {
        st_arr->top_book_stack = st;

    } else {
        Stack* new_stack = st;
        new_stack->next = st_arr->top_book_stack;
        st_arr->top_book_stack = new_stack;
    }

    st_arr->stack_count++;
    
    return;
}

//* Pops a struct of type "Stack" from a struct of type "Stack_array"
Stack* pop_stack(Stack_array* st_arr)
{
    if (st_arr == NULL)
    {
        return NULL;
    }

    if (st_arr->top_book_stack == NULL)
    {
        return NULL;
    }

    Stack* current = st_arr->top_book_stack;
    Stack* popBuffer = current;
    st_arr->top_book_stack = st_arr->top_book_stack->next;

    st_arr->stack_count--;

    return popBuffer;

}

void print_book(Book* book)
{
    printf("(%d) | ", book->release_date);
    printf("%s,  ", book->title);
    printf("%s\n", book->genre);
    
    return;
}

void empty_stack(Stack* stack)
{
    while (!isEmpty(stack))
    {
        Book* tmp = pop(stack);
        free(tmp);
    }

    return;
}

void genre_stackify(Stack_array* st_arr, Book* new_book)
{
    //* Check if the stack array is initialized
    //* To avoid segfault
    if (st_arr == NULL)
    {
        return;
    }
    //* We check if the stack array is empty
    //* If so, we create a new stack and push the book
    //* into it and push the stack into the stack array
    if (st_arr->top_book_stack == NULL)
    {
        Stack* new_stack = init_stack(0);
        push(new_stack, new_book);
        push_stack(st_arr, new_stack);

    } else {
        bool found = false;
        Stack_array aux = init_stack_array();
        Stack* tmp_stack = NULL;

        //* We look for a stack with the same genre as the new book
        while (st_arr->top_book_stack != NULL)
        {
            tmp_stack = pop_stack(st_arr);

            //* If strcmp returns 0, the strings are equal
            //* Therefore, we found a stack with the same genre
            //* so we push the book into it
            if (strcmp(tmp_stack->st_top->element_book->genre, new_book->genre) == 0)
            {
                found = true;
                push(tmp_stack, new_book);
            }
            //* if it doesn't return 0 we push the stack into the aux stack array
            //* and keep looking
            push_stack(&aux, tmp_stack);
        }
        //* If we didn't find a stack with the same genre
        //* we create a new stack and push the book into it
        if (!found)
        {
            Stack* new_stack = init_stack(0);
            push(new_stack, new_book);
            push_stack(&aux, new_stack);
        }

        //* We update the pointer of the stack array to the aux stack array
        *st_arr = aux;
    }
    
    return;
}

void date_stackify(Stack_array* st_arr, Book* new_book)
{
    //* Check if the stack array is initialized
    //* To avoid segfault
    if (st_arr == NULL)
    {
        return;
    }

    //* We check if the stack array is empty
    //* If so, we create a new stack and push the book
    //* into it and push the stack into the stack array
    if (st_arr->top_book_stack == NULL)
    {
        Stack* new_stack = init_stack(0);
        push(new_stack, new_book);
        push_stack(st_arr, new_stack);

    } else {
        bool found = false;
        Stack_array aux = init_stack_array();
        Stack* tmp_stack = NULL;

        //* We look for a stack with the same genre as the new book
        while (st_arr->top_book_stack != NULL)
        {
            tmp_stack = pop_stack(st_arr);

            //* if the release date is the same as the new book
            //* means we found the correct stack
            //* so we push the book into it
            if (tmp_stack->st_top->element_book->release_date == new_book->release_date)
            {
                found = true;
                push(tmp_stack, new_book);
            }
            //* if it doesn't equal we push the stack into the aux stack array
            //* and keep looking
            push_stack(&aux, tmp_stack);
        }
        //* If we didn't find a stack with the same date
        //* we create a new stack and push the book into it
        if (!found)
        {
            Stack* new_stack = init_stack(0);
            push(new_stack, new_book);
            push_stack(&aux, new_stack);
        }

        //* We update the pointer of the stack array to the aux stack array
        *st_arr = aux;

        //* We push the stacks from the aux stack array back into the original stack array
        /*while (aux->top_book_stack != NULL)
        {
            tmp_stack = pop_stack(aux);
            push_stack(st_arr, tmp_stack);
        }*/
    }

    return;
}

int sub_menu(char* print_text)
{
    int choose;
    printf("%s", print_text);
    scanf("\n%d", &choose);

    return choose;
}

void free_stack_arr(Stack_array* st_arr)
{
    if (st_arr == NULL)
    {
        return;
    }

    while (st_arr->top_book_stack != NULL)
    {
        Stack* tmp = pop_stack(st_arr);
        empty_stack(tmp);
        free(tmp);
    }

    return;
}

//* Print all the generated stacks in the stack array
void print_stack_array(Stack_array* st_arr, Stacked_by stacked_by)
{
    if (st_arr == NULL)
    {
        return;
    }

    Stack_array aux = init_stack_array();
    Stack* tmp_stack = NULL;
    int iterator = 0;

    while (st_arr->top_book_stack != NULL)
    {
        printf("It enters while cycle\n");
        tmp_stack = pop_stack(st_arr);
        
        if (stacked_by == GENRE)
        {
            printf("\n[%d] %s\n", iterator, tmp_stack->st_top->element_book->genre);

        } else if (stacked_by == YEAR) {
            printf("\n[%d]: %d\n", iterator, tmp_stack->st_top->element_book->release_date);
        }
        iterator++;

        push_stack(&aux, tmp_stack);
    }

    *st_arr = aux;

    /*while (aux->top_book_stack != NULL)
    {
        tmp_stack = pop_stack(aux);
        push_stack(st_arr, tmp_stack);
    }*/

    return;
}

//* Get the selected stacked based in the index
//* it has in the stack array
Stack* get_stack(Stack_array* st_arr, int choose)
{
    if (st_arr == NULL)
    {
        return NULL;
    }
    //* variable used to know how many stacks we moved
    //* until we reach the selected stack
    int moved_positions = 0;

    Stack_array aux = init_stack_array();
    Stack* tmp_stack = NULL;
    Stack* choosen_stack = NULL;

    //* We traverse the stack array until we reach the selected stack
    while (st_arr->top_book_stack != NULL)
    {
        tmp_stack = pop_stack(st_arr);

        //* if we reach the selected stack we save it
        if (moved_positions == choose)
        {
            choosen_stack = tmp_stack;
        }

        moved_positions++;
        push_stack(&aux, tmp_stack);
    }

    //* We assign the stack array to the aux stack array
    *st_arr = aux;

    return choosen_stack;
}

