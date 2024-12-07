#include "Bishop.h"
#include <cstdlib>

Bishop::Bishop(int position, Color color) : Piece(position, PieceType::BISHOP ,color) {}

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

    int directions[] = {-9, 9, -7, 7};  // -9: top left, 9: bottom right, -7: top right, 7: bottom left
    int current_position;  

    for (int direction : directions) {
        current_position = position;

        while (true) {
            current_position += direction; 

            if (current_position < 0 || current_position > 63){
                break;
            } 

 
            if(abs(current_position / 8 - position / 8) != abs(current_position % 8 - position % 8)){
                break;  // if they are not on the same cross level
            }

            valid_moves.push_back(current_position);
        }
    }

    return valid_moves;
}

std::vector<int> Bishop::get_eatable_moves()
{
    std::vector<int> eatable_moves;

    int directions[] = {-9, 9, -7, 7}; 
    int current_position;  

    for (int direction : directions) {
        current_position = position;

        while (true) {
            current_position += direction; 

            if (current_position < 0 || current_position > 63){
                break;
            } 

 
            if(abs(current_position / 8 - position / 8) != abs(current_position % 8 - position % 8)){
                break;  // if they are not on the same cross level
            }

            eatable_moves.push_back(current_position);
        }
    }

    return eatable_moves;
}