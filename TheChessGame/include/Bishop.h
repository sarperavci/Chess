#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop : public Piece
{
public:
    Bishop(int position, Color color);
    int get_position() override;
    Color get_color() override;
    void move(int destination) override;
    PieceType get_piece_type() override;
    std::vector<int> get_valid_moves() override;
    std::vector<int> get_eatable_moves() override;
    bool is_move_blocked(int destination, bool is_eat, Piece **board) override;
};

#endif