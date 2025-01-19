#ifndef GAME_h
#define GAME_h

#include "GameBoard.h"

class Game
{
private:
    GameBoard *game_board; ///< Pointer to the game board
    Color current_turn;    ///< Current turn color

public:
    Game();

    ~Game();

    void change_turn();

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