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

    int move_piece(Piece *piece, int destination);
    int move_piece(Piece *piece, int row, int col);
    int move_piece(int position, int destination);

    void remove_piece(int position);
    void remove_piece(int row, int col);

    void initiate_board();
    void clear_board();
    void refresh_board();

    bool is_check(Color color);

    // void check_pawn_promotion(int position, Piece* piece);
    bool is_pawn_promotion(int position, Piece *piece);
    void promote_pawn(int position, Piece *piece, PieceType new_type);

    bool is_en_passant(int position, Piece *piece, int dest);
    void perform_en_passant(int position, Piece *piece, int dest);

    bool can_castle(int position, Piece *piece, int dest);
    void perform_castling(int position, Piece *piece, int dest);

    void print_board(); // For debugging purposes
};

#endif