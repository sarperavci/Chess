#include "Pawn.h"

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

bool Pawn::is_valid_move(int destination)
{
    std::vector<int> valid_moves = get_valid_moves();
    for (int i = 0; i < valid_moves.size(); i++)
    {
        if (destination == valid_moves[i])
        {
            return true;
        }
    }
}

void Pawn::move(int destination)
{
    if (!has_moved)
        has_moved = true;

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

bool Pawn::is_valid_eat(int destination)
{
    std::vector<int> eatable_moves = get_eatable_moves();
    for (int i = 0; i < eatable_moves.size(); i++)
    {
        if (destination == eatable_moves[i])
        {
            return true;
        }
    }
    return false;
}