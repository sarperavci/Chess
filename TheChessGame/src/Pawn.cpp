#include "Pawn.h"
#include <cstdlib>

Pawn::Pawn(int position, Color color) : Piece(position, PieceType::PAWN, color) {}

int Pawn::get_position()
{
    return position;
}

Color Pawn::get_color()
{
    return color;
}

PieceType Pawn::get_piece_type()
{
    return piece_type;
}

void Pawn::move(int destination)
{
    if (!has_moved)
        has_moved = true;
    
    if (abs(destination - position) == 16)
        has_moved_two_squares = true;

    position = destination;
}

std::vector<int> Pawn::get_valid_moves()
{
    std::vector<int> valid_moves;

    if (color == Color::WHITE)
    {
        // Move one square forward
        if (position + 8 <= 63)
        {
            valid_moves.push_back(position + 8);
        }
        // Move two squares forward from initial position
        if (!has_moved && position + 16 <= 63)
        {
            valid_moves.push_back(position + 16);
        }
    }
    else // The pawn is black
    {
        // Move one square forward
        if (position - 8 >= 0)
        {
            valid_moves.push_back(position - 8);
        }
        // Move two squares forward from initial position
        if (!has_moved && position - 16 >= 0)
        {
            valid_moves.push_back(position - 16);
        }
    }

    return valid_moves;
}

std::vector<int> Pawn::get_eatable_moves()
{
    std::vector<int> eatable_moves;

    if (color == Color::WHITE)
    {
        // Eat diagonally left
        if (position + 7 <= 63 && (position % 8 != 0))
        {
            eatable_moves.push_back(position + 7);
        }
        // Eat diagonally right
        if (position + 9 <= 63 && (position % 8 != 7))
        {
            eatable_moves.push_back(position + 9);
        }
    }
    else
    {
        // Eat diagonally left
        if (position - 9 >= 0 && (position % 8 != 0))
        {
            eatable_moves.push_back(position - 9);
        }
        // Eat diagonally right
        if (position - 7 >= 0 && (position % 8 != 7))
        {
            eatable_moves.push_back(position - 7);
        }
    }

    return eatable_moves;
}
bool Pawn::is_move_blocked(int destination, bool is_eat, Piece **board)
{
    int position = get_position();
    Color color = get_color();
    int direction = (color == Color::WHITE) ? 1 : -1;

    // Check if the move is a forward move
    if (!is_eat)
    {
        if (destination == position + 8 * direction)
        {
            return board[destination] != nullptr;
        }
        if ((position / 8 == 1 && color == Color::WHITE) || (position / 8 == 6 && color == Color::BLACK))
        {
            if (destination == position + 16 * direction)
            {
                return board[position + 8 * direction] != nullptr || board[destination] != nullptr;
            }
        }
    }
    else
    {
        // Check if the move is a diagonal capture
        if ((destination == position + 7 * direction && position % 8 != 0) ||
            (destination == position + 9 * direction && position % 8 != 7))
        {
            return board[destination] == nullptr || board[destination]->get_color() == color;
        }
    }

    // If none of the above conditions are met, the move is invalid for a pawn
    return true;
}
bool Pawn::get_has_moved() const
{
    return has_moved;
}

bool Pawn::get_has_moved_two_squares() const
{
    return has_moved_two_squares;
}
