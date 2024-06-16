#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

typedef struct Player
{
    char* name;
    char symbol;

    bool is_winner;
}

#endif // PLAYER_H