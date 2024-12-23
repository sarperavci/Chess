#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

/**
 * @brief Class representing a Bishop chess piece.
 */
class Bishop : public Piece
{
public:
    /**
     * @brief Constructor for the Bishop class.
     * @param position Initial position of the Bishop.
     * @param color Color of the Bishop.
     */
    Bishop(int position, Color color);

    /**
     * @brief Get the current position of the Bishop.
     * @return The position of the Bishop.
     */
    int get_position() override;

    /**
     * @brief Get the color of the Bishop.
     * @return The color of the Bishop.
     */
    Color get_color() override;

    /**
     * @brief Move the Bishop to a new position.
     * @param destination The new position of the Bishop.
     */
    void move(int destination) override;

    /**
     * @brief Get the type of the piece.
     * @return The type of the piece (Bishop).
     */
    PieceType get_piece_type() override;

    /**
     * @brief Get the valid moves for the Bishop.
     * @return A vector of valid move positions.
     */
    std::vector<int> get_valid_moves() override;

    /**
     * @brief Get the valid eatable moves for the Bishop.
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
};

#endif