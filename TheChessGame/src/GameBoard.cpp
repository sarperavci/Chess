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

GameBoard::~GameBoard() {

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

bool GameBoard::is_pawn_move_blocked(Piece *piece, int destination, bool is_eat)
{
    int position = piece->get_position();
    Color color = piece->get_color();
    int direction = (color == Color::WHITE) ? 1 : -1;

    // Check if the move is a forward move
    if (!is_eat)
    {
        if (destination == position + 8 * direction)
        {
            return board[destination] != nullptr;
        }
        if ((position / 8 == 1 && color == Color::WHITE) || (position / 8 == 6 && color == Color::BLACK))
        {
            if (destination == position + 16 * direction)
            {
                return board[position + 8 * direction] != nullptr || board[destination] != nullptr;
            }
        }
    }
    else
    {
        // Check if the move is a diagonal capture
        if ((destination == position + 7 * direction && position % 8 != 0) ||
            (destination == position + 9 * direction && position % 8 != 7))
        {
            return board[destination] == nullptr || board[destination]->get_color() == color;
        }
    }

    // If none of the above conditions are met, the move is invalid for a pawn
    return true;
}

bool GameBoard::is_bishop_move_blocked(Piece *piece, int destination, bool is_eat)
{
    int position = piece->get_position();
    int row_diff = abs(destination / 8 - position / 8);
    int col_diff = abs(destination % 8 - position % 8);

    // Bishops move diagonally, so the row difference and column difference must be equal
    if (row_diff != col_diff)
    {
        return true; // Invalid bishop move
    }

    int row_direction = (destination / 8 > position / 8) ? 1 : -1;
    int col_direction = (destination % 8 > position % 8) ? 1 : -1;

    int current_row = position / 8 + row_direction;
    int current_col = position % 8 + col_direction;

    while (current_row != destination / 8 || current_col != destination % 8)
    {
        int current_position = current_row * 8 + current_col;
        if (board[current_position] != nullptr)
        {
            return true; // There is a piece blocking the bishop's path
        }
        current_row += row_direction;
        current_col += col_direction;
    }

    // Check if the destination is occupied by a piece of the same color
    if (board[destination] != nullptr)
    {
        if (board[destination]->get_color() == piece->get_color())
        {
            return true; // The move is blocked by a piece of the same color
        }
        else if (!is_eat)
        {
            return true; // The move is blocked by an enemy piece and it's not a capture move
        }
    }

    return false; // No pieces are blocking the bishop's path
}

bool GameBoard::is_knight_move_blocked(Piece *piece, int destination, bool is_eat)
{
    // Check if the destination is occupied
    if (board[destination] != nullptr)
    {
        // If the destination is occupied by a piece of the same color, the move is blocked
        if (board[destination]->get_color() == piece->get_color())
        {
            return true;
        }
        // If the destination is occupied by an enemy piece and it's not a capture move, the move is blocked
        else if (!is_eat)
        {
            return true;
        }
    }

    return false; // The move is not blocked
}

bool GameBoard::is_king_move_blocked(Piece *piece, int destination, bool is_eat)
{
    // Check if the destination is occupied
    if (board[destination] != nullptr)
    {
        // If the destination is occupied by a piece of the same color, the move is blocked
        if (board[destination]->get_color() == piece->get_color())
        {
            return true;
        }
        // If the destination is occupied by an enemy piece and it's not a capture move, the move is blocked
        else if (!is_eat)
        {
            return true;
        }
    }

    // If the destination is not occupied or it's a valid capture move, the move is not blocked
    return false;
}

bool GameBoard::is_queen_move_blocked(Piece *piece, int destination, bool is_eat)
{
    int position = piece->get_position();
    int row_diff = abs(destination / 8 - position / 8);
    int col_diff = abs(destination % 8 - position % 8);

    // Determine the direction of the move
    int row_direction = (destination / 8 > position / 8) ? 1 : (destination / 8 < position / 8) ? -1
                                                                                                : 0;
    int col_direction = (destination % 8 > position % 8) ? 1 : (destination % 8 < position % 8) ? -1
                                                                                                : 0;

    // Check if the move is horizontal, vertical, or diagonal
    if (row_diff == col_diff || row_diff == 0 || col_diff == 0)
    {
        int current_row = position / 8 + row_direction;
        int current_col = position % 8 + col_direction;

        while (current_row != destination / 8 || current_col != destination % 8)
        {
            int current_position = current_row * 8 + current_col;
            if (board[current_position] != nullptr)
            {
                return true; // There is a piece blocking the queen's path
            }
            current_row += row_direction;
            current_col += col_direction;
        }
    }
    else
    {
        return true; // Invalid queen move
    }

    // Check if the destination is occupied by a piece of the same color
    if (board[destination] != nullptr)
    {
        if (board[destination]->get_color() == piece->get_color())
        {
            return true; // The move is blocked by a piece of the same color
        }
        else if (!is_eat)
        {
            return true; // The move is blocked by an enemy piece and it's not a capture move
        }
    }

    return false; // No pieces are blocking the queen's path
}

bool GameBoard::is_rook_move_blocked(Piece *piece, int destination, bool is_eat)
{
    int position = piece->get_position();
    int row_diff = abs(destination / 8 - position / 8);
    int col_diff = abs(destination % 8 - position % 8);

    // Rooks move horizontally or vertically, so either row_diff or col_diff must be zero
    if (row_diff != 0 && col_diff != 0)
    {
        return true; // Invalid rook move
    }

    int row_direction = (destination / 8 > position / 8) ? 1 : (destination / 8 < position / 8) ? -1
                                                                                                : 0;
    int col_direction = (destination % 8 > position % 8) ? 1 : (destination % 8 < position % 8) ? -1
                                                                                                : 0;

    int current_row = position / 8 + row_direction;
    int current_col = position % 8 + col_direction;

    while (current_row != destination / 8 || current_col != destination % 8)
    {
        int current_position = current_row * 8 + current_col;
        if (board[current_position] != nullptr)
        {
            return true; // There is a piece blocking the rook's path
        }
        current_row += row_direction;
        current_col += col_direction;
    }

    // Check if the destination is occupied by a piece of the same color
    if (board[destination] != nullptr)
    {
        if (board[destination]->get_color() == piece->get_color())
        {
            return true; // The move is blocked by a piece of the same color
        }
        else if (!is_eat)
        {
            return true; // The move is blocked by an enemy piece and it's not a capture move
        }
    }

    return false; // No pieces are blocking the rook's path
}

// Wrapper function for the move_piece function
// is_eat=True adds an additional check for the destination square, to see if it's occupied by an enemy piece
// is_eat=False is used for moves that don't involve capturing an enemy piece (the destination square has to be empty)
bool GameBoard::is_move_blocked(Piece *piece, int destination, bool is_eat = false)
{
    switch (piece->get_piece_type())
    {
    case PieceType::PAWN:
        return is_pawn_move_blocked(piece, destination, is_eat);
    case PieceType::BISHOP:
        return is_bishop_move_blocked(piece, destination, is_eat);
    case PieceType::KNIGHT:
        return is_knight_move_blocked(piece, destination, is_eat);
    case PieceType::KING:
        return is_king_move_blocked(piece, destination, is_eat);
    case PieceType::QUEEN:
        return is_queen_move_blocked(piece, destination, is_eat);
    case PieceType::ROOK:
        return is_rook_move_blocked(piece, destination, is_eat);
    default:
        return true;
    }
}

void GameBoard::move_piece(Piece *piece, int destination)
{
    // Get the current position of the piece
    int position = piece->get_position();

    // Get the valid moves for the piece
    std::vector<int> valid_moves = piece->get_valid_moves();
    std::vector<int> eatable_moves = piece->get_eatable_moves();

    // Check if the destination is a valid move or capture
    bool is_valid_move = std::find(valid_moves.begin(), valid_moves.end(), destination) != valid_moves.end();
    bool is_valid_capture = std::find(eatable_moves.begin(), eatable_moves.end(), destination) != eatable_moves.end();

    if (is_valid_move || is_valid_capture)
    {
        // Check if the path is blocked for pieces that move along a path
        bool is_blocked = is_move_blocked(piece, destination, is_valid_capture);

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
            }
        }
    }
}

void GameBoard::move_piece(Piece *piece, int row, int col)
{
    move_piece(piece, indexes2DToInt(row, col));
}

void GameBoard::move_piece(int position, int destination)
{
    if (board[position] != nullptr)
    {

        move_piece(get_piece(position), destination);
    }
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
    for (int i = 0; i < 64; i++) {
        Piece *piece = board[i];
        if (piece != nullptr && piece->get_piece_type() == PieceType::KING && piece->get_color() == color) {
            king_position = i;
            break;
        }
    }

    // there is an error if the king cannot be found according to the given color
    if (king_position == -1) {
        return false;
    }

    Color opponent_color = (color == Color::WHITE) ? Color::BLACK : Color::WHITE;

    for (int i = 0; i < 64; i++) {
        Piece *piece = board[i];
        if (piece != nullptr && piece->get_color() == opponent_color) {
            std::vector<int> valid_moves = piece->get_eatable_moves();
            for (int move : valid_moves) {
                if (move == king_position) {
                    if (!is_move_blocked(piece, move, true)) {
                        return true;  // The king is in check
                    }
                }
            }
        }
    }
    return false;  // The king is not in check
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