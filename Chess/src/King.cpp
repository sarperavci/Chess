#include "King.h"
#include <cstdlib>

King::King(int position, Color color) : Piece(position, PieceType::KING ,color) {}

int King::get_position()
{
    return position;
}

Color King::get_color()
{
    return color;
}

PieceType King::get_piece_type()
{
    return piece_type;
}

void King::move(int destination)
{
    if (!has_moved)
        has_moved = true;
    position = destination;
}

std::vector<int> King::get_valid_moves()
{
    std::vector<int> valid_moves;

    int directions[] = {-1, 1, -8, 8, -9, 9, -7, 7};  // -1 and 1: horizontal, -8 and 8: vertical, -9: top left, 9: bottom right, -7: top right, 7: bottom left
    int current_position;  

    for (int direction : directions) {
        current_position = position + direction;

        if (current_position < 0 || current_position > 63){
            continue;
        } 

        if ((direction == -1 || direction == 1) && (current_position / 8 != position / 8)) { // if they are not on the same horizontal level
            continue; 
        }

        if ((direction == -8 || direction == 8) && (current_position % 8 != position % 8)) { // if they are not on the same vertical level
            continue;  
        }

        if (direction == -9 || direction == 9 || direction == -7 || direction == 7){  // if they are not on the same cross level
            if(abs(current_position / 8 - position / 8) != abs(current_position % 8 - position % 8)){
                continue;
            }       
        }
        valid_moves.push_back(current_position);     
    }

    return valid_moves;
}

// The king has no special moves for capturing pieces, so the valid moves are the same as the normal moves.
std::vector<int> King::get_eatable_moves()
{
    return get_valid_moves();
}

bool King::is_move_blocked(int destination, bool is_eat, Piece **board)
{
    Piece *dest_piece = board[destination];

    // Check if the destination is occupied
    if (dest_piece != nullptr)
    {
        // If the destination is occupied by a piece of the same color, or it's an enemy piece and not a capture move, the move is blocked
        return dest_piece->get_color() == get_color() || !is_eat;
    }

    // If the destination is not occupied and it's a capture move, the move is blocked
    return is_eat;
}

bool King::get_has_moved() const {
    return has_moved;
}