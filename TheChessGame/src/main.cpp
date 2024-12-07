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
    return 0;
}