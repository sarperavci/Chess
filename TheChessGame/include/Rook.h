#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

/**
 * @brief Class representing a Rook chess piece.
 */
class Rook : public Piece
{
private:
    bool has_moved = false; ///< Indicates if the Rook has moved

public:
    /**
     * @brief Constructor for the Rook class.
     * @param position Initial position of the Rook.
     * @param color Color of the Rook.
     */
    Rook(int position, Color color);

    /**
     * @brief Get the current position of the Rook.
     * @return The position of the Rook.
     */
    int get_position() override;

    /**
     * @brief Get the color of the Rook.
     * @return The color of the Rook.
     */
    Color get_color() override;

    /**
     * @brief Move the Rook to a new position.
     * @param destination The new position of the Rook.
     */
    void move(int destination) override;

    /**
     * @brief Get the type of the piece.
     * @return The type of the piece (Rook).
     */
    PieceType get_piece_type() override;

    /**
     * @brief Get the valid moves for the Rook.
     * @return A vector of valid move positions.
     */
    std::vector<int> get_valid_moves() override;

    /**
     * @brief Get the valid eatable moves for the Rook.
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
     * @brief Check if the Rook has moved.
     * @return True if the Rook has moved, false otherwise.
     */
    bool get_has_moved() const;
};

#endif