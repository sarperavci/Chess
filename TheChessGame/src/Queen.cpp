#include "Queen.h"
#include <cstdlib>

Queen::Queen(int position, Color color) : Piece(position, PieceType::Queen ,color) {}

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

bool Queen::is_valid_move(int destination)
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

void Queen::move(int destination)
{
    position = destination;
}

std::vector<int> Queen::get_valid_moves()
{
    std::vector<int> valid_moves;

    int directions[] = {-1, 1, -8, 8, -9, 9, -7, 7};  // -1 and 1: horizontal, -8 and 8: vertical, -9: top left, 9: bottom right, -7: top right, 7: bottom left
    int current_position;  

    for (int direction : directions) {
        current_position = position;

        while (true) {
            current_position += direction; 

            if (current_position < 0 || current_position > 63){
                break;
            } 

            if ((direction == -1 || direction == 1) && (current_position / 8 != position / 8)) { // if they are not on the same horizontal level
                break; 
            }

            if ((direction == -8 || direction == 8) && (current_position % 8 != position % 8)) { // if they are not on the same vertical level
                break;  
            }

            if (direction == -9 || direction == 9 || direction == -7 || direction == 7){  // if they are not on the same cross level
                if(abs(current_position / 8 - position / 8) != abs(current_position % 8 - position % 8)){
                    break;
                }       
            }

            valid_moves.push_back(current_position);
        }
    }

    return valid_moves;
}