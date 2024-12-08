#include "Game.h"
#include "GameBoard.h"

Game::Game()
{
    game_board = new GameBoard();
    current_turn = Color::WHITE;   // game starts with white
}

Game::~Game()
{
    delete game_board;
}

void Game::change_turn()
{
    if (current_turn == Color::WHITE) {
        current_turn = Color::BLACK;
    } else {
        current_turn = Color::WHITE;
    }
}

void Game::handle_move(int row, int col, int dest)
{

}

void Game::handle_move(int src, int dest)
{

}

void Game::start_game()
{

}

bool Game::is_check()
{
    return game_board->is_check(current_turn);
}

bool Game::is_checkmate()
{
    return false;
}

bool Game::is_stalemate()
{
    return false;
}

bool Game::is_draw()
{
    return false;
}

void Game::check_pawn_promotion(int position, Piece* piece)
{

}

void Game::check_en_passant(int position, Piece* piece, int dest)
{

}

void Game::check_castling(int position, Piece* piece, int dest)
{

}

void Game::update_game_status()
{

}

GameBoard* Game::get_game_board()
{
    return game_board;
}

Color Game::get_current_turn()
{
    return current_turn;
}
