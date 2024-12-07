#ifndef GAME_h
#define GAME_h

#include "GameBoard.h"

class Game
{
private:
    GameBoard *game_board;
    Color current_turn;

public:
    Game();
    ~Game();
    void change_turn();
    void handle_move(int row, int col, int dest); 
    void handle_move(int src, int dest);
    void start_game();
    bool is_checkmate();
    bool is_stalemate();
    bool is_check();
    bool is_draw();

    GameBoard *get_game_board();
    Color get_current_turn();

};

#endif