#include "Bishop.h"
#include <cstdlib>

Bishop::Bishop(int position, Color color) : Piece(position, PieceType::BISHOP, color) {}

int Bishop::get_position()
{
    return position;
}

Color Bishop::get_color()
{
    return color;
}

PieceType Bishop::get_piece_type()
{
    return piece_type;
}

void Bishop::move(int destination)
{
    position = destination;
}

std::vector<int> Bishop::get_valid_moves()
{
    std::vector<int> valid_moves;

    int directions[] = {-9, 9, -7, 7}; // -9: top left, 9: bottom right, -7: top right, 7: bottom left
    int current_position;

    for (int direction : directions)
    {
        current_position = position;

        while (true)
        {
            current_position += direction;

            if (current_position < 0 || current_position > 63)
            {
                break;
            }

            if (abs(current_position / 8 - position / 8) != abs(current_position % 8 - position % 8))
            {
                break; // if they are not on the same cross level
            }

            valid_moves.push_back(current_position);
        }
    }

    return valid_moves;
}

std::vector<int> Bishop::get_eatable_moves()
{
    return get_valid_moves();
}

bool Bishop::is_move_blocked(int destination, bool is_eat, Piece **board)
{
    int position = get_position();
    int row_diff = abs(destination / 8 - position / 8);
    int col_diff = abs(destination % 8 - position % 8);

    // Bishops move diagonally, so the row difference and column difference must be equal
    if (row_diff != col_diff)
    {
        return true; // Invalid bishop move
    }

    int row_direction = (destination / 8 > position / 8) ? 1 : -1;
    int col_direction = (destination % 8 > position % 8) ? 1 : -1;

    int current_row = position / 8 + row_direction;
    int current_col = position % 8 + col_direction;

    while (current_row != destination / 8 || current_col != destination % 8)
    {
        int current_position = current_row * 8 + current_col;
        if (board[current_position] != nullptr)
        {
            return true; // There is a piece blocking the bishop's path
        }
        current_row += row_direction;
        current_col += col_direction;
    }

    // Check if the destination is occupied by a piece of the same color
    if (board[destination] != nullptr)
    {
        if (board[destination]->get_color() == get_color())
        {
            return true; // The move is blocked by a piece of the same color
        }
        else if (!is_eat)
        {
            return true; // The move is blocked by an enemy piece and it's not a capture move
        }
    }

    return false; // No pieces are blocking the bishop's path
}
