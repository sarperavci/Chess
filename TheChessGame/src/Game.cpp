#include "Game.h"
#include "GameBoard.h"
#include "Pawn.h"
#include "King.h"
#include "Rook.h"
#include "Piece.h"
#include <vector>
#include <iostream>
#include "utils.h"
using namespace std;

Game::Game()
{
    game_board = new GameBoard();
    current_turn = Color::WHITE; // game starts with white
}

Game::~Game()
{
    delete game_board;
}

void Game::change_turn()
{
    if (current_turn == Color::WHITE)
    {
        current_turn = Color::BLACK;
    }
    else
    {
        current_turn = Color::WHITE;
    }
}

int Game::handle_move(int row, int col, int dest)
{
    int position = indexes2DToInt(row, col);
    return handle_move(position, dest);
}

int Game::handle_move(int src, int dest)
{
    int status = game_board->handle_move(src, dest);
    if (status)
    {
        change_turn();
    }
    return status;
}

// Terminal based game for demo
void Game::start_game()
{
    // Initialize the game board
    game_board->initiate_board();
    game_board->print_board();

    while (1)
    {
        // Get user input for the move
        int position, destination;
        std::cout << "Current turn: " << (current_turn == Color::WHITE ? "White" : "Black") << std::endl;
        std::cout << "Enter the position and destination: ";
        std::cin >> position >> destination;

        // Move the piece
        handle_move(position, destination);
        game_board->print_board();

        if (is_checkmate(current_turn))
        {
            cout << "Checkmate!" << endl;
            cout << (current_turn == Color::WHITE ? "Black" : "White") << " wins!" << endl;
            break;
        }

        if (is_stalemate())
        {
            cout << "Stalemate!" << endl;
            break;
        }

        if (is_check())
        {
            cout << "Check!" << endl;
        }
    }
}

bool Game::is_check()
{
    return game_board->is_check(current_turn);
}

bool Game::is_checkmate(Color current_color)
{

    if (!game_board->is_check(current_color))
    {
        return false; // king is not under threat
    }

    // serialize the current state of the board
    std::string curr_state = game_board->serialize_board();

    // create a virtual board to not change the actual board
    GameBoard *virtual_board = new GameBoard();
    virtual_board->deserialize_board(curr_state);

    // iterate through all the pieces on the board
    for (int i = 0; i < 64; i++)
    {
        Piece *piece = virtual_board->get_piece(i);
        if (piece != nullptr && piece->get_color() == current_color)
        {
            if (piece->get_valid_moves().size() == 0 && piece->get_eatable_moves().size() == 0)
            {
                continue;
            }
            std::pair<std::vector<int>, std::vector<int>> valid_moves = virtual_board->get_valid_moves(i);
            std::vector<int> final_valid_moves = valid_moves.first;
            std::vector<int> final_eatable_moves = valid_moves.second;
            if (final_valid_moves.empty() && final_eatable_moves.empty())
            {
                continue;
            }
            else
            {
                delete virtual_board;
                return false;
            }
        }
    }

    delete virtual_board;
    return true; // check mate
}

bool Game::is_stalemate()
{
    if (game_board->is_check(current_turn))
    {
        return false;
    }

        // serialize the current state of the board
    std::string curr_state = game_board->serialize_board();

    // create a virtual board to not change the actual board
    GameBoard *virtual_board = new GameBoard();
    virtual_board->deserialize_board(curr_state);

    // iterate through all the pieces on the board
    for (int i = 0; i < 64; i++)
    {
        Piece *piece = virtual_board->get_piece(i);
        if (piece != nullptr && piece->get_color() == current_turn)
        {
            if (piece->get_valid_moves().size() == 0 && piece->get_eatable_moves().size() == 0)
            {
                continue;
            }
            std::pair<std::vector<int>, std::vector<int>> valid_moves = virtual_board->get_valid_moves(i);
            std::vector<int> final_valid_moves = valid_moves.first;
            std::vector<int> final_eatable_moves = valid_moves.second;
            if (final_valid_moves.empty() && final_eatable_moves.empty())
            {
                continue;
            }
            else
            {
                delete virtual_board;
                return false;
            }
        }
    }


    delete virtual_board;
    return true; 
}

void Game::update_game_status()
{
}

GameBoard *Game::get_game_board()
{
    return game_board;
}

Color Game::get_current_turn()
{
    return current_turn;
}

void Game::set_current_turn(Color color)
{
    current_turn = color;
}
