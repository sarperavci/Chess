#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

/**
 * @brief Class representing a Queen chess piece.
 */
class Queen : public Piece
{
public:
    /**
     * @brief Constructor for the Queen class.
     * @param position Initial position of the Queen.
     * @param color Color of the Queen.
     */
    Queen(int position, Color color);

    /**
     * @brief Get the current position of the Queen.
     * @return The position of the Queen.
     */
    int get_position() override;

    /**
     * @brief Get the color of the Queen.
     * @return The color of the Queen.
     */
    Color get_color() override;

    /**
     * @brief Move the Queen to a new position.
     * @param destination The new position of the Queen.
     */
    void move(int destination) override;

    /**
     * @brief Get the type of the piece.
     * @return The type of the piece (Queen).
     */
    PieceType get_piece_type() override;

    /**
     * @brief Get the valid moves for the Queen.
     * @return A vector of valid move positions.
     */
    std::vector<int> get_valid_moves() override;

    /**
     * @brief Get the valid eatable moves for the Queen.
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