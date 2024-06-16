#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "grid.h"

typedef struct Game
{
    
    Player* winner;

    int total_turns;

    bool is_draw;
    bool is_over;
    bool has_someone_won;

} Game;

Game init_game_struct(void);
void game_loop(Game* game, Player* player1, Player* player2);
void play_turn(Game* game, Player* current_turn_player, Grid* grid);
void print_winner(Game* game);
void print_draw(Game* game);
void insert_player_input(Grid* grid, Player* current_palyer_turn, int palyer_input);
bool check_if_current_player_won(Grid* grid);

#endif // GAME_H