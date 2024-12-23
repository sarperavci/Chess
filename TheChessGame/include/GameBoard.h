#include "Piece.h"
#include <vector>
#include <string>
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

/**
 * @brief Class representing the game board for a chess game.
 * 
 * The chessboard is represented as a single array of 64 integers (0 to 63).
 * Each square on the chessboard is mapped to an integer:
 * a1 is 0, a2 is 8, ..., h8 is 63.
 * The mapping is done row by row from bottom to top, left to right.
 */
class GameBoard
{
private:
    Piece *board[64]; ///< Array representing the chessboard

public:
    std::vector<std::string> move_history; ///< History of moves made in the game

    /**
     * @brief Constructor for the GameBoard class.
     */
    GameBoard();

    /**
     * @brief Destructor for the GameBoard class.
     */
    ~GameBoard();

    /**
     * @brief Get the piece at a specific position.
     * @param position The position on the board.
     * @return Pointer to the piece at the specified position.
     */
    Piece *get_piece(int position);

    /**
     * @brief Get the piece at a specific row and column.
     * @param row The row index.
     * @param col The column index.
     * @return Pointer to the piece at the specified row and column.
     */
    Piece *get_piece(int row, int col);

    /**
     * @brief Get the entire board.
     * @return Pointer to the array representing the board.
     */
    Piece **get_board();

    /**
     * @brief Get the valid moves for a piece at a specific position.
     * @param position The position of the piece.
     * @return A pair of vectors containing valid move positions and eatable move positions.
     */
    std::pair<std::vector<int>, std::vector<int>> get_valid_moves(int position);

    /**
     * @brief Set a piece at a specific position.
     * @param position The position on the board.
     * @param piece Pointer to the piece to be placed.
     */
    void set_piece(int position, Piece *piece);

    /**
     * @brief Set a piece at a specific row and column.
     * @param row The row index.
     * @param col The column index.
     * @param piece Pointer to the piece to be placed.
     */
    void set_piece(int row, int col, Piece *piece);

    /**
     * @brief Move a piece to a new position.
     * @param piece Pointer to the piece to be moved.
     * @param destination The destination position.
     * @return 0 if the move is invalid, 1 if the move is valid.
     */
    int move_piece(Piece *piece, int destination);

    /**
     * @brief Move a piece to a new row and column.
     * @param piece Pointer to the piece to be moved.
     * @param row The destination row.
     * @param col The destination column.
     * @return 0 if the move is invalid, 1 if the move is valid.
     */
    int move_piece(Piece *piece, int row, int col);

    /**
     * @brief Move a piece from one position to another.
     * @param position The current position of the piece.
     * @param destination The destination position.
     * @return 0 if the move is invalid, 1 if the move is valid.
     */
    int move_piece(int position, int destination);

    /**
     * @brief Handle a move from one position to another.
     * @param src The source position.
     * @param dest The destination position.
     * @return 0 if the move is invalid, 1 if the move is valid.
     */
    int handle_move(int src, int dest);

    /**
     * @brief Remove a piece from a specific position.
     * @param position The position on the board.
     */
    void remove_piece(int position);

    /**
     * @brief Remove a piece from a specific row and column.
     * @param row The row index.
     * @param col The column index.
     */
    void remove_piece(int row, int col);

    /**
     * @brief Initialize the board with the starting positions of the pieces.
     */
    void initiate_board();

    /**
     * @brief Clear the board.
     */
    void clear_board();

    /**
     * @brief Check if a player is in check.
     * @param color The color of the player.
     * @return True if the player is in check, false otherwise.
     */
    bool is_check(Color color);

    /**
     * @brief Check if a pawn needs to be promoted.
     * @param position The position of the pawn.
     * @param piece Pointer to the pawn.
     * @return True if the pawn needs to be promoted, false otherwise.
     */
    bool is_pawn_promotion(int position, Piece *piece);

    /**
     * @brief Promote a pawn to a new piece type.
     * @param position The position of the pawn.
     * @param piece Pointer to the pawn.
     * @param new_type The new type of the piece.
     */
    void promote_pawn(int position, Piece *piece, PieceType new_type);

    /**
     * @brief Check if an en passant move is possible.
     * @param piece Pointer to the pawn.
     * @param dest The destination position.
     * @return True if en passant is possible, false otherwise.
     */
    bool is_en_passant(Piece *piece, int dest);

    /**
     * @brief Perform an en passant move.
     * @param position The position of the pawn.
     * @param piece Pointer to the pawn.
     * @param dest The destination position.
     */
    void perform_en_passant(int position, Piece *piece, int dest);

    /**
     * @brief Check if castling is possible.
     * @param position The position of the king.
     * @param piece Pointer to the king.
     * @param dest The destination position.
     * @return True if castling is possible, false otherwise.
     */
    bool can_castle(int position, Piece *piece, int dest);

    /**
     * @brief Perform castling.
     * @param position The position of the king.
     * @param piece Pointer to the king.
     * @param dest The destination position.
     */
    void perform_castling(int position, Piece *piece, int dest);

    /**
     * @brief Serialize the board state to a string.
     * @return The serialized board state.
     */
    std::string serialize_board();

    /**
     * @brief Deserialize the board state from a string.
     * @param board_state The serialized board state.
     */
    void deserialize_board(std::string board_state);

    /**
     * @brief Save the current move to the move history.
     */
    void save_move();

    /**
     * @brief Check if a move can be rewound.
     * @param n The number of moves to rewind.
     * @return True if the move can be rewound, false otherwise.
     */
    bool can_rewind_move(size_t n);

    /**
     * @brief Rewind the last n moves.
     * @param n The number of moves to rewind.
     */
    void rewind_move(int n);

    /**
     * @brief Print the board for debugging purposes.
     */
    void print_board();
};

#endif