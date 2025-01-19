#include "Queen.h"
#include <cstdlib>

Queen::Queen(int position, Color color) : Piece(position, PieceType::QUEEN, color) {}

int Queen::get_position()
{
    return position;
}

Color Queen::get_color()
{
    return color;
}

PieceType Queen::get_piece_type()
{
    return piece_type;
}

void Queen::move(int destination)
{
    position = destination;
}

std::vector<int> Queen::get_valid_moves()
{
    std::vector<int> valid_moves;

    int directions[] = {-1, 1, -8, 8, -9, 9, -7, 7}; // -1 and 1: horizontal, -8 and 8: vertical, -9: top left, 9: bottom right, -7: top right, 7: bottom left
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

            if (direction == -9 || direction == 9 || direction == -7 || direction == 7)
            { // if they are not on the same cross level
                if (abs(current_position / 8 - position / 8) != abs(current_position % 8 - position % 8))
                {
                    break;
                }
            }

            valid_moves.push_back(current_position);
        }
    }

    return valid_moves;
}

// Queen has no special eatable moves, so we can just return the valid moves
std::vector<int> Queen::get_eatable_moves()
{
    return get_valid_moves();
}

bool Queen::is_move_blocked(int destination, bool is_eat, Piece **board)
{
    int position = get_position();
    int row_diff = abs(destination / 8 - position / 8);
    int col_diff = abs(destination % 8 - position % 8);

    // Determine the direction of the move
    int row_direction = (destination / 8 > position / 8) ? 1 : (destination / 8 < position / 8) ? -1
                                                                                                : 0;
    int col_direction = (destination % 8 > position % 8) ? 1 : (destination % 8 < position % 8) ? -1
                                                                                                : 0;

    // Check if the move is horizontal, vertical, or diagonal
    if (row_diff == col_diff || row_diff == 0 || col_diff == 0)
    {
        int current_row = position / 8 + row_direction;
        int current_col = position % 8 + col_direction;

        while (current_row != destination / 8 || current_col != destination % 8)
        {
            int current_position = current_row * 8 + current_col;
            if (board[current_position] != nullptr)
            {
                return true; // There is a piece blocking the queen's path
            }
            current_row += row_direction;
            current_col += col_direction;
        }
    }
    else
    {
        return true; // Invalid queen move
    }

    return board[destination] != nullptr && (board[destination]->get_color() == get_color() || !is_eat);
}