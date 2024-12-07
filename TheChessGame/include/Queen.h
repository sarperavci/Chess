#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen : public Piece{
public:
    Queen(Color color, int position);
    int get_position() override;
    Color get_color() override;
    bool is_valid_move(int destination) override;
    void move(int destination) override;
    PieceType get_piece_type() override;
    std::vector<int> get_valid_moves() override;
}

#endif

