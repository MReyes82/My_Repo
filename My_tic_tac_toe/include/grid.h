#ifndef GRID_H
#define GRID_H

#include <stdbool.h>

/*
* Grid structure, choose this approach
* instead of a 2D array to make it clearer
*/ 

typedef struct Grid 
{
    char top_left;
    char top_mid;
    char top_right;

    char middle_left;
    char center;
    char middle_right;

    char bottom_left;
    char bottom_mid;
    char bottom_right;

    bool is_full;

} Grid;

Grid* init_grid(void);
void print_grid(Grid* grid);
void free_grid(Grid* grid);

#endif // GRID_H