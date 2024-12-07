#include <vector>

#include "Piece.h"

bool Piece::is_valid_move(int destination)
{
    std::vector<int> valid_moves = get_valid_moves();
    for (std::size_t i = 0; i < valid_moves.size(); i++)
    {
        if (destination == valid_moves[i])
        {
            return true;
        }
    }
    return false;
}

bool Piece::is_valid_eat(int destination)
{
    std::vector<int> eatable_moves = get_eatable_moves();
    for (std::size_t i = 0; i < eatable_moves.size(); i++)
    {
        if (destination == eatable_moves[i])
        {
            return true;
        }
    }
    return false;
}