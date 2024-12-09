#include "Rook.h"
#include <stdlib.h>

Rook::Rook(int position, Color color) : Piece(position, PieceType::ROOK, color) {}

int Rook::get_position()
{
    return position;
}

Color Rook::get_color()
{
    return color;
}

PieceType Rook::get_piece_type()
{
    return piece_type;
}

void Rook::move(int destination)
{
    if (!has_moved)
        has_moved = true;
    position = destination;
}

std::vector<int> Rook::get_valid_moves()
{
    std::vector<int> valid_moves;

    int directions[] = {-1, 1, -8, 8}; // vertical and horizontal moves
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

            if ((direction == -1 || direction == 1) && (current_position / 8 != position / 8))
            { // if they are not on the same horizontal level
                break;
            }

            if ((direction == -8 || direction == 8) && (current_position % 8 != position % 8))
            { // if they are not on the same vertical level
                break;
            }

            valid_moves.push_back(current_position);
        }
    }

    return valid_moves;
}

std::vector<int> Rook::get_eatable_moves()
{
    std::vector<int> eatable_moves;

    int directions[] = {-1, 1, -8, 8}; // vertical and horizontal moves
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

            if ((direction == -1 || direction == 1) && (current_position / 8 != position / 8))
            { // if they are not on the same horizontal level
                break;
            }

            if ((direction == -8 || direction == 8) && (current_position % 8 != position % 8))
            { // if they are not on the same vertical level
                break;
            }

            eatable_moves.push_back(current_position);
        }
    }

    return eatable_moves;
}

bool Rook::is_move_blocked(int destination, bool is_eat, Piece **board)
{
    int position = get_position();
    int row_diff = abs(destination / 8 - position / 8);
    int col_diff = abs(destination % 8 - position % 8);

    // Rooks move horizontally or vertically, so either row_diff or col_diff must be zero
    if (row_diff != 0 && col_diff != 0)
    {
        return true; // Invalid rook move
    }

    int row_direction = (destination / 8 > position / 8) ? 1 : (destination / 8 < position / 8) ? -1
                                                                                                : 0;
    int col_direction = (destination % 8 > position % 8) ? 1 : (destination % 8 < position % 8) ? -1
                                                                                                : 0;

    int current_row = position / 8 + row_direction;
    int current_col = position % 8 + col_direction;

    while (current_row != destination / 8 || current_col != destination % 8)
    {
        int current_position = current_row * 8 + current_col;
        if (board[current_position] != nullptr)
        {
            return true; // There is a piece blocking the rook's path
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

    return false; // No pieces are blocking the rook's path
}

bool Rook::get_has_moved() const
{
    return has_moved;
}