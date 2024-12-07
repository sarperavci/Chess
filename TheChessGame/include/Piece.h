#include <vector>
#ifndef PIECE_H
#define PIECE_H

enum class Color
{
    WHITE,
    BLACK
};
enum class PieceType
{
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN
};

// Virtual class for a chess piece
class Piece
{
protected:
    int position;
    PieceType piece_type;
    Color color;

public:
    Piece(int position, PieceType piece_type, Color color) : position(position), piece_type(piece_type), color(color) {}
    virtual ~Piece() {} 
    virtual int get_position() = 0;
    virtual Color get_color() = 0;
    virtual PieceType get_piece_type() = 0;

    virtual void move(int destination) = 0;
    
    virtual std::vector<int> get_valid_moves() = 0;
    virtual std::vector<int> get_eatable_moves() = 0;
    bool is_valid_move(int destination);
    bool is_valid_eat(int destination);
};

#endif