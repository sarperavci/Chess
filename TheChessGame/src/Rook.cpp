#include "Rook.h"

Rook::Rook(int position, Color color) : Piece(position, PieceType::ROOK ,color) {}

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

bool Rook::is_valid_move(int destination)
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

void Rook::move(int destination)
{
    position = destination;
}

std::vector<int> Rook::get_valid_moves()
{
    std::vector<int> valid_moves;

    int directions[] = {-1, 1, -8, 8};  // vertical and horizontal moves
    int current_position; 

        for(int direction : directions){
            current_position = position;

            while(true){
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

                valid_moves.push_back(current_position);    
            }
        }

    return valid_moves;
}

std::vector<int> Rook::get_eatable_moves()
{
    std::vector<int> eatable_moves;

    int directions[] = {-1, 1, -8, 8};  // vertical and horizontal moves
    int current_position; 

        for(int direction : directions){
            current_position = position;

            while(true){
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

                eatable_moves.push_back(current_position);    
            }
        }

    return eatable_moves;
}

bool Rook::is_valid_eat(int destination)
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