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

GameBoard::~GameBoard()
{
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

int GameBoard::move_piece(Piece *piece, int destination)
{
    // Get the current position of the piece
    int position = piece->get_position();

    // Get the valid moves for the piece
    std::vector<int> valid_moves = piece->get_valid_moves();
    std::vector<int> eatable_moves = piece->get_eatable_moves();

    // Check if the destination is a valid move or capture
    bool is_valid_move = std::find(valid_moves.begin(), valid_moves.end(), destination) != valid_moves.end();
    bool is_valid_capture = std::find(eatable_moves.begin(), eatable_moves.end(), destination) != eatable_moves.end();

    // Ensure that the destination is an empty square for a move
    is_valid_move = is_valid_move && board[destination] == nullptr;

    // Ensure that the destination is a valid capture
    is_valid_capture = is_valid_capture && board[destination] != nullptr;

    if (is_valid_move || is_valid_capture)
    {
        // Check if the path is blocked for pieces that move along a path
        bool is_blocked = piece->is_move_blocked(destination, is_valid_capture, board);

        if (!is_blocked)
        {
            // Handle move or capture
            if (board[destination] == nullptr || is_valid_capture)
            {
                if (is_valid_capture && board[destination] != nullptr)
                {
                    // Capture the piece
                    delete board[destination];
                }
                // Move the piece
                board[position] = nullptr;
                board[destination] = piece;
                piece->move(destination);
                return 1; // Move has been made
            }
        }
    }
    return 0; // No move has been made
}

int GameBoard::move_piece(Piece *piece, int row, int col)
{
    return move_piece(piece, indexes2DToInt(row, col));
}

int GameBoard::move_piece(int position, int destination)
{
    if (board[position] != nullptr)
    {
        return move_piece(get_piece(position), destination);
    }
    return 0;
}

void GameBoard::remove_piece(int position)
{
    if (board[position] != nullptr)
    {
        delete board[position];
        board[position] = nullptr;
    }
}

void GameBoard::remove_piece(int row, int col)
{
    remove_piece(indexes2DToInt(row, col));
}

void GameBoard::initiate_board()
{
    // I know it's very confusing but they're whites...
    // White pieces: ♙ ♘ ♗ ♕ ♔ ♗ ♘ ♖
    // Black pieces: ♟ ♞ ♝ ♛ ♚ ♝ ♞ ♜
    // really, compare https://www.compart.com/en/unicode/U+265C and https://www.compart.com/en/unicode/U+2656
    // I thought that was a bug, so I spent almost 1 hour to find out that it's not a bug.

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
            delete board[i];
            board[i] = nullptr;
        }
    }
}

bool GameBoard::is_check(Color color)
{
    int king_position = -1;

    // Function to find the position of the king of a given color
    for (int i = 0; i < 64; i++)
    {
        Piece *piece = board[i];
        if (piece != nullptr && piece->get_piece_type() == PieceType::KING && piece->get_color() == color)
        {
            king_position = i;
            break;
        }
    }

    // there is an error if the king cannot be found according to the given color
    if (king_position == -1)
    {
        return false;
    }

    Color opponent_color = (color == Color::WHITE) ? Color::BLACK : Color::WHITE;

    for (int i = 0; i < 64; i++)
    {
        Piece *piece = board[i];
        if (piece != nullptr && piece->get_color() == opponent_color)
        {
            std::vector<int> valid_moves = piece->get_eatable_moves();
            for (int move : valid_moves)
            {
                if (move == king_position)
                {
                    if (!piece->is_move_blocked(move, true, board))
                    {
                        return true; // The king is in check
                    }
                }
            }
        }
    }
    return false; // The king is not in check
}

bool GameBoard::is_pawn_promotion(int position, Piece *piece)
{
    if (piece->get_piece_type() == PieceType::PAWN)
    {
        if ((piece->get_color() == Color::WHITE && position >= 56) || (piece->get_color() == Color::BLACK && position < 8))
        {
            return true;
        }
    }
    return false;
}

void GameBoard::promote_pawn(int position, Piece *piece, PieceType new_type)
{
    Color color = piece->get_color();
    remove_piece(position);
    switch (new_type)
    {
    case PieceType::QUEEN:
        set_piece(position, new Queen(position, color));
        break;
    case PieceType::ROOK:
        set_piece(position, new Rook(position, color));
        break;
    case PieceType::BISHOP:
        set_piece(position, new Bishop(position, color));
        break;
    case PieceType::KNIGHT:
        set_piece(position, new Knight(position, color));
        break;
    default:
        break;
    }
}

bool GameBoard::is_en_passant(Piece *piece, int dest)
{
    if (piece->get_piece_type() != PieceType::PAWN)
    {
        return false;
    }
    
    Color target_color = (piece->get_color() == Color::WHITE) ? Color::BLACK : Color::WHITE;
    int target_way = (piece->get_color() == Color::WHITE) ? -8 : 8;

    std::vector<int> moves = piece->get_eatable_moves();
    for (int move : moves)
    {
        if (dest == move && board[dest] == nullptr && board[dest + target_way] != nullptr && board[dest + target_way]->get_color() == target_color && board[dest + target_way]->get_piece_type() == PieceType::PAWN && dynamic_cast<Pawn *>(board[dest + target_way])->get_has_moved_two_squares())
        {
            return true;
        }
    }

    return false;
}

void GameBoard::perform_en_passant(int position, Piece *piece, int dest)
{
    if (is_en_passant(piece, dest))
    {
        int capture_pos = dest + (piece->get_color() == Color::WHITE ? -8 : 8);

        // Remove the captured pawn
        remove_piece(capture_pos);

        // Move the pawn to the destination
        board[position] = nullptr;
        board[dest] = piece;
        piece->move(dest);
    }
}

bool GameBoard::can_castle(int position, Piece *piece, int dest)
{
    King *king = dynamic_cast<King *>(piece);
    if (king != nullptr)
    {
        int col = position % 8;

        if (col == 4)
        {
            Piece *rook = nullptr;
            bool isShortCastling = false;
            bool isLongCastling = false;

            if (dest == position + 2)
            {
                isShortCastling = true;
                rook = get_piece(position + 3);
            }
            else if (dest == position - 2)
            {
                isLongCastling = true;
                rook = get_piece(position - 4);
            }

            if (isShortCastling || isLongCastling)
            {
                Rook *rookPiece = dynamic_cast<Rook *>(rook);
                if (rookPiece != nullptr && !rookPiece->get_has_moved())
                {
                    int step = (isShortCastling) ? 1 : -1;
                    for (int i = position + step; i != dest; i += step)
                    {
                        if (get_piece(i) != nullptr)
                        {
                            return false;
                        }
                    }
                    if (is_check((king->get_color() == Color::WHITE) ? Color::BLACK : Color::WHITE) ||
                        get_piece(position + (isShortCastling ? 1 : -1)) != nullptr ||
                        get_piece(dest) != nullptr)
                    {
                        return false;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

void GameBoard::perform_castling(int position, Piece *piece, int dest)
{
    if (can_castle(position, piece, dest))
    {
        King *king = dynamic_cast<King *>(piece);
        if (king != nullptr)
        {
            bool isShortCastling = (dest == position + 2);
            bool isLongCastling = (dest == position - 2);

            if (isShortCastling || isLongCastling)
            {
                int rook_position = position + (isShortCastling ? 3 : -4);
                Rook *rookPiece = dynamic_cast<Rook *>(get_piece(rook_position));
                if (rookPiece != nullptr && rookPiece->get_color() == piece->get_color())
                {
                    int rook_dest = position + (isShortCastling ? 1 : -1);

                    // Move the king
                    board[position] = nullptr;
                    board[dest] = piece;
                    piece->move(dest);

                    // Move the rook
                    board[rook_position] = nullptr;
                    board[rook_dest] = rookPiece;
                    rookPiece->move(rook_dest);
                }
            }
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