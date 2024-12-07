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

std::vector<int> King::get_eatable_moves()
{
    std::vector<int> eatable_moves;

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
        eatable_moves.push_back(current_position);   
    }

    return eatable_moves;
}