#pragma once

#include <stdbool.h>

#define BOX_SIZE 44

typedef enum 
{
    YEAR,
    GENRE

} Stacked_by;

typedef struct Book 
{
    char title[50];
    char genre[40];
    int release_date;   
    
} Book;

typedef struct Node
{
    Book* element_book;
    struct Node* next;

} Node;

typedef struct Stack
{
    Node* st_top;
    struct Stack* next;

    int stack_lenth;
    int node_count;

} Stack;

typedef struct Stack_array
{
    Stack* top_book_stack;
    int stack_count;

} Stack_array;

Book* init_book(char* title, char* genre, int year);
Node* init_node(Book* book_node);
Stack* init_book_box(void);
Stack* init_stack(int length);
Stack_array init_stack_array(void);

void print_stack(Stack* book_stack);
bool isFull(Stack* st);
bool isEmpty(Stack* st);
void push(Stack* book_stack, Book* new_book);
Book* pop(Stack* book_stack);
void empty_stack(Stack* stack);

void push_stack(Stack_array* st_arr, Stack* st);
Stack* pop_stack(Stack_array* st_arr);
void free_stack_arr(Stack_array* st_arr);
void genre_stackify(Stack_array* st_arr, Book* new_book);
void date_stackify(Stack_array* st_arr, Book* new_book);

void print_book(Book* book);
int sub_menu(char* print_text);

void print_stack_array(Stack_array* st_arr, Stacked_by stacked_by);
Stack* get_stack(Stack_array* st_arr, int choose);

