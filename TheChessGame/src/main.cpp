#include <iostream>
#include <vector>
#include <algorithm>
#include "GameBoard.h"
int main()
{
    // Create a new game board
    GameBoard *game_board = new GameBoard();

    // Initialize the game board
    game_board->initiate_board();
    game_board->print_board();
    
    while (1)
    {
        // Get user input for the move
       int position, destination;
       std::cout << "Enter the position and destination: ";
       std::cin >> position >> destination;

        // Move the piece
        game_board->move_piece(position, destination);
        game_board->print_board();
       
    }


    return 0;
}