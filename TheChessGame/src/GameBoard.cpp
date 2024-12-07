#include "GameBoard.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

#include "utils.h"
#include <algorithm>
#include <iostream>

GameBoard::GameBoard()
{
    for (int i = 0; i < 64; i++)
    {
        board[i] = nullptr;
    }
}

Piece *GameBoard::get_piece(int position)
{
    return board[position];
}

Piece *GameBoard::get_piece(int row, int col)
{
    return get_piece(indexes2DToInt(row, col));
}

void GameBoard::set_piece(int position, Piece *piece)
{
    board[position] = piece;
}

void GameBoard::set_piece(int row, int col, Piece *piece)
{
    set_piece(indexes2DToInt(row, col), piece);
}

void GameBoard::move_piece(Piece *piece, int destination)
{
    // Get the current position of the piece
    int position = piece->get_position();

    // Get the valid moves for the piece
    std::vector<int> valid_moves = piece->get_valid_moves();

    // Check if the destination is a valid move
    if (std::find(valid_moves.begin(), valid_moves.end(), destination) != valid_moves.end())
    {
        if (board[destination] == nullptr)
        {
            board[position] = nullptr;
            board[destination] = piece;
            piece->move(destination);
        }
    }
}

void GameBoard::move_piece(Piece *piece, int row, int col)
{
    move_piece(piece, indexes2DToInt(row, col));
}

void GameBoard::remove_piece(int position)
{
    if (board[position] != nullptr)
    {
        //delete board[position];
        board[position] = nullptr;
    }
}

void GameBoard::remove_piece(int row, int col)
{
    remove_piece(indexes2DToInt(row, col));
}

void GameBoard::initiate_board()
{

    // White pieces
    set_piece(0, new Rook(0, Color::WHITE));
    set_piece(1, new Knight(1, Color::WHITE));
    set_piece(2, new Bishop(2, Color::WHITE));
    set_piece(3, new Queen(3, Color::WHITE));
    set_piece(4, new King(4, Color::WHITE));
    set_piece(5, new Bishop(5, Color::WHITE));
    set_piece(6, new Knight(6, Color::WHITE));
    set_piece(7, new Rook(7, Color::WHITE));
    for (int i = 8; i < 16; i++)
    {
        set_piece(i, new Pawn(i, Color::WHITE));
    }

    // Black pieces
    set_piece(56, new Rook(56, Color::BLACK));
    set_piece(57, new Knight(57, Color::BLACK));
    set_piece(58, new Bishop(58, Color::BLACK));
    set_piece(59, new Queen(59, Color::BLACK));
    set_piece(60, new King(60, Color::BLACK));
    set_piece(61, new Bishop(61, Color::BLACK));
    set_piece(62, new Knight(62, Color::BLACK));
    set_piece(63, new Rook(63, Color::BLACK));
    for (int i = 48; i < 56; i++)
    {
        set_piece(i, new Pawn(i, Color::BLACK));
    }

    // Empty squares
    for (int i = 16; i < 48; i++)
    {
        set_piece(i, nullptr);
    }
}

void GameBoard::clear_board()
{
    for (int i = 0; i < 64; i++)
    {
        if (board[i] != nullptr)
        {
           // delete board[i];
            board[i] = nullptr;
        }
    }
}

void GameBoard::print_board()
{
    const char *WHITE_PAWN = "\u2659";
    const char *WHITE_KING = "\u2654";
    const char *WHITE_QUEEN = "\u2655";
    const char *WHITE_ROOK = "\u2656";
    const char *WHITE_BISHOP = "\u2657";
    const char *WHITE_KNIGHT = "\u2658";
    const char *BLACK_KING = "\u265A";
    const char *BLACK_QUEEN = "\u265B";
    const char *BLACK_ROOK = "\u265C";
    const char *BLACK_BISHOP = "\u265D";
    const char *BLACK_KNIGHT = "\u265E";
    const char *BLACK_PAWN = "\u265F";
    const char *EMPTY_SQUARE = "\u25A1";

    for (int row = 7; row >= 0; --row)
    {
        for (int col = 0; col < 8; ++col)
        {
            Piece *piece = get_piece(row, col);
            if (piece == nullptr)
            {
                std::cout << EMPTY_SQUARE << " ";
            }
            else
            {
                switch (piece->get_piece_type())
                {
                case PieceType::PAWN:
                    std::cout << (piece->get_color() == Color::WHITE ? WHITE_PAWN : BLACK_PAWN) << " ";
                    break;
                case PieceType::KING:
                    std::cout << (piece->get_color() == Color::WHITE ? WHITE_KING : BLACK_KING) << " ";
                    break;
                case PieceType::QUEEN:
                    std::cout << (piece->get_color() == Color::WHITE ? WHITE_QUEEN : BLACK_QUEEN) << " ";
                    break;
                case PieceType::ROOK:
                    std::cout << (piece->get_color() == Color::WHITE ? WHITE_ROOK : BLACK_ROOK) << " ";
                    break;
                case PieceType::BISHOP:
                    std::cout << (piece->get_color() == Color::WHITE ? WHITE_BISHOP : BLACK_BISHOP) << " ";
                    break;
                case PieceType::KNIGHT:
                    std::cout << (piece->get_color() == Color::WHITE ? WHITE_KNIGHT : BLACK_KNIGHT) << " ";
                    break;
                default:
                    std::cout << "? ";
                    break;
                }
            }
        }
        std::cout << std::endl;
    }
}