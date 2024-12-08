#include "Game.h"
#include "GameBoard.h"
#include "Pawn.h"
#include "King.h"
#include "Rook.h"
#include "Piece.h"
#include <vector>

using namespace std;

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

bool Game::is_checkmate() {
    Color currentColor = current_turn;
    if (!game_board->is_check(currentColor)) {
        return false;  // king is not under threat
    }

    // player's all pieces are checked
    for (int i = 0; i < 64; i++) {
        Piece* piece = game_board->get_piece(i);
        if (piece != nullptr && piece->get_color() == currentColor) {
            vector<int> valid_moves = piece->get_eatable_moves();
            for (int move : valid_moves) {
                // backing up your current state and making moves
                Piece* captured_piece = game_board->get_piece(move);
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

                if (!still_in_check) {
                    return false;
                }
            }
        }
    }

    return true;  // check mate
}

bool Game::is_stalemate() {
    if (game_board->is_check(current_turn)) {
        return false;
    }

    for (int i = 0; i < 64; i++) {
        Piece* piece = game_board->get_piece(i);
        if (piece != nullptr && piece->get_color() == current_turn) {
            std::vector<int> valid_moves = piece->get_eatable_moves();

            // if the piece has a move it can make, there is no pat situation.
            for (int move : valid_moves) {
                // backing up your current state and making moves
                Piece* captured_piece = game_board->get_piece(move);
                int original_position = piece->get_position();

                game_board->set_piece(move, piece);
                game_board->set_piece(original_position, nullptr);
                piece->set_position(move);

                if (!game_board->is_check(current_turn)) {
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

    return true;  // stalemate
}

bool Game::is_draw()
{
    return false;
}

void Game::check_pawn_promotion(int position, Piece* piece)
{
    if (piece->get_piece_type() == PieceType::PAWN) {
        if ((piece->get_color() == Color::WHITE && position >= 56) || (piece->get_color() == Color::BLACK && position < 8)) {
            piece->set_piece_type(PieceType::QUEEN); // temporary promotion to queen
        }
    }
}

void Game::check_en_passant(int position, Piece* piece, int dest)
{
    if (piece->get_piece_type() == PieceType::PAWN) {
        Pawn* pawn = dynamic_cast<Pawn*>(piece);
        if (pawn != nullptr) {
            int row = position / 8;
            int col = position % 8;

            if (pawn->get_color() == Color::WHITE) {
                if (!pawn->get_has_moved()) {
                    // if the white pawn is next to the black pawn on the fourth row
                    if (row == 4 && (col + 1 == dest || col - 1 == dest)) {
                        Piece* target_piece = game_board->get_piece(dest);
                        if (target_piece != nullptr && target_piece->get_piece_type() == PieceType::PAWN && target_piece->get_color() == Color::BLACK) {
                            int target_row = target_piece->get_position() / 8;
                            if (target_row == 5) {  // If the black pawn is on the fifth row, the white pawn eats it
                                game_board->remove_piece(dest);
                                pawn->move(dest);
                            }
                        }
                    }
                }
            }
            else if (pawn->get_color() == Color::BLACK) {
                if (!pawn->get_has_moved()) {
                    // if the black pawn is next to the white pawn on the third row
                    if (row == 3 && (col + 1 == dest || col - 1 == dest)) {
                        Piece* target_piece = game_board->get_piece(dest);
                        if (target_piece != nullptr && target_piece->get_piece_type() == PieceType::PAWN && target_piece->get_color() == Color::WHITE) {
                            int target_row = target_piece->get_position() / 8;
                            if (target_row == 2) { // If the white pawn is on the second row, the black pawn eats it
                                game_board->remove_piece(dest);
                                pawn->move(dest);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Game::check_castling(int position, Piece* piece, int dest)
{
    King* king = dynamic_cast<King*>(piece);
    if (king != nullptr) {
        int col = position % 8;

        if (col == 4) {
            Piece* rook = nullptr;
            bool isShortCastling = false;
            bool isLongCastling = false;

            if (dest == position + 2) {
                isShortCastling = true;
                rook = game_board->get_piece(position + 3);
            } else if (dest == position - 2) {
                isLongCastling = true;
                rook = game_board->get_piece(position - 4);
            }

            if (isShortCastling || isLongCastling) {
                Rook* rookPiece = dynamic_cast<Rook*>(rook);
                if (rookPiece != nullptr && !rookPiece->get_has_moved()) {
                    int step = (isShortCastling) ? 1 : -1;
                    for (int i = position + step; i != dest; i += step) {
                        if (game_board->get_piece(i) != nullptr) {
                            return;
                        }
                    }
                    if (is_check() ||
                        game_board->get_piece(position + (isShortCastling ? 1 : -1)) != nullptr ||
                        game_board->get_piece(dest) != nullptr) {
                        return;
                    }
                    piece->move(dest);
                    rookPiece->move(position + (isShortCastling ? 1 : -1));
                }
            }
        }
    }
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
