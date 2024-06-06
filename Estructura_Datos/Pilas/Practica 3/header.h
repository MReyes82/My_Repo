#pragma once

#include <stdbool.h>

#define BOX_SIZE 44

typedef struct book 
{
    char title[64];
    char genre[32];
    int release_date;   
    
} Book;

typedef struct node
{
    Book* element_book;
    struct Node* next;

} Node;

typedef struct stack
{
    Node* st_top;
    int stack_lenth;
    int node_count;

} Stack;

typedef struct Stack_Array
{
    Stack book_stack;
    int stack_count;

} Stack_array;

Book* init_book(char* title, char* genre, int year);
Node* init_node(Book* book_node);
Stack* init_book_box(void);
Stack* init_stack(int length);
void print_stack(Stack* book_stack);
bool isFull(Stack* st);
bool isEmpty(Stack* st);
void push(Stack* book_stack, Book* new_book);
Book* pop(Stack* book_stack);
void push_stack(Stack_array* st_arr, Stack* st);
Book* pop_stack(Stack_array* st_arr);
void empty_stack(Stack* stack);
void genre_stackify(Stack_array* st_arr, Book* new_book);
void date_stackify(Stack_array* st_arr, Book* new_book);
int sub_menu(char* print_text);

void free_stack(Stack* st);
void free_node(Node* node);
