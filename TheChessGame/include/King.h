#ifndef KING_H
#define KING_H
#include "Piece.h"

class King : public Piece
{
private:
    bool has_moved = false;

public:
    King(int position, Color color);
    int get_position() override;
    Color get_color() override;
    void move(int destination) override;
    PieceType get_piece_type() override;
    std::vector<int> get_valid_moves() override;
    std::vector<int> get_eatable_moves() override;
    bool get_has_moved() const;
};

#endif