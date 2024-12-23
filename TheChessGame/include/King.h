#ifndef KING_H
#define KING_H
#include "Piece.h"

/**
 * @brief Class representing a King chess piece.
 */
class King : public Piece
{
private:
    bool has_moved = false; ///< Indicates if the King has moved

public:
    /**
     * @brief Constructor for the King class.
     * @param position Initial position of the King.
     * @param color Color of the King.
     */
    King(int position, Color color);

    /**
     * @brief Get the current position of the King.
     * @return The position of the King.
     */
    int get_position() override;

    /**
     * @brief Get the color of the King.
     * @return The color of the King.
     */
    Color get_color() override;

    /**
     * @brief Move the King to a new position.
     * @param destination The new position of the King.
     */
    void move(int destination) override;

    /**
     * @brief Get the type of the piece.
     * @return The type of the piece (King).
     */
    PieceType get_piece_type() override;

    /**
     * @brief Get the valid moves for the King.
     * @return A vector of valid move positions.
     */
    std::vector<int> get_valid_moves() override;

    /**
     * @brief Get the valid eatable moves for the King.
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
     * @brief Check if the King has moved.
     * @return True if the King has moved, false otherwise.
     */
    bool get_has_moved() const;
};

#endif