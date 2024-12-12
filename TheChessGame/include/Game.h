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
    
    // Returns 0 if the move is invalid, 1 if the move is valid 
    int handle_move(int row, int col, int dest); 
    int handle_move(int src, int dest);
    void start_game();
    bool is_checkmate(Color current_color);
    bool is_stalemate();
    bool is_check();

    void update_game_status();

    GameBoard *get_game_board();
    Color get_current_turn();
    void set_current_turn(Color color);

};

#endif