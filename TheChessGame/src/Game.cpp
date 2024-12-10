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
    if (game_board->get_piece(src) == nullptr)
    {
        return 0;
    }

    Piece *piece = game_board->get_piece(src);
    // check if the piece is the same color as the current turn
    if (piece->get_color() != current_turn)
    {
        return 0;
    }

    // check if the move is rook castling
    if (piece->get_piece_type() == PieceType::KING)
    {
        King *king = dynamic_cast<King *>(piece);
        if (king != nullptr)
        {
            if (game_board->can_castle(src, piece, dest))
            {
                game_board->perform_castling(src, piece, dest);
                change_turn();
                return 1;
            }
        }
    }

    // check if the move is en passant
    if (piece->get_piece_type() == PieceType::PAWN)
    {
        Pawn *pawn = dynamic_cast<Pawn *>(piece);
        if (pawn != nullptr)
        {
            if (game_board->is_en_passant(src, piece, dest))
            {
                game_board->perform_en_passant(src, piece, dest);
                change_turn();
                return 1;
            }
        }
    }

    // handle the normal move & eat, but zero status means the move is invalid and the turn doesn't change
    int status;
    status = game_board->move_piece(src, dest);
    if (status == 0)
        return 0;
    
    // if the pawn reaches the end of the board, promote it to a queen
    if (game_board->is_pawn_promotion(dest, piece))
    {
        game_board->promote_pawn(dest, piece, PieceType::QUEEN);
    }

    change_turn();

    return 1;
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

        if (is_checkmate())
        {
            cout << "Checkmate!" << endl;
            break;
        }

        if (is_stalemate())
        {
            cout << "Stalemate!" << endl;
            break;
        }

        if (is_draw())
        {
            cout << "Draw!" << endl;
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

bool Game::is_checkmate()
{
    Color currentColor = current_turn;
    if (!game_board->is_check(currentColor))
    {
        return false; // king is not under threat
    }

    // player's all pieces are checked
    for (int i = 0; i < 64; i++)
    {
        Piece *piece = game_board->get_piece(i);
        if (piece != nullptr && piece->get_color() == currentColor)
        {
            vector<int> valid_moves = piece->get_eatable_moves();
            for (int move : valid_moves)
            {
                // backing up your current state and making moves
                Piece *captured_piece = game_board->get_piece(move);
                int original_position = piece->get_position();

                game_board->set_piece(move, piece);
                game_board->set_piece(original_position, nullptr);
                piece->set_position(move);

                // is the king in danger in the possible move?
                bool still_in_check = game_board->is_check(currentColor);

                // restore the board
                game_board->set_piece(original_position, piece);
                game_board->set_piece(move, captured_piece);
                piece->set_position(original_position);

                if (!still_in_check)
                {
                    return false;
                }
            }
        }
    }

    return true; // check mate
}

bool Game::is_stalemate()
{
    if (game_board->is_check(current_turn))
    {
        return false;
    }

    for (int i = 0; i < 64; i++)
    {
        Piece *piece = game_board->get_piece(i);
        if (piece != nullptr && piece->get_color() == current_turn)
        {
            std::vector<int> valid_moves = piece->get_eatable_moves();

            // if the piece has a move it can make, there is no pat situation.
            for (int move : valid_moves)
            {
                // backing up your current state and making moves
                Piece *captured_piece = game_board->get_piece(move);
                int original_position = piece->get_position();

                game_board->set_piece(move, piece);
                game_board->set_piece(original_position, nullptr);
                piece->set_position(move);

                if (!game_board->is_check(current_turn))
                {
                    game_board->set_piece(original_position, piece);
                    game_board->set_piece(move, captured_piece);
                    piece->set_position(original_position);
                    return false;
                }

                // restore the board
                game_board->set_piece(original_position, piece);
                game_board->set_piece(move, captured_piece);
                piece->set_position(original_position);
            }
        }
    }

    return true; // stalemate
}

bool Game::is_draw()
{
    return false;
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
