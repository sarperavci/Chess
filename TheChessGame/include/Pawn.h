#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

/**
 * @brief Class representing a Pawn chess piece.
 */
class Pawn : public Piece
{
private:
    bool has_moved = false; ///< Indicates if the Pawn has moved
    bool has_moved_two_squares = false; ///< Indicates if the Pawn has moved two squares in its first move

public:
    /**
     * @brief Constructor for the Pawn class.
     * @param position Initial position of the Pawn.
     * @param color Color of the Pawn.
     */
    Pawn(int position, Color color);

    /**
     * @brief Get the current position of the Pawn.
     * @return The position of the Pawn.
     */
    int get_position() override;

    /**
     * @brief Get the color of the Pawn.
     * @return The color of the Pawn.
     */
    Color get_color() override;

    /**
     * @brief Move the Pawn to a new position.
     * @param destination The new position of the Pawn.
     */
    void move(int destination) override;

    /**
     * @brief Get the type of the piece.
     * @return The type of the piece (Pawn).
     */
    PieceType get_piece_type() override;

    /**
     * @brief Get the valid moves for the Pawn.
     * @return A vector of valid move positions.
     */
    std::vector<int> get_valid_moves() override;

    /**
     * @brief Get the valid eatable moves for the Pawn.
     * @return A vector of valid eatable move positions.
     */
    std::vector<int> get_eatable_moves() override;

    /**
     * @brief Check if a move is blocked.
     * @param destination The destination position.
     * @param is_eat True if the move involves capturing an enemy piece, false otherwise.
     * @param board The current state of the board.
     * @return True if the move is blocked, false otherwise.
     */
    bool is_move_blocked(int destination, bool is_eat, Piece **board) override;

    /**
     * @brief Check if the Pawn has moved.
     * @return True if the Pawn has moved, false otherwise.
     */
    bool get_has_moved() const;

    /**
     * @brief Check if the Pawn has moved two squares in its first move.
     * @return True if the Pawn has moved two squares, false otherwise.
     */
    bool get_has_moved_two_squares() const;
};

#endif