#include "Piece.h"

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

// GAMEBOARD FOR THE CHESS GAME

// Chessboard representation:
// The chessboard is represented as a single array of 64 integers (0 to 63).
// Each square on the chessboard is mapped to an integer:
// a1 is 0, a2 is 8, ..., h8 is 63.
// The mapping is done row by row from bottom to top, left to right.

class GameBoard
{
private:
    Piece *board[64];

public:
    GameBoard();
    ~GameBoard();
    Piece *get_piece(int position);
    Piece *get_piece(int row, int col);

    void set_piece(int position, Piece *piece);
    void set_piece(int row, int col, Piece *piece);

    bool is_move_blocked(Piece *piece, int destination, bool is_eat);
    bool is_bishop_move_blocked(Piece *piece, int destination, bool is_eat);
    bool is_pawn_move_blocked(Piece *piece, int destination, bool is_eat);
    bool is_knight_move_blocked(Piece *piece, int destination, bool is_eat);
    bool is_king_move_blocked(Piece *piece, int destination, bool is_eat);
    bool is_queen_move_blocked(Piece *piece, int destination, bool is_eat);
    bool is_rook_move_blocked(Piece *piece, int destination, bool is_eat);

    void move_piece(Piece *piece, int destination);
    void move_piece(Piece *piece, int row, int col);
    void move_piece(int position, int destination);

    void remove_piece(int position);
    void remove_piece(int row, int col);

    void initiate_board();
    void clear_board();
    void refresh_board();

    bool is_check(Color color);

    void print_board(); // For debugging purposes
};

#endif