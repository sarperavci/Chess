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
    void check_pawn_promotion(int position, Piece* piece);
    void check_en_passant(int position, Piece* piece, int dest);
    void check_castling(int position, Piece* piece, int dest);
    void update_game_status();

    GameBoard *get_game_board();
    Color get_current_turn();

};

#endif