#include "GameBoard.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <string>
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

// Get all possible moves for a piece, including moves that capture an opponent's piece, castling, en passant,
// and the most important, all future moves will be checked
// so you can safely use this function to get all valid moves
std::pair<std::vector<int>, std::vector<int>> GameBoard::get_valid_moves(int position)
{
    std::vector<int> valid_moves;
    std::vector<int> eatable_moves;
    Piece *piece = get_piece(position);

    if (!piece)
        return std::make_pair(valid_moves, eatable_moves);
    else
    {
        for (int pos : piece->get_valid_moves())
        {
            if (!piece->is_move_blocked(pos, false, board))
            {
                valid_moves.push_back(pos);
            }
        }

        for (int pos : piece->get_eatable_moves())
        {
            if (!piece->is_move_blocked(pos, true, board))
            {
                eatable_moves.push_back(pos);
            }
        }
    }

    // check for castling
    if (piece->get_piece_type() == PieceType::KING)
    {
        King *king = dynamic_cast<King *>(piece);
        if (king != nullptr)
        {
            if (can_castle(position, piece, position + 2))
            {
                valid_moves.push_back(position + 2);
            }
            if (can_castle(position, piece, position - 2))
            {
                valid_moves.push_back(position - 2);
            }
        }
    }

    // Create a virtual board to check if a future move is valid
    GameBoard *virtual_board = new GameBoard();
    // Yes, I know this is not the best way to do it, but it works
    // No slow down is noticeable
    std::vector<int> final_valid_moves = {};
    for (size_t n = 0; n < valid_moves.size(); n++)
    {
        virtual_board->clear_board();
        std::string current_state = serialize_board();
        virtual_board->deserialize_board(current_state);
        int status = virtual_board->handle_move(position, valid_moves[n]);

        if (status)
        {
            final_valid_moves.push_back(valid_moves[n]);
        }
    }

    std::vector<int> final_eatable_moves = {};
    for (size_t n = 0; n < eatable_moves.size(); n++)
    {
        virtual_board->clear_board();
        std::string current_state = serialize_board();
        virtual_board->deserialize_board(current_state);
        int status = virtual_board->handle_move(position, eatable_moves[n]);

        std::string new_state = virtual_board->serialize_board();

        if (status)
        {
            final_eatable_moves.push_back(eatable_moves[n]);
        }
    }

    delete virtual_board;

    if (piece->get_piece_type() == PieceType::PAWN)
    {
        Pawn *pawn = dynamic_cast<Pawn *>(piece);
        if (pawn != nullptr)
        {
            for (int dest : piece->get_eatable_moves())
            {
                if (is_en_passant(piece, dest))
                {
                    final_eatable_moves.push_back(dest);
                }
            }
        }
    }

    return std::make_pair(final_valid_moves, final_eatable_moves);
}
int GameBoard::handle_move(int src, int dest)
{
    if (src == dest)
    {
        return 0;
    }

    if (get_piece(src) == nullptr)
    {
        return 0;
    }

    // You cannot eat a king
    if (get_piece(dest) != nullptr && get_piece(dest)->get_piece_type() == PieceType::KING)
    {
        return 0;
    }

    Piece *piece = get_piece(src);

    // check if there's ongoing check
    int status_code = 0;

    // check if the move is rook castling
    if (piece->get_piece_type() == PieceType::KING)
    {
        King *king = dynamic_cast<King *>(piece);
        if (king != nullptr)
        {
            if (can_castle(src, piece, dest))
            {
                perform_castling(src, piece, dest);
                save_move();
                status_code = 1;
            }
        }
    }

    // check if the move is en passant
    if (piece->get_piece_type() == PieceType::PAWN)
    {
        Pawn *pawn = dynamic_cast<Pawn *>(piece);
        if (pawn != nullptr)
        {
            if (is_en_passant(piece, dest))
            {
                perform_en_passant(src, piece, dest);
                save_move();
                status_code = 1;
            }
        }
    }

    // If above special moves are not performed, move the piece normally
    if (!status_code)
    {
        status_code = move_piece(src, dest);
        save_move();
    }

    // check the danger of the king still exists, then undo the move
    if (is_check(piece->get_color()) && status_code)
    {
        rewind_move(1);
        status_code = 0;
    }

    return status_code;
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

Piece **GameBoard::get_board()
{
    return board;
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

// Check if the king of a given color is in check
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

std::string GameBoard::serialize_board()
{
    std::string board_str = "";

    for (int i = 0; i < 64; i++)
    {
        if (board[i] == nullptr)
        {
            board_str += 'X';
        }
        else
        {
            Piece *piece = board[i];
            if (piece->get_color() == Color::WHITE)
            {
                switch (piece->get_piece_type())
                {
                case PieceType::PAWN:
                    board_str += 'P';
                    break;
                case PieceType::ROOK:
                    board_str += 'R';
                    break;
                case PieceType::KNIGHT:
                    board_str += 'N';
                    break;
                case PieceType::BISHOP:
                    board_str += 'B';
                    break;
                case PieceType::QUEEN:
                    board_str += 'Q';
                    break;
                case PieceType::KING:
                    board_str += 'K';
                    break;
                default:
                    break;
                }
            }
            else if (piece->get_color() == Color::BLACK)
            {
                switch (piece->get_piece_type())
                {
                case PieceType::PAWN:
                    board_str += 'p';
                    break;
                case PieceType::ROOK:
                    board_str += 'r';
                    break;
                case PieceType::KNIGHT:
                    board_str += 'n';
                    break;
                case PieceType::BISHOP:
                    board_str += 'b';
                    break;
                case PieceType::QUEEN:
                    board_str += 'q';
                    break;
                case PieceType::KING:
                    board_str += 'k';
                    break;
                default:
                    break;
                }
            }
        }
    }

    return board_str;
}

// Always call clear_board() before calling this function to avoid memory leaks
void GameBoard::deserialize_board(std::string board_str)
{
    // convert the string to a board state
    for (int i = 0; i < 64; i++)
    {
        switch (board_str[i])
        {
        case 'P':
            set_piece(i, new Pawn(i, Color::WHITE));
            break;
        case 'R':
            set_piece(i, new Rook(i, Color::WHITE));
            break;
        case 'N':
            set_piece(i, new Knight(i, Color::WHITE));
            break;
        case 'B':
            set_piece(i, new Bishop(i, Color::WHITE));
            break;
        case 'Q':
            set_piece(i, new Queen(i, Color::WHITE));
            break;
        case 'K':
            set_piece(i, new King(i, Color::WHITE));
            break;
        case 'p':
            set_piece(i, new Pawn(i, Color::BLACK));
            break;
        case 'r':
            set_piece(i, new Rook(i, Color::BLACK));
            break;
        case 'n':
            set_piece(i, new Knight(i, Color::BLACK));
            break;
        case 'b':
            set_piece(i, new Bishop(i, Color::BLACK));
            break;
        case 'q':
            set_piece(i, new Queen(i, Color::BLACK));
            break;
        case 'k':
            set_piece(i, new King(i, Color::BLACK));
            break;
        default:
            set_piece(i, nullptr);
            break;
        }
    }
}
void GameBoard::save_move()
{
    std::string current_board_state = serialize_board();
    if (move_history.empty() || move_history.back() != current_board_state)
    {
        move_history.push_back(current_board_state);
    }
}

bool GameBoard::can_rewind_move(size_t n)
{
    return move_history.size() >= n;
}

void GameBoard::rewind_move(int n)
{
    if (!can_rewind_move(n))
    {
        std::cerr << "Cannot rewind " << n << " moves" << std::endl;
        return;
    }

    // Remove the last n moves from the move history
    move_history.erase(move_history.end() - n, move_history.end());

    // Clear the board
    clear_board();

    // Deserialize the board state from the last remaining move in the history
    if (!move_history.empty())
    {
        deserialize_board(move_history.back());
    }
    else
    {
        initiate_board();
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