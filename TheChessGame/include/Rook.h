#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook : public Piece
{
public:
    Rook(int position, Color color);
    int get_position() override;
    Color get_color() override;
    bool is_valid_move(int destination) override;
    void move(int destination) override;
    PieceType get_piece_type() override;
    std::vector<int> get_valid_moves() override;
};

#endif