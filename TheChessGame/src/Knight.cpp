#include "Knight.h"

Knight::Knight(int position, Color color) : Piece(position, PieceType::KNIGHT ,color) {}

int Knight::get_position()
{
    return position;
}

Color Knight::get_color()
{
    return color;
}

PieceType Knight::get_piece_type()
{
    return piece_type;
}

void Knight::move(int destination)
{
    position = destination;
}

std::vector<int> Knight::get_valid_moves()
{
    std::vector<int> valid_moves;

    int directions[] = {-10, 6, -6, 10, -17, 17, -15, 15};    // index change of L moves. 
    int new_position;

    for (int direction : directions) {
        new_position = position + direction; 

        if (new_position < 0 || new_position > 63){
            continue;
        }

        if(direction == -6){  // L movement: first 1 up, then 2 right
            if(new_position / 8 == position / 8){  // continue if it comes to same horizontal level
                continue;
            }
        }

        if(direction == 6){  // L movement: first 2 left, then 1 down
            if(new_position / 8 == position / 8){  // continue if it comes to same horizontal level
                continue;
            }
        }

        if(direction == -10){  // L movement: first 1 up, then 2 left
            if((new_position / 8) - (position / 8) == -2){  // continue if the new position is 2 rows above the previous position
                continue;
            }  
        }

        if(direction == 10){   // L movement: first 2 right, then 1 down
            if((new_position / 8) - (position / 8) == 2){  // continue if the new position is 2 rows down the previous position
                continue;
            }
        }

        if(direction == -17){  // L movement: first 2 up, then 1 left
            if((new_position / 8) - (position / 8) != -2){  // continue if the new position is not 2 rows above the previous position
                continue;
            }
        }

        if(direction == 17){   // L movement: first 1 right, then 2 down
            if((new_position / 8) - (position / 8) != 2){  // continue if the new position is not 2 rows down the previous position
                continue;
            }
        }

        if(direction == -15){  // L movement: first 2 up, then 1 right
            if((new_position / 8) - (position / 8) != -2){  // continue if the new position is not 2 rows above the previous position
                continue;
            }
        }

        if(direction == 15){   // L movement: first 1 left, then 2 down
            if((new_position / 8) - (position / 8) != 2){  // continue if the new position is not 2 rows down the previous position
                continue;
            }
        }

        valid_moves.push_back(new_position);
    }

    return valid_moves;
}

std::vector<int> Knight::get_eatable_moves()
{
    std::vector<int> eatable_moves;

    int directions[] = {-10, 6, -6, 10, -17, 17, -15, 15};    // index change of L moves. 
    int new_position;

    for (int direction : directions) {
        new_position = position + direction; 

        if (new_position < 0 || new_position > 63){
            continue;
        }

        if(direction == -6){  
            if(new_position / 8 == position / 8){  
                continue;
            }
        }

        if(direction == 6){  
            if(new_position / 8 == position / 8){  
                continue;
            }
        }

        if(direction == -10){  
            if((new_position / 8) - (position / 8) == -2){  
                continue;
            }  
        }

        if(direction == 10){  
            if((new_position / 8) - (position / 8) == 2){  
                continue;
            }
        }

        if(direction == -17){ 
            if((new_position / 8) - (position / 8) != -2){ 
                continue;
            }
        }

        if(direction == 17){   
            if((new_position / 8) - (position / 8) != 2){  
                continue;
            }
        }

        if(direction == -15){  
            if((new_position / 8) - (position / 8) != -2){  
                continue;
            }
        }

        if(direction == 15){  
            if((new_position / 8) - (position / 8) != 2){  
                continue;
            }
        }

        eatable_moves.push_back(new_position);
    }   

    return eatable_moves;
}