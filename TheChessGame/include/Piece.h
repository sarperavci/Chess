#include <vector>
#ifndef PIECE_H
#define PIECE_H

/**
 * @brief Enum class representing the color of a chess piece.
 */
enum class Color
{
    WHITE, ///< White color
    BLACK  ///< Black color
};

/**
 * @brief Enum class representing the type of a chess piece.
 */
enum class PieceType
{
    KING,   ///< King piece
    QUEEN,  ///< Queen piece
    ROOK,   ///< Rook piece
    BISHOP, ///< Bishop piece
    KNIGHT, ///< Knight piece
    PAWN    ///< Pawn piece
};

/**
 * @brief Virtual class representing a chess piece.
 */
class Piece
{
protected:
    int position; ///< Position of the piece on the board
    PieceType piece_type; ///< Type of the piece
    Color color; ///< Color of the piece

public:
    /**
     * @brief Constructor for the Piece class.
     * @param position Initial position of the piece.
     * @param piece_type Type of the piece.
     * @param color Color of the piece.
     */
    Piece(int position, PieceType piece_type, Color color) : position(position), piece_type(piece_type), color(color) {}

    /**
     * @brief Virtual destructor for the Piece class.
     */
    virtual ~Piece() {}

    /**
     * @brief Get the current position of the piece.
     * @return The position of the piece.
     */
    virtual int get_position() = 0;

    /**
     * @brief Get the color of the piece.
     * @return The color of the piece.
     */
    virtual Color get_color() = 0;

    /**
     * @brief Get the type of the piece.
     * @return The type of the piece.
     */
    virtual PieceType get_piece_type() = 0;

    /**
     * @brief Move the piece to a new position.
     * @param destination The new position of the piece.
     */
    virtual void move(int destination) = 0;

    /**
     * @brief Get the valid moves for the piece.
     * @return A vector of valid move positions.
     */
    virtual std::vector<int> get_valid_moves() = 0;

    /**
     * @brief Get the valid eatable moves for the piece.
     * @return A vector of valid eatable move positions.
     */
    virtual std::vector<int> get_eatable_moves() = 0;

    /**
     * @brief Check if a move is blocked.
     * @param destination The destination position.
     * @param is_eat True if the move involves capturing an enemy piece, false otherwise.
     * @param board The current state of the board.
     * @return True if the move is blocked, false otherwise.
     */
    virtual bool is_move_blocked(int destination, bool is_eat, Piece **board) = 0;

    /**
     * @brief Check if a move is valid.
     * @param destination The destination position.
     * @return True if the move is valid, false otherwise.
     */
    bool is_valid_move(int destination);

    /**
     * @brief Check if an eat move is valid.
     * @param destination The destination position.
     * @return True if the eat move is valid, false otherwise.
     */
    bool is_valid_eat(int destination);

    /**
     * @brief Set the type of the piece.
     * @param new_type The new type of the piece.
     */
    void set_piece_type(PieceType new_type);

    /**
     * @brief Set the position of the piece.
     * @param new_position The new position of the piece.
     */
    void set_position(int new_position);
};

#endif